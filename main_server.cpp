#include "Server.h"
#include <cstring>
#include <iostream>
#include <thread>
#include <unistd.h>

int main() {
  Server *server = new Server("172.31.128.46", 8283);
  std::string response = server->receive(1024);
  new std::thread(&Server::start, server);
  getchar();
  server->stop();
  delete server;
  return 0;
}