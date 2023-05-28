#ifndef PROCESADOR_F_H
#define PROCESADOR_F_H

#include "Bitacora.hpp"
#include "Escritor.hpp"
#include "Procesador.h"
#include <string>

class ProcesadorFinal : public Procesador {
public:
  ProcesadorFinal();
  bool abrir(char * token, std::string shaFile, std::string path, std::string archivo);
  void enviar(char * mensaje);
  ~ProcesadorFinal();

private:
  Escritor *escritor;
};

#endif