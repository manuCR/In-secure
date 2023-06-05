#ifndef ESCRITOR_H
#define ESCRITOR_H

#include <string>

class Escritor {
  public:
    Escritor();
    bool open(std::string flname, const char * mode);
    void write(std::string entry);
    void inicio();
    void close();

  private: 
    FILE * archivo;

};
#endif  // ESCRITOR_H