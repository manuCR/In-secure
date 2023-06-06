#ifndef PROCESADOR_I_H
#define PROCESADOR_I_H

#include "Client.h"
#include "Procesador.h"

class ProcesadorIntermediario : public Procesador {
  public:
    ProcesadorIntermediario(std::string address, int port, Feedback * feedback, std::string bindIp);
    bool abrir(std::vector<unsigned char>  token, std::string shaFile, std::string path,
               std::string archivo, std::vector<unsigned char> titulo);
    void enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2);
    ~ProcesadorIntermediario();

  private:
    Client *client;
};

#endif