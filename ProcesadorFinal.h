#ifndef PROCESADOR_F_H
#define PROCESADOR_F_H

#include "Bitacora.hpp"
#include "Escritor.hpp"
#include "Procesador.h"
#include <string>
#include <vector>

class ProcesadorFinal : public Procesador {
public:
  ProcesadorFinal();
  bool abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path, std::string archivo);
  void enviar(std::vector<unsigned char>  mensaje);
  ~ProcesadorFinal();

private:
  Escritor *escritor;
};

#endif