#ifndef SERVER_INICIAL_H
#define SERVER_INICIAL_H

#include "Server.h"
#include "Lector.hpp"

class ServerInicial : public Server {
  public:
    ServerInicial(std::string tok, std::string llave1, std::string llave2);
    void setSocket(std::string address, int port);
    void iniciarProcesador(std::string address, int port, bool fin, std::string bindIp);
    void iniciarCero(std::string path, bool cdcd);
    void abrirCero();
    void cerrarCero();
    void sendMessages();
    void start();
    void stop();
    ~ServerInicial();

  private:
    ArchivoCero *ceroPub;
    Lector * lector;
    const static int carpetas = 10;
    std::string pathPublico = "";
    std::string pathPrivado = "";
    int usersIndex;
    std::string shaFile;
    const std::string users[10] = {"cesar", "fabian", "jeremy", "leonel", "maeva", "manuel", "mariana", "nayeri", "rodrigo", "sofia"};
    std::string getPath();
    bool autenticar(Lector * lector);
    bool isCDCD(std::string titulo);
    void sleep();
};

#endif
