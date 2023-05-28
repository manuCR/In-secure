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
  std::string decryptMessage(const unsigned char*  message, const std::string& privateKeyPath);
  std::string encryptMessage(const std::string& message, const std::string& publicKeyPath);



};
#endif  //CIFRADO_H