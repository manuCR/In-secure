#include "Client.h"

Client::Client(std::string address, int port) {
  socket = new Socket(address, port);
  socket->connectTo();
}

void Client::send(std::string message) { return socket->send(message); }
void Client::end(std::string message) { return socket->end(); }

Client::~Client() { delete socket; }
