#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Bitacora.hpp"
#include <chrono>

// Constructor
Bitacora::Bitacora() {
    filename="bitacora.txt";
    ofstream archivo;
}

void Bitacora::add(string entry) {
    ofstream archivo;
    archivo.open(filename.c_str(), fstream::out);
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    archivo << std::ctime(&end_time);
    archivo << entry;
    archivo << endl;
    archivo.close();
    cout << "Escrito correctamente";
}


void Bitacora::open(){
    archivo.open(filename.c_str(), fstream::out);
    cout<< "Se abrió el archivo" <<endl;
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    archivo << std::ctime(&end_time)<< "\n";
    //write(entry);
  }

void Bitacora::write(string entry){
    archivo << entry<<"\n";
  }

void Bitacora::close(){
    archivo.close();
    cout<< "Se cerró el archivo" <<endl;
  }