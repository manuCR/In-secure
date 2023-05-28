#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <string>
#include <vector>
class Socket {
public:

  Socket(std::string address, int port);
  void connectTo();
  void bindTo();
  void send(std::vector<unsigned char> message);
  void send(std::string message);

  int acceptConection();
  std::vector<unsigned char> receive(int socket);
  ~Socket();

private:
  int sockfd, port, addrlen;
  std::string address;
  struct sockaddr_in server_addr;
};

#endif
