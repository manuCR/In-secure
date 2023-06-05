#include "ProcesadorIntermediario.h"

ProcesadorIntermediario::ProcesadorIntermediario(std::string address, int port, Feedback * feedback) {
  client = new Client(address, port, feedback);
  bitacora = new Bitacora();
  working = client->isWorking();
}

bool ProcesadorIntermediario::abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path,
                                    std::string archivo, std::vector<unsigned char> titulo) {
  bitacora->add(shaFile);
  client->send(token);
  client->send(shaFile);
  client->send(path);
  client->send(titulo);
  return true;
}
void ProcesadorIntermediario::enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2) {
  client->send(mensaje);
}

ProcesadorIntermediario::~ProcesadorIntermediario() { delete client; }
