#ifndef PROCESADOR_F_H
#define PROCESADOR_F_H

#include "Bitacora.hpp"
#include "Escritor.hpp"
#include "Procesador.h"
#include <string>

class ProcesadorFinal : public Procesador {
public:
  ProcesadorFinal();
  bool abrir(std::string token, std::string shaFile, std::string path, std::string archivo);
  void enviar(std::string mesaje);
  ~ProcesadorFinal();

private:
  Escritor *escritor;
};

#endif