#include "Lector.hpp"
#include <iostream>
#include <string>

using namespace std;

// Constructor
Lector::Lector() { filename = ""; }

int Lector::open(string flname) {
  filename = "/home/manuel" + flname;
  archivo =
      fopen(filename.c_str(), "rb"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    return 1;
  }
  return 0;
}

int Lector::read() { return fread(buffer, sizeof(char), 1024, archivo); }

std::string Lector::getText() { return string(buffer); }

int Lector::close() {
  fclose(archivo); // cierra el archivo
  return 0;
}
