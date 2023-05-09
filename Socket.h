#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <string>

class Socket {
public:
  struct mess {
    bool end;
    std::string mes;
  };
  Socket(std::string address, int port);
  void connectTo();
  void bindTo();
  void send(std::string message);
  void end();
  int acceptConection();
  mess receive(int socket, int buffer_size);
  ~Socket();

private:
  int sockfd, port, addrlen;
  std::string address;
  struct sockaddr_in server_addr;
};

#endif
