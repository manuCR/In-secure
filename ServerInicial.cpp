#include "ServerInicial.h"
#include "Lector.hpp"
#include <iostream>

ServerInicial::ServerInicial(std::string tok) { token = tok; }

void ServerInicial::setSocket(std::string address, int port, bool cdcd) {
  this->cdcd = cdcd;
}

void ServerInicial::iniciarCero(std::string path) {
  priv = path;
  ceroPub = new ArchivoCero();
  ceroPriv = new ArchivoCero();
}

void ServerInicial::abrirCero() {
  ceroPriv->iniciar(getPath(true));
  ceroPub->iniciar(getPath(false));
  // sobre escribir valor de ceroPub en caso de que fuera modificado
}

void ServerInicial::iniciarProcesador(std::string address, int port, bool fin) {
  procesador = new ProcesadorIntermediario(address, port);
}

void ServerInicial::start() {
  active = true;
  while (active) {
    abrirCero();
    int tituloNumero = ceroPriv->getArchivoActual();
    std::string titulo = ceroPriv->getFileName();
    Lector lector;
    if (lector.open(getPath(false) + titulo + ".txt")) {
      if (ceroPriv->cambiarArchivoActual(getPath(true), tituloNumero + 1)) {
        ceroPub->cambiarArchivoActual(getPath(false), tituloNumero + 1);
        if (procesador->abrir(token, getPath(false), titulo)) {
          std::string texto = "";
          while (lector.read()) {
            std::string chunk = lector.getText();
            texto += chunk;
            procesador->enviar(chunk);
          }
          std::cout << "lectura final:" << texto << std::endl;
          lector.close();
        }
      }
    }
  }
}

void ServerInicial::stop() { active = false; }

std::string ServerInicial::getPath(bool secret) {
  std::string path = "";
  if (secret) {
    path = path + priv;
  }
  if (cdcd) {
    path = path + "/cdcd";
  } else {
    if (usersIndex >= carpetas) {
      usersIndex = usersIndex % carpetas;
    }
    path = path + "/eaea/" + users[usersIndex++];
  }
  return path;
}

ServerInicial::~ServerInicial() { delete procesador; }
