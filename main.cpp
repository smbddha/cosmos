#include <iostream>
#include <sstream>
#include <string>

#include "nbody.hpp"

using nbody::Nbody;

int main() {

  int N,i=0;
  std::string line;
  std::getline(std::cin, line);

  std::istringstream in(line);
  in >> N; 
 
  float *xs,*ys,*ms,*vx,*vy;
  xs = new float[N]();
  ys = new float[N]();
  ms = new float[N]();
  vx = new float[N]();
  vy = new float[N]();

  while(std::getline(std::cin, line) && i < N) {
    std::istringstream l(line);
    l >> xs[i] >> ys[i] >> ms[i] >> vx[i] >> vy[i];
  }

  Nbody nbody(xs,ys,ms,vx,vy,0.01);

  int Steps = 5000;
  for (int i=0; i<Steps; i++) {
    nbody.step(); 
  }
}
