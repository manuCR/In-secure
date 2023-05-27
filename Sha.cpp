#include "Sha.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>

Sha::Sha() {}

std::string Sha::shaFile(std::string filename) {
  std::ifstream file(filename, std::ios::binary);

  if (!file) {
    return "";
  }

    EVP_MD_CTX* mdctx = new EVP_MD_CTX();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    constexpr size_t bufferSize = 4096;
    char buffer[bufferSize];
    while (file.read(buffer, bufferSize)) {
        EVP_DigestUpdate(mdctx, buffer, bufferSize);
    }

    EVP_DigestUpdate(mdctx, buffer, file.gcount());

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLength;
    EVP_DigestFinal_ex(mdctx, digest, &digestLength);

    std::stringstream ss;
    for (unsigned int i = 0; i < digestLength; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    EVP_MD_CTX_free(mdctx);

    return ss.str();
}

Sha::~Sha() {}