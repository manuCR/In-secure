#include "Escritor.hpp"
#include "Lector.hpp"

// Constructor
Escritor::Escritor() {
}

bool Escritor::open(std::string flname) {
  std::string filename = "/home/manuel.arroyoportilla" + flname;
  archivo = fopen(filename.c_str(), "w");
  if (!archivo) {
    perror("Error occurred while opening file.\n");
    return 1;
  }
  return 0;
}

void Escritor::inicio() {
  rewind(archivo);
}

void Escritor::write(std::string entry) {
  std::fputs(entry.c_str(), archivo);
}

void Escritor::close() {
  fclose(archivo);
}
