#include "Lector.hpp"
#include <iostream>
#include <string>

using namespace std;

// Constructor
Lector::Lector() { filename = ""; }

int Lector::open(string flname) {
  filename = "/home/manuel.arroyoportilla" + flname;
  archivo = fopen(filename.c_str(), "r"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    return 1;
  }
  rewind(archivo);
  return 0;
}

int Lector::read() { 
  buffer = {0};
  return fread(buffer, sizeof(char), 470, archivo);
}

std::string Lector::getText() { return string(buffer); }

int Lector::close() {
  fclose(archivo); // cierra el archivo
  return 0;
}
