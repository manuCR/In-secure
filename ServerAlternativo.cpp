#include "Lector.hpp"
#include "ServerAlternativo.h"
#include "ProcesadorFinal.h"
#include "ProcesadorIntermediario.h"
#include <thread>

extern const char * const FULL;

ServerAlternativo::ServerAlternativo(std::string tok, std::string key1, std::string key2) {
  token = tok;
  llave1 = key1;
  llave2 = key2;
}

void ServerAlternativo::setSocket(std::string address, int port, bool cdcd) {
  socket = new Socket(address, port, feedback);
  socket->bindTo();
  working = socket->listen();
  active = false;
  this->cdcd = cdcd;
}

void ServerAlternativo::iniciarProcesador(std::string address, int port, bool fin) {
  if (fin) {
    procesador = new ProcesadorFinal();
  } else {
    procesador = new ProcesadorIntermediario(address, port, feedback);
  }
}

void ServerAlternativo::iniciarCero(std::string path) {
  priv = path;
  feedback = new Feedback(priv);
  ceroPriv = new ArchivoCero(feedback);
 }

void ServerAlternativo::start() {
  if (!procesador->isWorking() || !working){
    return;
  }
  active = true;
  std::thread *worker;
  while (active) {
    int id = socket->acceptConection();
    worker = new std::thread(&ServerAlternativo::getMessages, this, id);
  }
}

void ServerAlternativo::stop() { active = false; }

void ServerAlternativo::getMessages(int id) {
  Cifrado * cifrado = new Cifrado(feedback);
  std::vector<unsigned char> tok = receive(id);
  std::string tolkien = cifrado->decryptMessage(tok, FULL + llave1);
  if (tolkien == token) {
    std::vector<unsigned char> shaFile = receive(id);
    std::vector<unsigned char> path = receive(id);
    std::vector<unsigned char> titulo = receive(id);
    std::string mesSha (reinterpret_cast<char*>(&shaFile[0]));
    std::string mesPath (reinterpret_cast<char*>(&path[0]));
    std::string mesTitulo = cifrado->decryptMessage(titulo, FULL + llave1);
    int tituloNum = stoi(mesTitulo);
    ceroPriv->iniciar(priv + mesPath);
    if (ceroPriv->getArchivoActual() == tituloNum &&
        ceroPriv->cambiarArchivoActual(priv + mesPath, tituloNum + 1)) {
      if (procesador->abrir(tok, mesSha, mesPath, mesTitulo, titulo)) {
        std::vector<unsigned char> message = receive(id);
        while (message.size()>0) {
          procesador->enviar(message, cifrado, llave2);
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
