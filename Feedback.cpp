#include "Feedback.h"
#include "Escritor.hpp"


Feedback::Feedback() {}

void Feedback::iniciar(std::string path){
  this->path = path;
}

void Feedback::agregarFeedback(std::string mensaje) {
  std::lock_guard<std::mutex> lock(mutex);
  Escritor escritor;
  if (escritor.open(path + FILEF, "a+") == 0) {
    escritor.write(currentDateTime() + ": " + mensaje + "\n");
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
