#include "Cifrado.hpp"
#include "ProcesadorFinal.h"

ProcesadorFinal::ProcesadorFinal() { 
  escritor = new Escritor();
  bitacora = new Bitacora();
  working = true;
  }

bool ProcesadorFinal::abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path,
                            std::string archivo, std::vector<unsigned char> titulo) {
  bitacora->add(shaFile);
  return escritor->open(path + archivo + ".txt", "w+") == 0;
}
void ProcesadorFinal::enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2) { 
  //Aqui Desencriptar Mensaje chunk con llave 2
  std::string chunkie = cifrado->decryptMessage(mensaje, llave2);

  escritor->write(chunkie); 
}

ProcesadorFinal::~ProcesadorFinal() {
  escritor->close();
  delete escritor;
}
