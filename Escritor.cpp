#include "Escritor.hpp"
#include "Lector.hpp"

// Constructor
Escritor::Escritor() {
}

bool Escritor::open(std::string flname, const char * mode) {
  std::string filename = FULL + flname;
  archivo = fopen(filename.c_str(), mode);
  if (!archivo) {
    return 1;
  }
  return 0;
}

void Escritor::write(std::string entry) {
  std::fputs(entry.c_str(), archivo);
}

void Escritor::close() {
  fclose(archivo);
}
