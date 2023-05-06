#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Lector.hpp"

// Constructor
Lector::Lector() {
    filename="";
}


  int Lector::open(string flname) {
    filename = flname;
    archivo.open(flname); // abre el archivo Ej: "src/archivo.txt"

    if (!archivo.is_open()) { // verifica si el archivo se abrió correctamente
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }
  return 0;
  }

string Lector::read() {
    std::string str;
    if (std::getline(archivo, str)){
      return str;
    }
    return "";
}

  int Lector::close() {
    archivo.close();  // cierra el archivo
    return 0;
}
