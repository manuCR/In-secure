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

  private: 

  int open(std::string flname);

  void reader(std::string entry);

  void close();

};
#endif  // LECTOR_H