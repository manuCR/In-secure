#include "Escritor.hpp"
#include "Lector.hpp"

// Constructor
Escritor::Escritor() {
}

bool Escritor::open(std::string flname) {
  std::string filename = FULL + flname;
  archivo = fopen(filename.c_str(), "w+");
  if (!archivo) {
    return 1;
  } else {
    perror("Error occurred while opening file.\n");
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
