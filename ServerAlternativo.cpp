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

void ServerAlternativo::iniciarCero(std::string path) {
  priv = path;
  ceroPriv = new ArchivoCero();
 }

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
  std::vector<unsigned char> tok = receive(id);
  //Aqui descifrar tok.mes llave1 
  std::string tolkien = cifrado.decryptMessage(tok, "/home/manuel.arroyoportilla/In-secure/pub.pem");
  if (tolkien == token) {
    std::vector<unsigned char> shaFile = receive(id);
    std::vector<unsigned char> path = receive(id);
    std::vector<unsigned char> titulo = receive(id);
    std::string mesSha (reinterpret_cast<char*>(&shaFile[0]));
    std::string mesPath (reinterpret_cast<char*>(&path[0]));
    std::string mesTitulo (reinterpret_cast<char*>(&titulo[0]));
    std::cout << "mesSha: " << mesSha << std::endl;
    int tituloNum = stoi(mesTitulo);
    ceroPriv->iniciar(priv + mesPath);
    if (ceroPriv->getArchivoActual() == tituloNum &&
        ceroPriv->cambiarArchivoActual(priv + mesPath, tituloNum + 1)) {
      if (procesador->abrir(tok, mesSha, mesPath, mesTitulo)) {
        std::vector<unsigned char> message = receive(id);
        while (message.size()>0) {
          procesador->enviar(message);
          message = receive(id);
        }
      }
    }
  }
}

std::vector<unsigned char> ServerAlternativo::receive(int id) { return socket->receive(id); }

ServerAlternativo::~ServerAlternativo() {
  delete procesador;
  delete socket;
}
