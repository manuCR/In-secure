#include "ProcesadorIntermediario.h"

ProcesadorIntermediario::ProcesadorIntermediario(std::string address, int port, Feedback * feedback, std::string bindIp) {
  client = new Client(address, port, feedback, bindIp);
  bitacora = new Bitacora();
}

bool ProcesadorIntermediario::abrir(std::vector<unsigned char>  token, 
                                    std::vector<unsigned char> enShaFile, std::string shaFile,
                                    std::vector<unsigned char> enPath, std::string path,
                                    std::vector<unsigned char> titulo, std::string archivo) {
  client->connect();
  bitacora->add(shaFile);
  client->send(token);
  client->send(enShaFile);
  client->send(enPath);
  client->send(titulo);
  return true;
}

void ProcesadorIntermediario::enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2) {
  client->send(mensaje);
}

void ProcesadorIntermediario::enviar(std::string  mensaje) { 
  client->send(mensaje); 
}

void ProcesadorIntermediario::disconnect() { 
  client->disconnect();
}

ProcesadorIntermediario::~ProcesadorIntermediario() {
  delete bitacora;
  delete client;
}
