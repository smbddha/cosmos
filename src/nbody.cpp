#include <iostream>
#include <fstream>
#include <exception>
#include <cmath>
#include <sstream>

#include "nbody.hpp"

#define SIZE(x) (sizeof(x)/sizeof(*x))

namespace nbody {
  Nbody::Nbody() {
    N = 2;
    ms = new T[N]();
    xs = new T[N]();
    ys = new T[N]();
    vx = new T[N]();
    vy = new T[N]();

    ms[0] = 1.989e30; ms[1] = 0.330e24;
    xs[0] = 0.0; xs[1] = 0.0;
    ys[0] = 0.0; ys[1] = 57.9e9;
    vx[0] = 0.0; vx[1] = 47.3e3;
    vy[0] = 0.0; vy[1] = 0.0;
    
    fx = new T[N](); 
    fy = new T[N]();
  
    dt = 10.;
  }
  
  Nbody::Nbody(int N, T *xs, T *ys, T *ms, T *vx, T *vy, T dt) {
    if (SIZE(xs) != SIZE(ys) || 
        SIZE(xs) != SIZE(ms) || 
        SIZE(xs) != SIZE(vx) ||
        SIZE(xs) != SIZE(vy)) {
      throw std::invalid_argument("gotta be the same length bud");
    }

    this->dt = dt;
    this->xs = xs; this->ys = ys;
    this->ms = ms;
    this->vx = vx; this->vy = vy;
    fx = new T[N](); 
    fy = new T[N]();
    this->N = N;
  }

  Nbody::~Nbody() {
    deallocate();
  }

  void Nbody::deallocate() {
    delete[] xs; delete[] ys; delete[] ms; delete[] vx; delete[] vy;
    delete[] fx; delete[] fy;
  }

  void Nbody::step() {
    f_reset();
    
    int i;
    for (i=0; i<N; i++) add_force(i);
    
    for (i=0; i<N; i++) {
      vx[i] += dt * fx[i] / ms[i];
      vy[i] += dt * fy[i] / ms[i];
      
      xs[i] += dt * vx[i];
      ys[i] += dt * vy[i];
    }
    tick++;

  }

  void Nbody::step(int n) {
    for (int i=0; i<n; i++) step();
  }

  void Nbody::changePos(int x, int y, T val) {
    
    std::cerr << "Pos: " << xs[x] << "  ";
    xs[x] += val;
    std::cerr << "Changed pos: " << xs[x] << std::endl;
  }

  template<typename S>
  void Nbody::parseInput(S st) {
    deallocate();
    
    int i=0;
    std::string line;
    std::getline(st, line);

    std::istringstream in(line);
    in >> N; 
   
    xs = new T[N]();
    ys = new T[N]();
    ms = new T[N]();
    vx = new T[N]();
    vy = new T[N]();
    fx = new T[N](); 
    fy = new T[N]();

    while(std::getline(st, line) && i < N) {
      std::istringstream l(line);
      l >> ms[i] >> xs[i] >> ys[i] >> vx[i] >> vy[i];
      i++;
    }
  }

  void Nbody::parseFile(std::string filename) {
    std::ifstream f;
    f.open(filename);
    parseInput<std::ifstream&>(f);
    f.close();
    
    std::cerr << "FILE PARSED" <<std::endl;
  }

  std::string Nbody::str() {
    std::ostringstream o;
    for (int i=0;i<N;i++) {
      o << xs[i] << " " << ys[i] << " "
        << vx[i] << " " << vy[i]
        << std::endl;
    }
    return o.str();
  }

  void Nbody::add_force(int idx) {
    
    T dx,dy,dist,F;
    for (int i=0; i<N; i++) {
      if (i == idx) continue;
      dx = xs[i] - xs[idx];
      dy = ys[i] - ys[idx];

      dist = distance(idx, i); 

      F = 0.;
      if (dist > 1e-10f) F = (G * ms[idx] * ms[i]) / (dist*dist);
      
      fx[idx] += F * dx / dist;
      fy[idx] += F * dy / dist;
    }
  }

  void Nbody::f_reset() {
    for (int i=0; i<N; i++) {
      fx[i] = 0.; fy[i] = 0.;
    }
  }

  float Nbody::get(int i, int j) {
    if (j >= N) return 0.0;
    switch(i) {
      case 1:
        return rescale(xs[j], -57.9e9, 57.9e9, -1.0, 1.0);
      case 2:
        return rescale(ys[j], -57.9e9, 57.9e9, -1.0, 1.0);
      default:
        return 0.;
    } 
  }

  T Nbody::distance(int idx1, int idx2) {
    T dx = xs[idx2] - xs[idx1];
    T dy = ys[idx2] - ys[idx1];
    return std::sqrt(dx*dx + dy*dy);
  }
}

