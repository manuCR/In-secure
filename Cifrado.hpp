#ifndef CIFRADO_H
#define CIFRADO_H

#include "Feedback.h"
#include <vector>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>


class Cifrado {

private:
  Feedback * feedback;
  
public:
  Cifrado(Feedback * feedback);
  std::string decryptMessage(std::vector<unsigned char> encryptedMessage, const std::string& privateKeyPath, bool tok);
  std::vector<unsigned char> encryptMessage(const std::string& message, const std::string& publicKeyPath);
  void printError(std::string mensaje, bool tok);
  int chunkSize(const std::string& privateKeyPath);
};
#endif  //CIFRADO_H
