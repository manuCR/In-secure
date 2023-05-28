#include "ProcesadorIntermediario.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

ProcesadorIntermediario::ProcesadorIntermediario(std::string address,
                                                 int port) {
  client = new Client(address, port);
  bitacora = new Bitacora();
}

bool ProcesadorIntermediario::abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path,
                                    std::string archivo) {
  bitacora->add(shaFile);
  client->send(token);
  client->send(shaFile);
  client->send(path);
  client->send(archivo);
  return true;
}
void ProcesadorIntermediario::enviar(std::vector<unsigned char>  mensaje) {
  // tal vez funciona?
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
