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
  std::string temp = lector->read();
  while(temp.length() > 0){
    texto += temp;
    client->send(temp);
    temp = lector->read();
  }
  client->end();
  lector->close();
  delete client;
  std::cout << "lectura final:" << texto << std::endl;
  delete lector;
  return 0;
}
