#ifndef PROCESADOR_I_H
#define PROCESADOR_I_H

#include "Client.h"
#include "Procesador.h"
#include <string>

class ProcesadorIntermediario : public Procesador {
public:
  ProcesadorIntermediario(std::string address, int port);
  bool abrir(std::string token, std::string shaFile, std::string path, std::string archivo);
  void enviar(std::string mesaje);
  ~ProcesadorIntermediario();

private:
  Client *client;
};

#endif