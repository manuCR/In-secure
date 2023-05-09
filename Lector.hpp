#ifndef LECTOR_H
#define LECTOR_H

#include <cstdio>
#include <string>


class Lector {

 public:
  std::string filename;
  FILE * archivo;
  char * buffer = new char[1024];

  /**
  * @brief Class constructor.
  */
  Lector();

  int open(std::string flname) ;
  int read();
  std::string getText();
  int close() ;


};
#endif  // LECTOR_H