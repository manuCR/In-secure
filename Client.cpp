#include "Client.h"

Client::Client(std::string address, int port, Feedback * feedback, std::string bindIp) {
  socket = new Socket(address, port, feedback);
  working = socket->bindTo(bindIp);
}

void Client::send(std::vector<unsigned char> message) {
  socket->connectTo();
  return socket->send(message);
}

void Client::send(std::string message) {
  socket->connectTo();
  return socket->send(message);
}

bool Client::isWorking() {
  return working;
}

Client::~Client() {
  delete socket;
}
