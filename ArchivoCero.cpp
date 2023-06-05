#include "ArchivoCero.h"
#include "Lector.hpp"
#include <iomanip>
#include <sstream>
#include <string>


ArchivoCero::ArchivoCero(Feedback * feedback) {
  this->feedback = feedback;
  actual = 0;
  escritor = new Escritor();
}

void ArchivoCero::iniciar(std::string path) {
  this->path = path;
  Lector lector(feedback);
  std::string full = path + FILE0;
  if(lector.open(full) == 0){
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
  escritor->open(path + FILE0);
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
