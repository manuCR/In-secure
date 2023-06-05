#include "Feedback.h"
#include "Escritor.hpp"
#include <iomanip>
#include <sstream>

Feedback::Feedback(std::string path) {
  this->path = path;
}

void Feedback::agregarFeedback(std::string mensaje) {
  std::lock_guard<std::mutex> lock(mutex);
  Escritor escritor;
  escritor.open(path + FILEF);
  time_t now = time(nullptr);
  std::stringstream formatted_time;
  formatted_time << std::put_time(std::localtime(&now), "%F %T");
  escritor.write(formatted_time.str() + ": " + mensaje);
  escritor.close();
}

Feedback::~Feedback() {}
