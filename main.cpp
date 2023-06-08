#include "Server.h"
#include "ServerAlternativo.h"
#include "ServerInicial.h"
#include <thread>

// 1:inicial(bool), 2:final(bool), 3:ipServer(string), 4:puertoServer(int),
// 5:ipCliente(string), 6:puertoCliente(int), 7: CDCD(bool), 
// 8: cero privados(string), 9: token(string), 10: llave tok(string)
// 11: llave archivos(string)
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
  // vamos a manejar los canales con dos procesos separados
  // canales?
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
  new std::thread(&Server::start, server); // quitar el thread para que corra en el systemd
  delete server;
  return 0;
}
