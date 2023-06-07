#include "ServerInicial.h"
#include "Hex.h"
#include "ProcesadorIntermediario.h"
#include "Sha.h"
#include <cstdio>
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
  feedback = new Feedback();
  feedback->iniciar(getPath());
  usersIndex--;
  ceroPub = new ArchivoCero(feedback);
  ceroPriv = new ArchivoCero(feedback);
}

void ServerInicial::abrirCero() {
  pathPublico = getPath();
  pathPrivado = priv + pathPublico;
  feedback->iniciar(pathPublico);
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
  cifrado = new Cifrado(feedback);
  lector = new Lector(feedback);
  while (active) {
    abrirCero();
    int tituloNumero = ceroPriv->getArchivoActual();
    std::string titulo = ceroPriv->getFileName();
    std::cout << "tratando de enviar " << titulo << std::endl;
    if (lector->open(pathPublico + titulo + ".txt") == 0) {
      if (autenticar(lector)){
        if (ceroPriv->cambiarArchivoActual(pathPrivado, tituloNumero + 1)) {
          ceroPub->cambiarArchivoActual(pathPublico, tituloNumero + 1);
          //Aqui Token // Llave 1
          std::vector<unsigned char> tolkien = cifrado->encryptMessage(token, FULL + llave1);
          std::vector<unsigned char> tiltien = cifrado->encryptMessage(titulo, FULL + llave1);
          if (procesador->abrir(tolkien, shaFile, pathPublico, titulo, tiltien)) {
            int chunkSize = cifrado->chunkSize(FULL + llave2, false);
            while (lector->read(chunkSize)) {
              std::string chunk = lector->getText();
              //Aqui Chunk // Llave 2 
              std::vector<unsigned char> chunkie = cifrado->encryptMessage(chunk, FULL + llave2);
              procesador->enviar(chunkie, cifrado, FULL + llave2);
            }
            procesador->enviar("");
          }
        }
      } else {
        feedback->agregarFeedback("No se pudo autenticar al usuario");
      }
      lector->close();
    }
    // despertarse cada dos horas
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  }
}

bool ServerInicial::isCDCD(std::string titulo) {
  if(cdcd) {
    Sha sha(feedback);
    shaFile = sha.shaFile(pathPublico + titulo + ".txt");
  }
  return cdcd;
}

bool ServerInicial::autenticar(Lector * lector) {
  std::cout << "pase1 " << std::endl;
  std::string name = lector->readLine();
  std::string user = users[usersIndex];
  if(name.size() < 100 && name.find(user) != std::string::npos) {
    std::cout << "pase1 " << std::endl;
    std::string hexa = lector->readLine();
    Hex hex;
    std::vector<unsigned char>  shaEncriptado = hex.hexToByte(hexa);
    std::string keyPath = FULL + pathPrivado + user + ".pem";
    std::string messageSha = cifrado->decryptMessage(shaEncriptado, keyPath, false);
    long start = lector->getPosition();
    if(messageSha.size() == 64) {
      std::cout << "pase2 " << std::endl;
      Sha sha(feedback);
      bool noError = true;
      int read = lector->read(512);
      while (read > 0 && noError == 0) {
        noError = sha.add(lector->getChars(), read);
        read = lector->read(512);
      }
      shaFile = sha.finish();
      if(messageSha == shaFile){
        std::cout << "pase3 " << std::endl;
        lector->setPosition(start);
        return true;
      }
    }
  }
  return false;
}

void ServerInicial::stop() {
  active = false;
}

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

ServerInicial::~ServerInicial() {
  delete lector;
  delete cifrado;
  delete ceroPub;
  delete ceroPriv;
  delete feedback;
  delete procesador;
}
