#ifndef BITACORA_H
#define BITACORA_H

#include <fstream>
#include <string>


class Bitacora {
  public:
    std::string filename;
    std::ofstream archivo;
    Bitacora();
    void add(std::string entry);

  private:
    void open();
    void write(std::string entry);
    void close();
};
#endif  // BITACORA_H
