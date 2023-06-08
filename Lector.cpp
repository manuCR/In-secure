#include "Lector.hpp"
#include <cstdio>
#include <cstring>

// Constructor
Lector::Lector(Feedback * feedback) { 
  filename = "";
  this->feedback = feedback;
}

int Lector::open(std::string flname) {
  filename = std::string(FULL + flname);
  archivo = fopen(filename.c_str(), "r"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    feedback->agregarFeedback("No se pudo abrir el archivo " + flname);
    return 1;
  }
  return 0;
}

int Lector::openBinari(std::string flname) {
  filename = FULL + flname;
  archivo = fopen(filename.c_str(), "rb"); // abre el archivo Ej: "src/archivo.txt"
  if (!archivo) { // verifica si el archivo se abrió correctamente
    feedback->agregarFeedback("No se pudo abrir el archivo " + flname);
    return 1;
  }
  return 0;
}

int Lector::read(int chunk) {
  memset(buffer, 0, BUFFER);
  return fread(buffer, sizeof(char), chunk, archivo);
}

std::string Lector::readLine() {
  memset(buffer, 0, BUFFER);
  if(fgets(reinterpret_cast<char*>(buffer), 1025, archivo) != NULL){
    return std::string(reinterpret_cast<char*>(buffer));  
  }
  return "";
}

std::string Lector::getText() {
  return std::string(reinterpret_cast<char*>(buffer));
}

unsigned char * Lector::getChars() {
  return buffer;
}

int Lector::close() {
  memset(buffer, 0, BUFFER);
  fclose(archivo); // cierra el archivo
  return 0;
}

long Lector::getPosition() {
  return ftell(archivo);
}

void Lector::setPosition(long position) {
  fseek(archivo, position, SEEK_SET);
}

Lector::~Lector() { 
  delete[] buffer;
}
