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
    ceroPriv->iniciar(priv + path.mes);
    if (ceroPriv->getArchivoActual() < stoi(titulo.mes) &&
        ceroPriv->cambiarArchivoActual(path.mes, stoi(titulo.mes))) {
      if (procesador->abrir(tolkien, shaFile.mes, path.mes, titulo.mes)) {
        Socket::mess message = receive(id);
        while (!message.end) {
          procesador->enviar(message.mes);
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
