#ifndef LECTOR_H
#define LECTOR_H

#include <cstdio>
#include <string>


class Lector {
  public:
    Lector();
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
};
#endif  // LECTOR_H