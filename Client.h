#ifndef CLIENTE_H
#define CLIENTE_H

#include "Socket.h"
#include <string>
#include <vector>

class Client {
  public:
    Client(std::string address, int port);
    void send(std::vector<unsigned char>  message);
    void send(std::string  message);
    ~Client();

  private:
    Socket *socket;
};

#endif
