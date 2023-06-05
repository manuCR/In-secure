#include "Lector.hpp"
#include "ProcesadorIntermediario.h"
#include "ServerInicial.h"
#include "Sha.h"
#include <iostream>
#include <thread>

ServerInicial::ServerInicial(std::string tok, std::string key1, std::string key2) { 
  token = tok;
  llave1 = key1;
  llave2 = key2;
}

void ServerInicial::setSocket(std::string address, int port, bool cdcd) {
  this->cdcd = cdcd;
}

void ServerInicial::iniciarCero(std::string path) {
  priv = path;
  feedback = new Feedback(getPath(false));
  ceroPub = new ArchivoCero(feedback);
  ceroPriv = new ArchivoCero(feedback);
}

void ServerInicial::abrirCero() {
  ceroPriv->iniciar(getPath(true));
  ceroPub->iniciar(getPath(false));
  // sobre escribir valor de ceroPub en caso de que fuera modificado
}

void ServerInicial::iniciarProcesador(std::string address, int port, bool fin) {
  procesador = new ProcesadorIntermediario(address, port, feedback);
}

void ServerInicial::start() {
  if (!procesador->isWorking()){
    return;
  }
  active = true;
  Cifrado * cifrado = new Cifrado(feedback);
  Sha sha(feedback);
  while (active) {
    abrirCero();
    int tituloNumero = ceroPriv->getArchivoActual();
    std::string titulo = ceroPriv->getFileName();
    std::cout << "tratando de enviar " << titulo << std::endl;
    std::string shaFile = sha.shaFile(getPath(false) + titulo + ".txt");
    Lector lector(feedback);
    if (lector.open(getPath(false) + titulo + ".txt") == 0) {
      if (ceroPriv->cambiarArchivoActual(getPath(true), tituloNumero + 1)) {
        ceroPub->cambiarArchivoActual(getPath(false), tituloNumero + 1);
        //Aqui Token // Llave 1
        std::vector<unsigned char> tolkien = cifrado->encryptMessage(token, FULL + llave1);
        std::vector<unsigned char> tiltien = cifrado->encryptMessage(titulo, FULL + llave1);
        if (procesador->abrir(tolkien, shaFile, getPath(false), titulo, tiltien)) {
          while (lector.read()) {
            std::string chunk = lector.getText();
            //Aqui Chunk // Llave 2 
            std::vector<unsigned char> chunkie = cifrado->encryptMessage(chunk, FULL + llave2);
            procesador->enviar(chunkie, cifrado, llave2);
          }
          lector.close();
        }
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  }
}

void ServerInicial::stop() { active = false; }

std::string ServerInicial::getPath(bool secret) {
  std::string path = "";
  if (secret) {
    path = path + priv;
  }
  if (cdcd) {
    path = path + "/cdcd/";
  } else {
    if (usersIndex >= carpetas) {
      usersIndex = usersIndex % carpetas;
    }
    path = path + "/eaea/" + users[usersIndex++] + "/";
  }
  return path;
}

ServerInicial::~ServerInicial() { delete procesador; }
