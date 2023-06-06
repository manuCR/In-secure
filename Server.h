#ifndef SERVER_H
#define SERVER_H

#include "ArchivoCero.h"
#include "Procesador.h"

class Server {
  protected:
    bool active;
    bool cdcd;
    std::string llave1;
    std::string llave2;
    std::string priv;
    std::string token;
    ArchivoCero *ceroPriv;
    Procesador *procesador;
    Feedback * feedback;

  public:
    virtual void setSocket(std::string address, int port) = 0;
    virtual void iniciarProcesador(std::string address, int port, bool fin, std::string bindIp) = 0;
    virtual void iniciarCero(std::string path, bool fin) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Server(){};
};

#endif
