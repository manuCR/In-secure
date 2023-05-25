#ifndef SERVER_ALTERNATIVO_H
#define SERVER_ALTERNATIVO_H

#include "ArchivoCero.h"
#include "Server.h"
#include "Socket.h"
#include <string>

class ServerAlternativo : public Server {
public:
  ServerAlternativo(std::string tok);
  void setSocket(std::string address, int port, bool cdcd);
  void iniciarProcesador(std::string address, int port, bool fin);
  void iniciarCero(std::string path);
  void getMessages(int id);
  Socket::mess receive(int id);
  void start();
  void stop();
  ~ServerAlternativo();

private:
  Socket *socket;
};

#endif
