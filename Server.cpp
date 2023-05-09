#include "Server.h"
#include <iostream>
#include <thread>

Server::Server(std::string address, int port) {
  socket = new Socket(address, port);
  socket->bindTo();
  active = false;
}

void Server::start() {
  active = true;
  std::thread *worker;
  while (active) {
    int id = socket->acceptConection();
    worker = new std::thread(&Server::getMessages, this, id);
  }
}

void Server::stop() { active = false; }

void Server::getMessages(int id) {
  Socket::mess message = receive(id);
  std::string texto = "";
  while (!message.end) {
    texto += message.mes;
    message = receive(id);
  }
  std::cout << "lectura final:" << texto << std::endl;
}

Socket::mess Server::receive(int id) {
  return socket->receive(id);
}

Server::~Server() { delete socket; }
