#ifndef CIFRADO_H
#define CIFRADO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>


class Cifrado {

public:
  Cifrado();
  std::string decryptMessage(char*  message, const std::string& privateKeyPath);
  void encryptMessage(const std::string& message, const std::string& publicKeyPath, char * result);



};
#endif  //CIFRADO_H