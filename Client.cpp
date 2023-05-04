#include "Client.h"

Client::Client(const std::string &address, int port) {
  socket = new Socket();
  socket->connectTo(address, port);
}

void Client::send(const std::string &message) { return socket->send(message); }

Client::~Client() { delete socket; }
