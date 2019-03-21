#include <iostream>
#include <exception>
#include <cmath>
#include <sstream>

#include "nbody.hpp"

#define SIZE(x) (sizeof(x)/sizeof(*x))

namespace nbody {
  Nbody::Nbody() {}
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
    delete[] xs; delete[] ys; delete[] ms; delete[] vx; delete[] vy;
    delete[] fx; delete[] fy;
  }

  void Nbody::step() {
    f_reset();
    
    int i;
    for (i=0; i<N; i++) add_force(i);
    
    std::cerr << "FORCES: ";
    for (i=0; i<N; i++) std::cerr << fx[i] << " " << fy[i] << "   ";
    std::cerr << std::endl;


    std::cerr << "VELS: ";
    for (i=0; i<N; i++) {
      vx[i] += dt * fx[i] / ms[i];
      vy[i] += dt * fy[i] / ms[i];
      
      std::cerr << vx[i] << " " << vy[i] << "   ";
      
      xs[i] += dt * vx[i];
      ys[i] += dt * vy[i];
    }
    std::cerr << std::endl;
    tick++;
  }

  void Nbody::step(int n) {
    for (int i=0; i<n; i++) step();
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
      //std::cerr << "DIST: " << dist << " G: " << G << std::endl;
      //std::cerr << "[+] " << (G * ms[idx]) << std::endl;

      F = 0.;
      if (dist > 1e-10f) F = (G * ms[idx] * ms[i]) / (dist*dist);
      //std::cerr << "F " << F << std::endl;
      
      fx[idx] += F * dx / dist;
      fy[idx] += F * dy / dist;
    }
  }

  void Nbody::f_reset() {
    for (int i=0; i<N; i++) {
      fx[i] = 0.; fy[i] = 0.;
    }
  }

  T Nbody::distance(int idx1, int idx2) {
    T dx = xs[idx2] - xs[idx1];
    T dy = ys[idx2] - ys[idx1];
    std::cerr << "dx: " << dx << " dy: " << dy << std::endl;
    return std::sqrt(dx*dx + dy*dy);
  }
}

