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

void ServerInicial::setSocket(std::string address, int port) {
}

void ServerInicial::iniciarCero(std::string path, bool cdcd) {
  this->cdcd = cdcd;
  priv = path;
  feedback = new Feedback(getPath());
  usersIndex--;
  ceroPub = new ArchivoCero(feedback);
  ceroPriv = new ArchivoCero(feedback);
}

void ServerInicial::abrirCero() {
  pathPublico = getPath();
  pathPrivado = priv + pathPublico;
  ceroPriv->iniciar(pathPrivado);
  ceroPub->iniciar(pathPublico);
  // sobre escribir valor de ceroPub en caso de que fuera modificado
}

void ServerInicial::iniciarProcesador(std::string address, int port, bool fin, std::string bindIp) {
  procesador = new ProcesadorIntermediario(address, port, feedback, bindIp);
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
    std::string shaFile = sha.shaFile(pathPublico + titulo + ".txt");
    Lector lector(feedback);
    if (lector.open(pathPublico + titulo + ".txt") == 0) {
      if (ceroPriv->cambiarArchivoActual(pathPrivado, tituloNumero + 1)) {
        ceroPub->cambiarArchivoActual(pathPublico, tituloNumero + 1);
        //Aqui Token // Llave 1
        if (cdcd || autenticar()){
          std::vector<unsigned char> tolkien = cifrado->encryptMessage(token, FULL + llave1);
          std::vector<unsigned char> tiltien = cifrado->encryptMessage(titulo, FULL + llave1);
          if (procesador->abrir(tolkien, shaFile, pathPublico, titulo, tiltien)) {
            int chunkSize = cifrado->chunkSize(FULL + llave2);
            while (lector.read(chunkSize)) {
              std::string chunk = lector.getText();
              //Aqui Chunk // Llave 2 
              std::vector<unsigned char> chunkie = cifrado->encryptMessage(chunk, FULL + llave2);
              procesador->enviar(chunkie, cifrado, FULL + llave2);
            }
            procesador->enviar("");
            lector.close();
          }
        }
      }
    }
    // despertarse cada dos horas
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  }
}

void ServerInicial::stop() { active = false; }

std::string ServerInicial::getPath() {
  std::string path = "";
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
