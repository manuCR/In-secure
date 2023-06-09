#ifndef SOCKET_H
#define SOCKET_H

#include "Feedback.h"
#include <arpa/inet.h>
#include <vector>

class Socket {
  public:
    Socket(std::string address, int port, Feedback * feedback);
    bool connectTo();
    bool bindTo(std::string address);
    bool listen();
    void send(std::vector<unsigned char> message);
    void send(std::string message);
    int acceptConection();
    std::vector<unsigned char> receive(int socket);
    void end(int socket);
    ~Socket();

  private:
    Feedback * feedback;
    int sockfd, port, addrlen;
    std::string address;
    struct sockaddr_in server_addr;
};

#endif
