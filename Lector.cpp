#include "Lector.hpp"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Constructor
Lector::Lector() { filename = ""; }

int Lector::open(string flname) {
  filename = "/home/manuel.arroyoportilla" + flname;
  std::cout << "lector filename: " <<  filename << std::endl;
  archivo = fopen(filename.c_str(), "r"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    return 1;
  }
  return 0;
}

int Lector::read() { 
  memset(buffer, 0, 512);
  return fread(buffer, sizeof(char), 470, archivo);
}

std::string Lector::getText() { return string(buffer); }

int Lector::close() {
  fclose(archivo); // cierra el archivo
  return 0;
}
