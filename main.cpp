#include <iostream>
#include <sstream>
#include <string>

#include "nbody.hpp"

using nbody::Nbody;

int main() {

  int N,i=0;
  std::istringstream line;
  std::getline(std::cin, line);

  line >> N; 
 
  float* xs,ys,ms,vx,vy;
  while(std::getline(std::cin, line) && i < N) {
    
  }
}
