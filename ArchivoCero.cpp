#include "ArchivoCero.h"
#include "Lector.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

#include <cerrno>
#include <cstring>

ArchivoCero::ArchivoCero() {
  actual = 0;
  escritor = new Escritor();
}

void ArchivoCero::iniciar(std::string pato) {
  path = pato;
  Lector lector;
  std::cout << "archivo cero iniciar pato: " <<  pato << std::endl;
  std::cout << "archivo cero iniciar path: " <<  path << std::endl;
  std::string full = path + NOMBRE;
  std::cout << "archivo cero iniciar full: " <<  path << NOMBRE << std::endl;
  if(lector.open(path + NOMBRE) == 0){
    int posicion = lector.read();
    std::cout << "archivo cero iniciar posicion: " <<  posicion << std::endl;
    if (posicion) {
      std::cout << "archivo cero iniciar entre" << std::endl;
      std::string numero = lector.getText();
      actual = stoi(numero);
    } else {
      std::cerr << "Failed to read file: " << std::strerror(errno) << std::endl;
    }
    lector.close();
  }
} 

int ArchivoCero::getArchivoActual() { return actual; }

bool ArchivoCero::cambiarArchivoActual(std::string path, int numero) {
  std::lock_guard<std::mutex> lock(mutex);
  escritor->open(path + NOMBRE);
  if (actual + 1 == numero) {
    actual++;
    escritor->inicio();
    escritor->write(getFileName());
    escritor->close();
    return true;
  }
  return false;
}

std::string ArchivoCero::getFileName() {
  std::stringstream ss;
  ss << std::setw(6) << std::setfill('0') << actual;
  return ss.str();
}

ArchivoCero::~ArchivoCero() {
  delete escritor;
}
