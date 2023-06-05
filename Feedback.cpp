#include "Feedback.h"
#include "Escritor.hpp"
#include <iostream>


Feedback::Feedback(std::string path) {
  this->path = path;
}

void Feedback::agregarFeedback(std::string mensaje) {
  std::lock_guard<std::mutex> lock(mutex);
  std::cout << mensaje << std::endl;
  Escritor escritor;
  std::cout << "1" << std::endl;
  std::cout << path + FILEF << std::endl;
  if (escritor.open(path + FILEF) == 0) {
    std::cout << "1" << std::endl;
    escritor.write(currentDateTime() + ": " + mensaje);
    std::cout << "2" << std::endl;
    escritor.close();
  }
  
}




std::string Feedback::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

Feedback::~Feedback() {}
