#ifndef BITACORA_H
#define BITACORA_H

#include <fstream>
#include <string>


class Bitacora {

 public:
  std::string filename;
  ofstream archivo;

  /**
  * @brief Class constructor.
  */
  Bitacora();

  void add(std::string entry);

  private: 

  void open();

  void write(std::string entry);

  void close();

};
#endif  // BITACORA_H
