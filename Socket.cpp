#include "Socket.h"
#include <cstring>
#include <unistd.h>
#include <vector>

Socket::Socket(std::string address, int port, Feedback * feedback) {
  this->feedback = feedback;
  this->port = port;
  this->address = address;
  this->server_addr.sin_family = AF_INET;
  this->server_addr.sin_port = htons(port);
  this->server_addr.sin_addr.s_addr = inet_addr(address.c_str());
  this->addrlen = sizeof(server_addr);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    feedback->agregarFeedback("Failed to create socket");
  }
}

bool Socket::connectTo() {
  if (sockfd == -1) {
    return false;
  }
  int result =  connect(sockfd, (struct sockaddr *)&server_addr, addrlen);
  if ( result == -1) {
    feedback->agregarFeedback("Failed to connect socket");
  }
  return result != -1;
}

bool Socket::bindTo(std::string address) {
  if (sockfd == -1) {
    return false;
  }
  int result = 0;
  if (address.size() > 0){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = inet_addr(address.c_str());
    int len = sizeof(server_addr);
    result = bind(sockfd, (struct sockaddr *)&addr, len);
  } else {
    result = bind(sockfd, (struct sockaddr *)&server_addr, addrlen);
  }  
  if ( result == -1) {
    feedback->agregarFeedback("Failed to bind");
  }
  return result != -1;
}

bool Socket::listen() {
  if (sockfd == -1) {
    return false;
  }
  int result = ::listen(sockfd, 3);
  if ( result == -1) {
    feedback->agregarFeedback("Failed to listen to server");
  }
  return result != -1;
}


int Socket::acceptConection() {
  int socket = accept(sockfd, (struct sockaddr *)&server_addr, (socklen_t *)&addrlen);
  if (socket == -1) {
    feedback->agregarFeedback("Failed to accept to server");
    return -1;
  }
  return socket;
}

void Socket::send(std::vector<unsigned char> message) {
  int len = 512;
  ::send(sockfd, &len, sizeof(len), 0);
  if (::send(sockfd, &message[0], len, 0) == -1) {
    feedback->agregarFeedback("Failed to send message");
  }
}

void Socket::send(std::string message) {
  int len = message.length();
  ::send(sockfd, &len, sizeof(len), 0);
  if (::send(sockfd, message.c_str(), len, 0) == -1) {
    feedback->agregarFeedback("Failed to send message");
  }
}

std::vector<unsigned char> Socket::receive(int socket) {
  int len = 0;
  recv(socket, &len, sizeof(len), 0);
  if (len > 512 || len <= 0) {
    return std::vector<unsigned char>(0);
  }
  std::vector<unsigned char> mes{std::vector<unsigned char>(512)};
  unsigned char buffer[512] = { 0 };
  if (recv(socket, buffer, len, 0) == -1) {
    feedback->agregarFeedback("Failed to receive message");
  }
  memcpy(&mes[0], buffer, len);
  return mes;
}

Socket::~Socket() {
  close(sockfd);
}
