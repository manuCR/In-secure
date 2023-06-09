#include "Server.h"
#include "ServerAlternativo.h"
#include "ServerInicial.h"
#include <thread>

int main(int argc, char *argv[]) {
  bool arg1 = atoi(argv[1]);
  bool arg2 = atoi(argv[2]);
  std::string arg3 = argv[3];
  int arg4 = atoi(argv[4]);
  std::string arg5 = argv[5];
  int arg6 = atoi(argv[6]);
  bool arg7 = atoi(argv[7]);
  std::string arg8 = argv[8];
  std::string arg9 = argv[9];
  std::string arg10 = argv[10];
  std::string arg11 = argv[11];
  if (arg1 && arg2) {
    return 0;
  }
  Server *server;
  if (arg1) {
    server = new ServerInicial(arg9, arg10, arg11);
  } else {
    server = new ServerAlternativo(arg9, arg10, arg11);
  }
  server->iniciarCero(arg8, arg7);
  server->setSocket(arg3, arg4);
  server->iniciarProcesador(arg5, arg6, arg2, arg3);
  server->start();
  delete server;
  return 0;
}
