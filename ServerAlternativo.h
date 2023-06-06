#ifndef SERVER_ALTERNATIVO_H
#define SERVER_ALTERNATIVO_H

#include "Server.h"
#include "Socket.h"

class ServerAlternativo : public Server {
  public:
    ServerAlternativo(std::string tok, std::string llave1, std::string llave2);
    void setSocket(std::string address, int port);
    void iniciarProcesador(std::string address, int port, bool fin, std::string bindIp);
    void iniciarCero(std::string path, bool cdcd);
    void getMessages(int id);
    std::vector<unsigned char> receive(int id);
    void start();
    void stop();
    ~ServerAlternativo();

  private:
    Socket * socket;
    bool working;
};

#endif
