#ifndef PROCESADOR_H
#define PROCESADOR_H

#include <string>
#include "Bitacora.hpp"

class Procesador {
protected:
  Bitacora *bitacora;

public:
  virtual bool abrir(char * token, std::string shaFile,
                     std::string path,
                     std::string archivo) = 0;
  virtual void enviar(char* mensaje) = 0;
  virtual ~Procesador(){};
};

#endif