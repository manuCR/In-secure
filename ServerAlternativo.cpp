#include "ServerAlternativo.h"
#include "ProcesadorFinal.h"
#include "ProcesadorIntermediario.h"
#include "Cifrado.hpp"
#include <iostream>
#include <thread>

ServerAlternativo::ServerAlternativo(std::string tok) { token = tok; }

void ServerAlternativo::setSocket(std::string address, int port, bool cdcd) {
  socket = new Socket(address, port);
  socket->bindTo();
  active = false;
  this->cdcd = cdcd;
}

void ServerAlternativo::iniciarProcesador(std::string address, int port,
                                          bool fin) {
  if (fin) {
    procesador = new ProcesadorFinal();
  } else {
    procesador = new ProcesadorIntermediario(address, port);
  }
}

void ServerAlternativo::iniciarCero(std::string path) { priv = path; }

void ServerAlternativo::start() {
  active = true;
  std::thread *worker;
  while (active) {
    int id = socket->acceptConection();
    worker = new std::thread(&ServerAlternativo::getMessages, this, id);
  }
}

void ServerAlternativo::stop() { active = false; }

void ServerAlternativo::getMessages(int id) {
  Cifrado cifrado;
  Socket::mess tok = receive(id);
  //Aqui descifrar tok.mes llave1 
  std::string tolkien = cifrado.decryptMessage(tok.mes, "/home/manuel.arroyoportilla/In-secure/pub.pem");
  if (tolkien == token) {
    Socket::mess shaFile = receive(id);
    Socket::mess path = receive(id);
    Socket::mess titulo = receive(id);
    Socket::mess mesSha = std::string(shaFile.mes);
    std::string mesPath = std::string(path.mes);
    std::string mesTitulo = std::string(titulo.mes);
    ceroPriv->iniciar(priv + mesPath);
    if (ceroPriv->getArchivoActual() < stoi(mesTitulo) &&
        ceroPriv->cambiarArchivoActual(mesPath, stoi(mesTitulo))) {
      if (procesador->abrir(tolkien, mesSha, mesPath, mesTitulo)) {
        Socket::mess message = receive(id);
        std::string mesMessage = std::string(message.mes);
        while (!message.end) {
          procesador->enviar(mesMessage;
          message = receive(id);
        }
      }
    }
  }
}

Socket::mess ServerAlternativo::receive(int id) { return socket->receive(id); }

ServerAlternativo::~ServerAlternativo() {
  delete procesador;
  delete socket;
}
