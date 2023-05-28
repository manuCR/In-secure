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
  this->addrlen = sizeof(server_addr);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::connectTo() {
  if (connect(sockfd, (struct sockaddr *)&server_addr, addrlen) ==
      -1) {
    std::cerr << "Failed to connect to server: " << std::strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Socket::bindTo() {
  int opt = 1;
  if (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) == -1) {
    std::cerr << "Failed to bind to server: " << std::strerror(errno)
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
  int socket = accept(sockfd, (struct sockaddr *)&server_addr, (socklen_t *)&addrlen);
  if (socket == -1) {
    std::cerr << "Failed to accept to server: " << std::strerror(errno)
              << std::endl;
    return -1;
  }
  return socket;
}

void Socket::send(std::string message) {
  int len = message.length();
  ::send(sockfd, &len, sizeof(len), 0);
  std::cout << "socket send length: " << len << " message length: " << message.length() << std::endl;
  if (::send(sockfd, message.c_str(), len, 0) == -1) {
    std::cerr << "Failed to send message: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
}

Socket::mess Socket::receive(int socket) {
  int len = 0;
  recv(socket, &len, sizeof(len), 0);
  char buffer[512] = { 0 };
  mess comunication;
  if (recv(socket, buffer, len, 0) == -1) {
    std::cerr << "Failed to receive message: " << std::strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }
  strncpy(buffer, comunication.mes, len);
  std::cout << "socket receive length: " << len << std::endl;
  if (len > 0) {
    comunication.end = false;
  } else {
    comunication.end = true;
  }
  return comunication;
}

Socket::~Socket() { close(sockfd); }
