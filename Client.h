#ifndef CLIENTE_H
#define CLIENTE_H

#include "Feedback.h"
#include "Socket.h"

class Client {
  public:
    Client(std::string address, int port, Feedback * feedback, std::string bindIp);
    void send(std::vector<unsigned char>  message);
    void send(std::string  message);
    bool isWorking();
    void connect();
    void disconnect();
    ~Client();

  private:
    Socket * socket;
    std::string address;
    int port;
    Feedback * feedback;
    std::string bindIp;
    bool working = false;
};

#endif
