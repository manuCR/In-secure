#include "Hex.h"
#include <sstream>
#include <iomanip>

Hex::Hex(){
}

std::vector<unsigned char> Hex::hexToByte(std::string input){
  if (input.size() % 2 == 0 && input.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos){
    std::vector<unsigned char> bytes;
    int i = 0;
    while(i < input.size()) {
      unsigned char res = hexSwitch(input[i]) * 16 + hexSwitch(input[i+1]);
      bytes.push_back(res);
      i += 2;
    }
    return bytes;
  }
  return std::vector<unsigned char>(0);
}

std::string Hex::byteToHex(std::vector<unsigned char> input) {
  std::stringstream ss;
  ss << std::hex;
  for(int i=0; i< input.size(); ++i) {
    ss << std::setw(2) << std::setfill('0') << (int)input[i];
  }
  return ss.str();
}

unsigned char Hex::hexSwitch(char ch) {
  switch (ch){
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      return ch - '0';
      break;
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
      return ch - 'A' + 10;
      break;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
      return ch - 'a' + 10;
      break;
   default:
    return 0;
  }
}
