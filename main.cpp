#include "Client.h"
#include "Lector.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

int main() {
  Lector *lector = new Lector();
  Client *client = new Client("172.24.3.83", 8283);
  lector->open("enviar.txt");
  std::string texto = "";
  std::string temp = "";
  while (lector->read() > 0) {
    temp = lector->getText();
    client->send(temp);
    texto += temp;
  }
  lector->close();
  delete client;
  std::cout << "lectura final:" << std::endl << texto << std::endl;
  delete lector;
  return 0;
}
