#ifndef PROCESADOR_H
#define PROCESADOR_H

#include "Bitacora.hpp"
#include "Cifrado.hpp"

class Procesador {
protected:
  Bitacora *bitacora;
  bool working;

public:
  virtual bool abrir(std::vector<unsigned char>  token, 
                     std::vector<unsigned char> enShaFile, std::string shaFile,
                     std::vector<unsigned char> enPath, std::string path,
                     std::vector<unsigned char> titulo, std::string archivo) = 0;
  virtual void enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2) = 0;
  virtual void enviar(std::string  mensaje) = 0;
  virtual void disconnect() = 0;
  virtual ~Procesador(){};
  bool isWorking() { return working; }
};

#endif
