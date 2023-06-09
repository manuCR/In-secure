#ifndef LECTOR_H
#define LECTOR_H

#include "Feedback.h"

#define FULL "/home/valery.murcia"
#define BUFFER 2048

class Lector {
  public:
    Lector(Feedback * feedback);
    int open(std::string flname) ;
    int openBinari(std::string flname) ;
    int read(int chunk);
    std::string getText();
    std::string readLine();
    unsigned char * getChars();
    int close() ;
    long getPosition();
    void setPosition(long position);
    ~Lector();
  private:
    std::string filename;
    FILE * archivo;
    unsigned char * buffer = new unsigned char[BUFFER];
    Feedback * feedback;
};
#endif  // LECTOR_H