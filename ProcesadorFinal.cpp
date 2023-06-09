#include "Cifrado.hpp"
#include "ProcesadorFinal.h"

ProcesadorFinal::ProcesadorFinal() { 
  escritor = new Escritor();
  bitacora = new Bitacora();
  working = true;
  }

bool ProcesadorFinal::abrir(std::vector<unsigned char>  token, 
                            std::vector<unsigned char> enShaFile, std::string shaFile,
                            std::vector<unsigned char> enPath, std::string path,
                            std::vector<unsigned char> titulo, std::string archivo) {
  bitacora->add(shaFile);
  return escritor->open(path + archivo + ".txt", "w+") == 0;
}

void ProcesadorFinal::enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2) { 
  std::string chunkie = cifrado->decryptMessage(mensaje, llave2, false);
  escritor->write(chunkie); 
}

void ProcesadorFinal::enviar(std::string  mensaje) {
  escritor->close();
}

ProcesadorFinal::~ProcesadorFinal() {
  delete bitacora;
  delete escritor;
}
