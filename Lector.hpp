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

  int read(std::string flname) ;


};
#endif  // LECTOR_H