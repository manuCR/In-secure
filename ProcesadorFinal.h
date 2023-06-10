#ifndef PROCESADOR_F_H
#define PROCESADOR_F_H

#include "Escritor.hpp"
#include "Procesador.h"

class ProcesadorFinal : public Procesador {
  public:
    ProcesadorFinal();
    bool abrir(std::vector<unsigned char>  token, 
               std::vector<unsigned char> enShaFile, std::string shaFile,
               std::vector<unsigned char> enPath, std::string path,
               std::vector<unsigned char> titulo, std::string archivo);
    void enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2);
    void enviar(std::string  mensaje);
    void disconnect();
    ~ProcesadorFinal();

  private:
    Escritor *escritor;
};

#endif