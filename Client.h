#ifndef CLIENTE_H
#define CLIENTE_H

#include "Socket.h"
#include <string>

class Client {
public:
  Client(const std::string &address, int port);
  void send(const std::string &message);
  ~Client();

private:
  Socket *socket;
};

#endif
