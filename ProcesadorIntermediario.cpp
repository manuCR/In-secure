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
  client->send(&shaFile[0]);
  client->send(&path[0]);
  client->send(&archivo[0]);
  return true;
}
void ProcesadorIntermediario::enviar(char * mensaje) {
  // tal vez funciona?
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
