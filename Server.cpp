#include "Server.h"

Server::Server(const std::string &address, int port) {
  socket = new Socket();
  socket->bindTo(address, port);
}

std::string Server::receive(int buffer_size) {
  return socket->receive(buffer_size);
}

Server::~Server() { delete socket; }
