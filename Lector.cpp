#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Lector.hpp"

// Constructor
Lector::Lector() {
    filename="";
    ifstream archivo;
}

int Lector::read(string flname) {
    std::ifstream archivo(flname); // abre el archivo Ej: "archivo.txt"

    if (!archivo.is_open()) { // verifica si el archivo se abrió correctamente
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }

    const int n = 100; // cantidad de caracteres a enviar del mensaje por socket
    
    char buffer[n + 1] = {0}; // crea un buffer para almacenar los caracteres leídos

    while (archivo.read(buffer, n)) { // lee n caracteres del archivo
        std::string sms(buffer); // convierte los caracteres leídos en una cadena
        //deberia llamar a la caja negra para que cifre la linea.
        //debe enviar la linea por un socket.         
        std::cout << sms << std::endl; // imprime el mensaje en la consola
        std::fill(buffer, buffer + n + 1, 0); // limpia el buffer
    }

    if (archivo.gcount() > 0) { // verifica si quedan caracteres por leer
        std::string sms(buffer, archivo.gcount()); // convierte los caracteres leídos en una cadena
        std::cout << sms << std::endl; // imprime la última parte del archivo en la consola
    }

    archivo.close();  // cierra el archivo
    return 0;
}


int Lector::open(string flname){
    std::ifstream archivo(flname); // abre el archivo Ej: "archivo.txt"

    if (!archivo.is_open()) { // verifica si el archivo se abrió correctamente
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return 1;
    }
    return 0;
  }

void Lector::reader(string entry){
    std::string linea;
    while (std::getline(archivo, linea)) { // lee cada línea del archivo
        //deberia llamar a la caja negra para que cifre la linea.
        //debe enviar la linea por un socket. 
        std::cout << linea << std::endl; // imprime la línea en la consola
        
    }
  }

void Lector::close(){
    archivo.close(); // cierra el archivo
    cout<< "Se cerró el archivo" <<endl;
  }
