#ifndef CLIENTE_H
#define CLIENTE_H

#include "Feedback.h"
#include "Socket.h"

class Client {
  public:
    Client(std::string address, int port, Feedback * feedback);
    void send(std::vector<unsigned char>  message);
    void send(std::string  message);
    bool isWorking();
    ~Client();

  private:
    Socket * socket;
    bool working = false;
};

#endif
