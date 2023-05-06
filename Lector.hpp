#ifndef LECTOR_H
#define LECTOR_H

#include <fstream>
#include <string>


class Lector {

 public:
  std::string filename;
  std::ifstream archivo;

  /**
  * @brief Class constructor.
  */
  Lector();

  int open(std::string flname) ;
  std::string read() ;
  int close() ;


};
#endif  // LECTOR_H