#ifndef PROCESADOR_I_H
#define PROCESADOR_I_H

#include "Client.h"
#include "Procesador.h"
#include <string>
#include <vector>

class ProcesadorIntermediario : public Procesador {
public:
  ProcesadorIntermediario(std::string address, int port);
  bool abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path, std::string archivo);
  void enviar(std::vector<unsigned char>  mensaje);
  ~ProcesadorIntermediario();

private:
  Client *client;
};

#endif