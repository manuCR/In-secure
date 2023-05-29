#ifndef PROCESADOR_I_H
#define PROCESADOR_I_H

#include "Client.h"
#include "Procesador.h"
#include <string>

class ProcesadorIntermediario : public Procesador {
public:
  ProcesadorIntermediario(std::string address, int port);
  bool abrir(char * token, std::string shaFile, std::string path, std::string archivo);
  void enviar(char * mensaje);
  ~ProcesadorIntermediario();

private:
  Client *client;
};

#endif