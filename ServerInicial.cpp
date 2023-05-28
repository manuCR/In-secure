#include "ServerInicial.h"
#include "Lector.hpp"
#include "Cifrado.hpp"
#include "Sha.h"
#include <iostream>
#include <chrono>
#include <thread>

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
  Cifrado cifrado;
  Sha sha;
  while (active) {
    abrirCero();
    int tituloNumero = ceroPriv->getArchivoActual();
    std::string titulo = ceroPriv->getFileName();
    std::string shaFile = sha.shaFile(getPath(false) + titulo + ".txt");
    Lector lector;
    if (lector.open(getPath(false) + titulo + ".txt") == 0) {
      if (true || ceroPriv->cambiarArchivoActual(getPath(true), tituloNumero + 1)) {
        ceroPub->cambiarArchivoActual(getPath(false), tituloNumero + 1);
        Aqui Token // Llave 1
        char tolkien[512] = {0};
        cifrado.encryptMessage(token, "/home/manuel.arroyoportilla/In-secure/key.pem", tolkien);
        if (procesador->abrir(tolkien, shaFile, getPath(false), titulo)) {
          while (lector.read()) {
            std::string chunk = lector.getText();
            //Aqui Chunk // Llave 2 
            char chunkie[512] = {0};
            cifrado.encryptMessage(chunk, "/home/manuel.arroyoportilla/In-secure/key2.pem", chunkie);
            procesador->enviar(chunkie);
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
    path = path + "/eaea/" + users[usersIndex++];
  }
  return path;
}

ServerInicial::~ServerInicial() { delete procesador; }
