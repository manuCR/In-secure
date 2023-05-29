#include "Sha.h"
#include "Lector.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>


Sha::Sha() {}

int Sha::start() {
  mdCtx = EVP_MD_CTX_new();
  if (!EVP_DigestInit_ex(mdCtx, EVP_sha256(), NULL)) {
    printf("Message digest initialization failed.\n");
    EVP_MD_CTX_free(mdCtx);
    return -1;
  }
  return 0;
}

int Sha::add(const unsigned char * str, int len) {
  if (!EVP_DigestUpdate(mdCtx, str, len)) {
    printf("Message digest update failed.\n");
    EVP_MD_CTX_free(mdCtx);
    return -1;
  }
  return 0;
}

std::string Sha::finish() {
  if (!EVP_DigestFinal_ex(mdCtx, mdVal, &mdLen)) {
    printf("Message digest finalization failed.\n");
    EVP_MD_CTX_free(mdCtx);
    return std::string("");
  }
  EVP_MD_CTX_free(mdCtx);

  std::stringstream ss;
  for (int i = 0; i < mdLen; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(mdVal[i]);
  }

  return ss.str();
}

std::string Sha::shaFile(std::string filename) {
  Lector lector;
  if(lector.openBinari(filename) == 0) {
    int noError = start();
    int read = lector.read();
    while (read > 0 && noError == 0) {
      noError = add(lector.getChars(), read);
      read = lector.read();
    }
    lector.close();
    return finish();
  }
  return std::string("");
}

Sha::~Sha() {}