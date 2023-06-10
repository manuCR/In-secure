#include "ServerInicial.h"
#include "Hex.h"
#include "ProcesadorIntermediario.h"
#include "Sha.h"
#include <chrono>
#include <cstdio>
#include <ctime>
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
  usersIndex = 0;
  ceroPub = new ArchivoCero(feedback);
  ceroPriv = new ArchivoCero(feedback);
}

void ServerInicial::abrirCero() {
  pathPublico = getPath();
  pathPrivado = priv + pathPublico;
  feedback->iniciar(pathPublico);
  ceroPriv->iniciar(pathPrivado);
  ceroPub->iniciar(pathPublico);
  ceroPub->restaurarActual(ceroPriv->getArchivoActual());
}

void ServerInicial::iniciarProcesador(std::string address, int port, bool fin, std::string bindIp) {
  procesador = new ProcesadorIntermediario(address, port, feedback, bindIp);
}

void ServerInicial::start() {
  if (!procesador->isWorking()) {
    feedback->agregarFeedback("No se pudo contactar al siguiente nodo");
    return;
  }
  active = true;
  cifrado = new Cifrado(feedback);
  lector = new Lector(feedback);
  while (active) {
    sleep();
    abrirCero();
    int tituloNumero = ceroPriv->getArchivoActual();
    std::string titulo = ceroPriv->getFileName();
    if (lector->open(pathPublico + titulo + ".txt") == 0) {
      if (isCDCD(titulo) || autenticar(lector)){
        if (ceroPriv->cambiarArchivoActual(tituloNumero + 1)) {
          ceroPub->cambiarArchivoActual(tituloNumero + 1);
          std::vector<unsigned char> tolkien = cifrado->encryptMessage(token, FULL + llave1);
          std::vector<unsigned char> tiltien = cifrado->encryptMessage(titulo, FULL + llave1);
          std::vector<unsigned char> shatien = cifrado->encryptMessage(shaFile, FULL + llave1);
          std::vector<unsigned char> pathien = cifrado->encryptMessage(pathPublico, FULL + llave1);
          if (procesador->abrir(tolkien, shatien, shaFile, pathien, pathPublico, tiltien, titulo)) {
            int chunkSize = cifrado->chunkSize(FULL + llave2, false);
            while (lector->read(chunkSize)) {
              std::string chunk = lector->getText();
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
    usersIndex++;
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
  std::string name = lector->readLine();
  std::string user = users[usersIndex];
  if(name.size() < 100 && name.find(user) != std::string::npos) {
    std::string hexa = lector->readLine();
    if (hexa.size() > 0) {
      hexa.pop_back();
      Hex hex;
      std::vector<unsigned char>  shaEncriptado = hex.hexToByte(hexa);
      std::string keyPath = FULL + pathPrivado + user + ".pem";
      std::string messageSha = cifrado->decryptMessage(shaEncriptado, keyPath, false);
      if(messageSha.size() == 64) {
        long start = lector->getPosition();
        Sha sha(feedback);
        int noError = sha.start();
        int read = lector->read(512);
        while (read > 0 && noError == 0) {
          noError = sha.add(lector->getChars(), read);
          read = lector->read(512);
        }
        shaFile = sha.finish();
        if(messageSha == shaFile){
          lector->setPosition(start);
          return true;
        }
      }
    }
  }
  return false;
}

void ServerInicial::stop() {
  active = false;
}

void ServerInicial::sleep() {
  if (cdcd) {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm * localTime = std::localtime(&currentTime);
    int hours = localTime->tm_hour % 2 * 60;
    int minutes = localTime->tm_min + 10;
    int sleepTime = 120 - (hours + minutes) % 120;
    std::this_thread::sleep_for(std::chrono::minutes(sleepTime));
  } else {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

std::string ServerInicial::getPath() {
  std::string path = "";
  if (cdcd) {
    path = path + "/cdcd/";
  } else {
    if (usersIndex >= carpetas) {
      usersIndex = usersIndex % carpetas;
    }
    path = path + "/eaea/" + users[usersIndex] + "/";
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
