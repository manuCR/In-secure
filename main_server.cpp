#include "Server.h"
#include <cstring>
#include <iostream>
#include <thread>
#include <unistd.h>

int main() {
  Server *server = new Server("172.24.3.83", 8283);
  new std::thread(&Server::start, server);
  getchar();
  server->stop();
  delete server;
  return 0;
}