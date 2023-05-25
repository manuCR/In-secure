#include "Cifrado.hpp"
#include "ProcesadorFinal.h"

ProcesadorFinal::ProcesadorFinal() { escritor = new Escritor(); }

bool ProcesadorFinal::abrir(std::string token, std::string path,
                            std::string archivo) {
  return escritor->open(path + archivo + ".txt");
}
void ProcesadorFinal::enviar(std::string mensaje) { 
  //Aqui Desencriptar Mensaje chunk con llave 2 
  Cifrado cifrado;
  std::string chunkie = cifrado.decryptMessage(mensaje, "/home/valery.murcia/In-secure/key2.pem");

  escritor->write(chunkie); 
  }

ProcesadorFinal::~ProcesadorFinal() {
  escritor->close();
  delete escritor;
}
