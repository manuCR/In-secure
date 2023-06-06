#ifndef PROCESADOR_F_H
#define PROCESADOR_F_H

#include "Escritor.hpp"
#include "Procesador.h"

class ProcesadorFinal : public Procesador {
  public:
    ProcesadorFinal();
    bool abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path,
               std::string archivo, std::vector<unsigned char> titulo);
    void enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2);
    void enviar(std::string  mensaje);
    ~ProcesadorFinal();

  private:
    Escritor *escritor;
};

#endif