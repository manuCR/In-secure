#ifndef SHA_H
#define SHA_H

#include <string>

class Sha {
  public:
    Sha();
    std::string shaFile(std::string fileName);
    ~Sha();
};

#endif
