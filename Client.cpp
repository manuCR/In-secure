#include "Client.h"

Client::Client(std::string address, int port, Feedback * feedback) {
  socket = new Socket(address, port, feedback);
  working = socket->connectTo();
}

void Client::send(std::vector<unsigned char> message) {
  return socket->send(message);
}

void Client::send(std::string message) {
  return socket->send(message);
}

bool Client::isWorking() {
  return working;
}

Client::~Client() { delete socket; }
