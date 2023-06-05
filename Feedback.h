#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>
#include <mutex>

const char * const FILEF = "feedback.txt";

class Feedback {

private:
  std::string path;
  std::mutex mutex;

public:
  Feedback(std::string path);
  void agregarFeedback(std::string mensaje);
  std::string currentDateTime();
  ~Feedback();
};
#endif // BITACORA_H
