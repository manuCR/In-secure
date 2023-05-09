#include "Socket.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket(std::string address, int port) {
  this->port = port;
  this->address = address;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(address.c_str());
  this->addrlen = sizeof(address);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::connectTo() {
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    std::cerr << "Failed to connect to server: " << std::strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::bindTo() {
  int opt = 1;
  if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) == -1) {
    std::cerr << "Failed to connect to server: " << std::strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }

  if (listen(sockfd, 3) == -1) {
    std::cerr << "Failed to listen to server: " << std::strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

int Socket::acceptConection() {
  int socket =
      accept(sockfd, (struct sockaddr *)&server_addr, (socklen_t *)&addrlen);
  if (socket == -1) {
    std::cerr << "Failed to accept to server: " << std::strerror(errno)
              << std::endl;
    return -1;
  }
  return socket;
}

void Socket::send(std::string message) {
  if (::send(sockfd, message.c_str(), message.size(), 0) == -1) {
    std::cerr << "Failed to send message: " << std::strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

Socket::mess Socket::receive(int socket, int buffer_size) {
  char buffer[buffer_size];
  mess comunication;
  if (read(socket, buffer, buffer_size) == -1) {
    std::cerr << "Failed to receive message: " << std::strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }
  if (buffer[0] == 0) {
    comunication.end = true;
    comunication.mes = std::string();
  } else {
    comunication.end = false;
    comunication.mes = std::string(buffer);
  }
  return comunication;
}

Socket::~Socket() { close(sockfd); }
