#include "ProcesadorIntermediario.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

ProcesadorIntermediario::ProcesadorIntermediario(std::string address,
                                                 int port) {
  client = new Client(address, port);
  bitacora = new Bitacora();
}

bool ProcesadorIntermediario::abrir(std::string token, std::string shaFile, std::string path,
                                    std::string archivo) {
  bitacora->add(shaFile);
  std::cout << "token size:" << token.length() << std::endl;
  client->send(token);
  client->send(shaFile);
  client->send(path);
  client->send(archivo);
  return true;
}
void ProcesadorIntermediario::enviar(char * mensaje) {
  // tal vez funciona?
  std::string mes;
  mes.resize(512);
  memcpy(&mes[0], mensaje, 512);
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
