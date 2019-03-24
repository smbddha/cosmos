#include <iostream>
#include <sstream>
#include <string>

#include "nbody.hpp"

using nbody::Nbody;

int main(int argc, char** argv) {

  Nbody nbody = Nbody();
  nbody.parseFile(std::string("small.txt"));
  nbody.setDt(30000.);

  std::cout << nbody.getN() << std::endl;
  std::cout << nbody.str();
  
  int Steps = 50000;
  for (int i=0; i<Steps; i++) {
    nbody.step(); 
    std::cout << nbody.str();
    
    if (!(Steps % 5)) nbody.changePos(2, 0, 100000000.);
  }

  return(0);
}
