#ifndef PROCESADOR_H
#define PROCESADOR_H

#include "Bitacora.hpp"
#include "Cifrado.hpp"

class Procesador {
protected:
  Bitacora *bitacora;
  bool working;

public:
  virtual bool abrir(std::vector<unsigned char> token, std::string shaFile,
                     std::string path,
                     std::string archivo,
                     std::vector<unsigned char> titulo) = 0;
  virtual void enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2) = 0;
  virtual ~Procesador(){};
  bool isWorking() { return working; }
};

#endif
