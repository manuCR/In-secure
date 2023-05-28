#ifndef LECTOR_H
#define LECTOR_H

#include <cstdio>
#include <string>


class Lector {
  public:
    Lector();
    int open(std::string flname) ;
    int read();
    std::string getText();
    int close() ;
  private:
    std::string filename;
    FILE * archivo;
    char * buffer = new char[1024];
};
#endif  // LECTOR_H