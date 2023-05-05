#include "Socket.h"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <cstdlib>
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
    std::cerr << "Failed to connect to server: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::bindTo(const std::string &address, int port) {
  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    std::cerr << "Failed to reuse the port" << std::endl;
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(address.c_str());
  int addrlen = sizeof(server_addr);

  if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) == -1) {
    std::cerr << "Failed to connect to server: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, 3) == -1) {
    std::cerr << "Failed to listen to server: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
  new_socket =
      accept(sockfd, (struct sockaddr *)&server_addr, (socklen_t *)&addrlen);
  if (new_socket == -1) {
    std::cerr << "Failed to accept to server: " << std::strerror(errno) << std::endl;
  }
}

void Socket::send(const std::string &message) {
  if (::send(sockfd, message.c_str(), message.size(), 0) == -1) {
    std::cerr << "Failed to send message: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::string Socket::receive(int buffer_size) {
  char buffer[buffer_size];
  if (read(new_socket, buffer, buffer_size) == -1) {
    std::cerr << "Failed to receive message: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
  return std::string(buffer);
}

Socket::~Socket() { close(sockfd); }
