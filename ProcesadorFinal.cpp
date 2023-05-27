#include "Cifrado.hpp"
#include "ProcesadorFinal.h"

ProcesadorFinal::ProcesadorFinal() { 
  escritor = new Escritor();
  bitacora = new Bitacora();
  }

bool ProcesadorFinal::abrir(std::string token, std::string shaFile, std::string path,
                            std::string archivo) {
  bitacora->add(shaFIle);
  return escritor->open(path + archivo + ".txt");
}
void ProcesadorFinal::enviar(std::string mensaje) { 
  //Aqui Desencriptar Mensaje chunk con llave 2 
  Cifrado cifrado;
  std::string chunkie = cifrado.decryptMessage(mensaje, "/home/manuel.arroyoportilla/In-secure/key2.pem");

  escritor->write(chunkie); 
  }

ProcesadorFinal::~ProcesadorFinal() {
  escritor->close();
  delete escritor;
}
