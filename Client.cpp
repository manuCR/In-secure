#include "Client.h"

Client::Client(std::string address, int port, Feedback * feedback, std::string bindIp) {
  this->address = address;
  this->port = port;
  this->feedback = feedback;
  this->bindIp = bindIp;
}

void Client::connect() {
  socket = new Socket(address, port, feedback);
  working = socket->bindTo(bindIp);
  working = socket->connectTo();
}

void Client::disconnect() {
  working =false;
  delete socket;
}

void Client::send(std::vector<unsigned char> message) {
  return socket->send(message);
}

void Client::send(std::string message) {
  return socket->send(message);
}

Client::~Client() {
  delete socket;
}
