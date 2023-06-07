#include "Sha.h"
#include "Lector.hpp"
#include <iomanip>
#include <sstream>


Sha::Sha(Feedback * feedback) {
  this->feedback = feedback;
}

int Sha::start() {
  mdCtx = EVP_MD_CTX_create();
  if (!EVP_DigestInit_ex(mdCtx, EVP_sha256(), NULL)) {
    feedback->agregarFeedback("Message digest initialization failed.");
    EVP_MD_CTX_destroy(mdCtx);
    return -1;
  }
  return 0;
}

int Sha::add(const unsigned char * str, int len) {
  if (!EVP_DigestUpdate(mdCtx, str, len)) {
    feedback->agregarFeedback("Message digest update failed.");
    EVP_MD_CTX_destroy(mdCtx);
    return -1;
  }
  return 0;
}

std::string Sha::finish() {
  if (!EVP_DigestFinal_ex(mdCtx, mdVal, &mdLen)) {
    feedback->agregarFeedback("Message digest finalization failed.");
    EVP_MD_CTX_destroy(mdCtx);
    return std::string("");
  }
  EVP_MD_CTX_destroy(mdCtx);

  std::stringstream ss;
  for (int i = 0; i < mdLen; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(mdVal[i]);
  }

  return ss.str();
}

std::string Sha::shaFile(std::string filename) {
  Lector lector(feedback);
  if(lector.openBinari(filename) == 0) {
    int noError = start();
    int read = lector.read(512);
    while (read > 0 && noError == 0) {
      noError = add(lector.getChars(), read);
      read = lector.read(512);
    }
    lector.close();
    return finish();
  }
  return std::string("");
}

Sha::~Sha() {}