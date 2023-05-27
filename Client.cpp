#include "Client.h"
#include <iostream>

Client::Client(std::string address, int port) {
  socket = new Socket(address, port);
  std::cout << "Cliente" << address << " " << port << std::endl;
  socket->connectTo();
}

void Client::send(std::string message) { return socket->send(message); }

Client::~Client() { delete socket; }
