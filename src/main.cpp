#include <iostream>
#include <sstream>
#include <string>

#include "nbody.hpp"

using nbody::Nbody;

int main(int argc, char** argv) {

  Nbody nbody = Nbody();
  nbody.parseFile(std::string("small.txt"));
  nbody.setDt(100000.);

  std::cout << nbody.getN() << std::endl;
  std::cout << nbody.str();
  
  int Steps = 5000;
  for (int i=0; i<Steps; i++) {
    nbody.step(); 
    std::cout << nbody.str();
  }

  return(0);
}
