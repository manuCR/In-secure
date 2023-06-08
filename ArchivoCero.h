#ifndef ARCHIVO_CERO_H
#define ARCHIVO_CERO_H

#include "Escritor.hpp"
#include "Feedback.h"
#include <mutex>

#define FILE0 "000000.txt"

class ArchivoCero {

public:
  ArchivoCero(Feedback * feedback);
  void iniciar(std::string path);
  int getArchivoActual();
  bool cambiarArchivoActual(int numero);
  bool restaurarActual(int numero);
  std::string getFileName();
  ~ArchivoCero();

private:
  int actual;
  Escritor * escritor;
  std::mutex mutex;
  std::string path;
  Feedback * feedback;
};
#endif // BITACORA_H
