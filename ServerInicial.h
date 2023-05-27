#ifndef SERVER_INICIAL_H
#define SERVER_INICIAL_H

#include "ArchivoCero.h"
#include "Server.h"
#include <string>

class ServerInicial : public Server {
public:
  ServerInicial(std::string tok);
  void setSocket(std::string address, int port, bool cdcd);
  void iniciarProcesador(std::string address, int port, bool fin);
  void iniciarCero(std::string path);
  void abrirCero();
  void cerrarCero();
  void sendMessages();
  std::string getPath(bool priv);
  void start();
  void stop();
  ~ServerInicial();

private:
  ArchivoCero *ceroPub;
  const static int carpetas = 3;
  const std::string users[carpetas] = {"carpeta1/", "carpeta2/", "carpeta3/"};
  int usersIndex;
};

#endif
