#ifndef LECTOR_H
#define LECTOR_H

#include "Feedback.h"

class Lector {
  public:
    Lector(Feedback * feedback);
    int open(std::string flname) ;
    int openBinari(std::string flname) ;
    int read();
    std::string getText();
    unsigned char * getChars();
    int close() ;
  private:
    std::string filename;
    FILE * archivo;
    unsigned char * buffer = new unsigned char[512];
    Feedback * feedback;
};
#endif  // LECTOR_H