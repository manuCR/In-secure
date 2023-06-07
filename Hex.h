#ifndef HEX_H
#define HEX_H

#include <string>
#include <vector>

class Hex {
  public:
    Hex();
    std::vector<unsigned char> hexToByte(std::string in);
    std::string byteToHex(std::vector<unsigned char> out);
    unsigned char hexSwitch(char ch);
};
#endif  // HEX_H
