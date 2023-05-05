#ifndef ESCRITOR_H
#define ESCRITOR_H

#include <fstream>
#include <string>


class Escritor {

 public:
  std::string filename;
  std::ofstream archivo;

  /**
  * @brief Class constructor.
  */
  Escritor();

  void add(std::string entry, std::string flname) ;

  private: 

  void open(std::string flname);

  void write(std::string entry);

  void close();

};
#endif  // ESCRITOR_H