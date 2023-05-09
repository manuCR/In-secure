#ifndef CLIENTE_H
#define CLIENTE_H

#include "Socket.h"
#include <string>

class Client {
public:
  Client(std::string address, int port);
  void send(std::string message);
  void end();
  ~Client();

private:
  Socket *socket;
};

#endif
