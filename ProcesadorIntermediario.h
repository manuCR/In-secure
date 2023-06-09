#ifndef PROCESADOR_I_H
#define PROCESADOR_I_H

#include "Client.h"
#include "Procesador.h"

class ProcesadorIntermediario : public Procesador {
  public:
    ProcesadorIntermediario(std::string address, int port, Feedback * feedback, std::string bindIp);
    bool abrir(std::vector<unsigned char>  token, 
               std::vector<unsigned char> enShaFile, std::string shaFile,
               std::vector<unsigned char> enPath, std::string path,
               std::vector<unsigned char> titulo, std::string archivo);
    void enviar(std::vector<unsigned char>  mensaje, Cifrado * cifrado, std::string llave2);
    void enviar(std::string  mensaje);
    ~ProcesadorIntermediario();

  private:
    Client *client;
};

#endif