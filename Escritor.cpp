#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Escritor.hpp"
#include <chrono>

// Constructor
Escritor::Escritor() {
    filename="";
    ofstream archivo;
}

void Escritor::add(string entry, string flname) {
    ofstream archivo;
    filename=flname;
    archivo.open(filename.c_str(), fstream::out);
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    archivo << std::ctime(&end_time);
    archivo << entry;
    archivo << endl;
    archivo.close();
    cout << "Escrito correctamente";
}


void Escritor::open(string flname){
    filename=flname;
    archivo.open(filename.c_str(), fstream::out);
    cout<< "Se abrió el archivo" <<endl;
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    archivo << std::ctime(&end_time)<< "\n";
    //write(entry);
  }

void Escritor::write(string entry){
    archivo << entry<<"\n";
  }

void Escritor::close(){
    archivo.close();
    cout<< "Se cerró el archivo" <<endl;
  }
