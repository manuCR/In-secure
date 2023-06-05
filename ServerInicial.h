#ifndef SERVER_INICIAL_H
#define SERVER_INICIAL_H

#include "Server.h"

class ServerInicial : public Server {
  public:
    ServerInicial(std::string tok, std::string llave1, std::string llave2);
    void setSocket(std::string address, int port);
    void iniciarProcesador(std::string address, int port, bool fin);
    void iniciarCero(std::string path, bool cdcd);
    void abrirCero();
    void cerrarCero();
    void sendMessages();
    std::string getPath(bool priv);
    void start();
    void stop();
    ~ServerInicial();

  private:
    ArchivoCero *ceroPub;
    const static int carpetas = 10;
    const std::string users[10] = {"cesar", "fabian", "jeremy", "leonel", "maeva", "manuel", "mariana", "nayeri", "rodrigo", "sofia"};
    int usersIndex;
};

#endif
