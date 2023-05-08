#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include <string>

class Server {
public:
  Server(std::string address, int port);
  void getMessages(int id);
  Socket::mess receive(int id, int buffer_size);
  void start();
  void stop();
  ~Server();

private:
  Socket *socket;
  bool active;
};

#endif
