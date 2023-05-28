#include "ArchivoCero.h"
#include "Lector.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

ArchivoCero::ArchivoCero() {
  actual = 0;
  escritor = new Escritor();
}

void ArchivoCero::iniciar(std::string pato) {
  path = pato;
  Lector lector;
  // verificar que se logro abrir?
  std::cout << "path "<< path << std::endl;
  if(lector.open(path + NOMBRE)){
    int posicion = lector.read();
    if (posicion) {
      std::string numero = lector.getText();
      actual = stoi(numero);
    }
    lector.close();
  }
} 

int ArchivoCero::getArchivoActual() { return actual; }

bool ArchivoCero::cambiarArchivoActual(std::string path, int numero) {
  std::lock_guard<std::mutex> lock(mutex);
  escritor->open(path + NOMBRE);
  if (actual + 1 != numero) {
    return false;
  }
  actual++;
  escritor->inicio();
  escritor->write(getFileName());
  escritor->close();
  return true;
}

std::string ArchivoCero::getFileName() {
  std::stringstream ss;
  ss << std::setw(6) << std::setfill('0') << actual;
  std::cout << "actual " << actual << std::endl;
  std::cout << "ss " << ss.str() << std::endl;
  return ss.str();
}

ArchivoCero::~ArchivoCero() {
  delete escritor;
}
