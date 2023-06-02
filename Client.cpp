#include "Client.h"
#include <vector>

Client::Client(std::string address, int port) {
  socket = new Socket(address, port);
  socket->connectTo();
}

void Client::send(std::vector<unsigned char> message) { return socket->send(message); }

void Client::send(std::string message) { return socket->send(message); }

Client::~Client() { delete socket; }
