#ifndef SERVER_H
#define SERVER_H

#include "ArchivoCero.h"
#include "ProcesadorIntermediario.h"
#include <string>

class Server {
protected:
  bool active;
  bool cdcd;
  std::string priv;
  std::string token;
  ArchivoCero *ceroPriv;
  Procesador *procesador;

public:
  virtual void setSocket(std::string address, int port, bool cdcd) = 0;
  virtual void iniciarProcesador(std::string address, int port, bool fin) = 0;
  virtual void iniciarCero(std::string path) = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual ~Server(){};
};

#endif
