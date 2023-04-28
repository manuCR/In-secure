#ifndef BITACORA_H
#define BITACORA_H

#include <fstream>
#include <string>


class Bitacora {

 public:
  std::string filename;

  /**
  * @brief Class constructor.
  */
  Bitacora();

  void add(std::string entry);


};
#endif  // BITACORA_H
