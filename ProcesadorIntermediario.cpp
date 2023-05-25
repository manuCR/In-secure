#include "ProcesadorIntermediario.h"

ProcesadorIntermediario::ProcesadorIntermediario(std::string address,
                                                 int port) {
  client = new Client(address, port);
}

bool ProcesadorIntermediario::abrir(std::string token, std::string path,
                                    std::string archivo) {
  client->send(token);
  client->send(path);
  client->send(archivo);
  return true;
}
void ProcesadorIntermediario::enviar(std::string mensaje) {
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
