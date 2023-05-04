#include "Socket.h"
#include <cstring>
#include <iostream>

int main() {
  Socket socket;
  socket.connectTo("127.0.0.1", 8283);
  std::cout << "Connected to server" << std::endl;
  socket.send("Hello, server!");
  std::string response = socket.receive(1024);
  std::cout << "Server response: " << response << std::endl;
  return 0;
}