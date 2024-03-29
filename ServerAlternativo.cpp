#include "Feedback.h"
#include "Lector.hpp"
#include "ServerAlternativo.h"
#include "ProcesadorFinal.h"
#include "ProcesadorIntermediario.h"
#include <thread>

ServerAlternativo::ServerAlternativo(std::string tok, std::string key1, std::string key2) {
  token = tok;
  llave1 = key1;
  llave2 = key2;
}

void ServerAlternativo::setSocket(std::string address, int port) {
  socket = new Socket(address, port, feedback);
  socket->bindTo("");
  working = socket->listen();
  active = false;
}

void ServerAlternativo::iniciarProcesador(std::string address, int port, bool fin, std::string bindIp) {
  this->cdcd = cdcd;
  if (fin) {
    procesador = new ProcesadorFinal();
  } else {
    procesador = new ProcesadorIntermediario(address, port, feedback, bindIp);
  }
}

void ServerAlternativo::iniciarCero(std::string path, bool cdcd) {
  priv = path;
  feedback = new Feedback();
  if (cdcd) {
    feedback->iniciar(priv + "/cdcd/");
  } else {
    feedback->iniciar(priv + "/eaea/");
  }
  ceroPriv = new ArchivoCero(feedback);
  cifrado = new Cifrado(feedback);
 }

void ServerAlternativo::start() {
  active = true;
  while (active) {
    int id = socket->acceptConection();
    new std::thread(&ServerAlternativo::getMessages, this, id);
  }
}

void ServerAlternativo::stop() {
  active = false;
}

void ServerAlternativo::getMessages(int id) {
  std::vector<unsigned char> tok = receive(id);
  if (tok.size() > 0) {
    std::string tolkien = cifrado->decryptMessage(tok, FULL + llave1, true);
    if (tolkien == token) {
      std::vector<unsigned char> shaFile = receive(id);
      std::vector<unsigned char> path = receive(id);
      std::vector<unsigned char> titulo = receive(id);
      std::string mesSha = cifrado->decryptMessage(shaFile, FULL + llave1, false);
      std::string mesPath = cifrado->decryptMessage(path, FULL + llave1, false);
      std::string mesTitulo = cifrado->decryptMessage(titulo, FULL + llave1, false);
      int tituloNum = stoi(mesTitulo);
      ceroPriv->iniciar(priv + mesPath);
      if (ceroPriv->getArchivoActual() == tituloNum &&
          ceroPriv->cambiarArchivoActual(tituloNum + 1)) {
        if (procesador->abrir(tok, shaFile, mesSha, path, mesPath, titulo, mesTitulo)) {
          std::vector<unsigned char> message = receive(id);
          while (message.size()>0) {
            procesador->enviar(message, cifrado, FULL + llave2);
            message = receive(id);
          }
          procesador->enviar("");
          procesador->disconnect();
        }
      }
    }
  }
}

std::vector<unsigned char> ServerAlternativo::receive(int id) {
  return socket->receive(id);
}

ServerAlternativo::~ServerAlternativo() {
  delete cifrado;
  delete ceroPriv;
  delete feedback;
  delete procesador;
  delete socket;
}
