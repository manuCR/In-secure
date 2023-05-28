#include "ProcesadorIntermediario.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

ProcesadorIntermediario::ProcesadorIntermediario(std::string address,
                                                 int port) {
  client = new Client(address, port);
  bitacora = new Bitacora();
}

bool ProcesadorIntermediario::abrir(char * token, std::string shaFile, std::string path,
                                    std::string archivo) {
  bitacora->add(shaFile);
  client->send(token);
  client->send(shaFile.c_str());
  client->send(path.c_str());
  client->send(archivo.c_str());
  return true;
}
void ProcesadorIntermediario::enviar(char * mensaje) {
  // tal vez funciona?
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
