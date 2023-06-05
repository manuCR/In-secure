#ifndef ARCHIVO_CERO_H
#define ARCHIVO_CERO_H

#include "Escritor.hpp"
#include "Feedback.h"
#include <mutex>

const char * const FILE0 = "000000.txt";

class ArchivoCero {

public:
  ArchivoCero(Feedback * feedback);
  void iniciar(std::string pato);
  int getArchivoActual();
  bool cambiarArchivoActual(std::string path, int numero);
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
