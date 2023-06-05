#ifndef SHA_H
#define SHA_H

#include "Feedback.h"
#include <openssl/evp.h>

class Sha {
  public:
    Sha(Feedback * feedback);
    std::string shaFile(std::string fileName);
    int start();
    int add(const unsigned char * str, int len);
    std::string finish();
    ~Sha();
  private:
    EVP_MD_CTX *mdCtx;
    unsigned char mdVal[EVP_MAX_MD_SIZE], *md;
    unsigned int mdLen;
    Feedback * feedback;
};

#endif
