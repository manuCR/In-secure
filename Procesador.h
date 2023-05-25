#ifndef PROCESADOR_H
#define PROCESADOR_H

#include <string>

class Procesador {
public:
  virtual bool abrir(std::string token, std::string path,
                     std::string archivo) = 0;
  virtual void enviar(std::string mesaje) = 0;
  virtual ~Procesador(){};
};

#endif