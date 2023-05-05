#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include <string>

class Server {
public:
  Server(const std::string &address, int port);
  std::string receive(int buffer_size);
  ~Server();

private:
  Socket *socket;
};

#endif
