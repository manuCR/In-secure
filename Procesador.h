#ifndef PROCESADOR_H
#define PROCESADOR_H

#include <string>
#include "Bitacora.hpp"
#include <vector>

class Procesador {
  protected:
    Bitacora *bitacora;

  public:
    virtual bool abrir(std::vector<unsigned char> token, std::string shaFile,
                       std::string path,
                       std::string archivo) = 0;
    virtual void enviar(std::vector<unsigned char>  mensaje) = 0;
    virtual ~Procesador(){};
};

#endif