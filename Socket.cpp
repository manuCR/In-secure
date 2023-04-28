#include "Socket.h"
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket() {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::connectTo(const std::string &address, int port) {
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(address.c_str());

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    std::cerr << "Failed to connect to server" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::send(const std::string &message) {
  if (::send(sockfd, message.c_str(), message.size(), 0) == -1) {
    std::cerr << "Failed to send message" << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::string Socket::receive(int buffer_size) {
  char buffer[buffer_size];
  if (recv(sockfd, buffer, buffer_size, 0) == -1) {
    std::cerr << "Failed to receive message" << std::endl;
    exit(EXIT_FAILURE);
  }
  return std::string(buffer);
}

Socket::~Socket() { close(sockfd); }
