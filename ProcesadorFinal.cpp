#include "Cifrado.hpp"
#include "ProcesadorFinal.h"
#include <iostream>

ProcesadorFinal::ProcesadorFinal() { 
  escritor = new Escritor();
  bitacora = new Bitacora();
  }

bool ProcesadorFinal::abrir(char * token, std::string shaFile, std::string path,
                            std::string archivo) {
  bitacora->add(shaFile);
  return escritor->open(path + archivo + ".txt") == 0;
}
void ProcesadorFinal::enviar(char * mensaje) { 
  //Aqui Desencriptar Mensaje chunk con llave 2
  Cifrado cifrado;
  std::string chunkie = cifrado.decryptMessage(mensaje, "/home/manuel.arroyoportilla/In-secure/pub2.pem");

  escritor->write(chunkie); 
  }

ProcesadorFinal::~ProcesadorFinal() {
  escritor->close();
  delete escritor;
}
