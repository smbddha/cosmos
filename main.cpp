#include <iostream>
#include <sstream>
#include <string>

#include "nbody.hpp"

using nbody::Nbody;

int main() {

  float dt = 0.001;
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
    l >> ms[i] >> xs[i] >> ys[i] >> vx[i] >> vy[i];
  }

  std::cout << "GOT " << N << " BODIES" << std::endl;

  Nbody nbody(xs,ys,ms,vx,vy,dt);

  std::cout << "[+] STARTING SIMULATION" << std::endl;
  std::cout << nbody.str();
  
  int Steps = 50;
  for (int i=0; i<Steps; i++) {
    nbody.step(); 
    std::cout << nbody.str();
  }

  return(0);
}
