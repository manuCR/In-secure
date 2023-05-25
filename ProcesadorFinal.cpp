#include "ProcesadorFinal.h"

ProcesadorFinal::ProcesadorFinal() { escritor = new Escritor(); }

bool ProcesadorFinal::abrir(std::string token, std::string path,
                            std::string archivo) {
  return escritor->open(path + archivo + ".txt");
}
void ProcesadorFinal::enviar(std::string mensaje) { escritor->write(mensaje); }

ProcesadorFinal::~ProcesadorFinal() {
  escritor->close();
  delete escritor;
}
