#include "ProcesadorIntermediario.h"

ProcesadorIntermediario::ProcesadorIntermediario(std::string address,
                                                 int port) {
  client = new Client(address, port);
  bitacora = new Bitacora();
}

bool ProcesadorIntermediario::abrir(std::string token, std::string shaFile, std::string path,
                                    std::string archivo) {
  bitacora->add(shaFile);
  client->send(token);
  client->send(shaFile);
  client->send(path);
  client->send(archivo);
  return true;
}
void ProcesadorIntermediario::enviar(std::string mensaje) {
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
