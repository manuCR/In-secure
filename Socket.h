#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class Socket {
public:
  Socket();
  void connectTo(const std::string &address, int port);
  void send(const std::string &message);
  std::string receive(int buffer_size);
  ~Socket();

private:
  int sockfd;
};

#endif
