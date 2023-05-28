#ifndef CIFRADO_H
#define CIFRADO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>


class Cifrado {

public:
  Cifrado();
  std::string decryptMessage(std::vector<unsigned char> encryptedMessage, const std::string& privateKeyPath);
  void encryptMessage(const std::string& message, const std::string& publicKeyPath, std::vector<unsigned char> result);

};
#endif  //CIFRADO_H