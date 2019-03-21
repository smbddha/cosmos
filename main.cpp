#include <iostream>
#include <sstream>
#include <string>

#include "nbody.hpp"

using nbody::Nbody;

int main() {

  T dt = 10000.;
  int N,i=0;
  std::string line;
  std::getline(std::cin, line);

  std::istringstream in(line);
  in >> N; 
 
  T *xs,*ys,*ms,*vx,*vy;
  xs = new T[N]();
  ys = new T[N]();
  ms = new T[N]();
  vx = new T[N]();
  vy = new T[N]();

  while(std::getline(std::cin, line) && i < N) {
    std::istringstream l(line);
    l >> ms[i] >> xs[i] >> ys[i] >> vx[i] >> vy[i];
    i++;
  }

  std::cout << N << std::endl;

  Nbody nbody(N, xs,ys,ms,vx,vy,dt);

  std::cerr << "[+] STARTING SIMULATION" << std::endl;
  std::cout << nbody.str();
  
  int Steps = 5000;
  for (int i=0; i<Steps; i++) {
    nbody.step(); 
    std::cout << nbody.str();
  }

  return(0);
}
