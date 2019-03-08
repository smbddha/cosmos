#include <iostream>
#include <exception>
#include <cmath>
#include <sstream>

#include "nbody.hpp"

#define SIZE(x) (sizeof(x)/sizeof(*x))

int main() {
  Nbody nbody = Nbody(); 
}

Nbody::Nbody(float *xs, float *ys, float *ms, float *vx, float *vy, float dt) {
  if (SIZE(xs) != SIZE(ys) || 
      SIZE(xs) != SIZE(ms) || 
      SIZE(xs) != SIZE(vx) ||
      SIZE(xs) != SIZE(vy)) {
    throw std::invalid_argument("gotta be the same length bud");
  }

  G = 6.673e-11;

  this->dt = dt;
  this->xs = xs; this->ys = ys;
  this->ms = ms;
  this->vx = vx; this->vy = vy;
  fx = new float[SIZE(xs)]; fx = new float[SIZE(xs)];
  N = SIZE(xs);
}

Nbody::~Nbody() {
  free(xs); free(ys); free(ms); free(vx); free(vy);
  free(fx); free(fy);
}

void Nbody::step() {
  int i;
  for (i=0; i<N; i++) add_force(i);
  for (i=0; i<N; i++) {
    vx[i] = dt * fx[i] / ms[i];
    vy[i] = dt * fy[i] / ms[i];
    xs[i] = dt * vx[i];
    ys[i] = dt * vy[i];
  }
  tick++;
}

void Nbody::step(int n) {
  for (int i=0; i<n; i++) step();
}

std::string Nbody::str() {
  std::ostringstream o;
  o << "TICK " << tick << std::endl;
  for (int i=0;i<N;i++) {
    o << "x: " << xs[i] << " y: " << ys[i]
      << " vx: " << vx[i] << " vy: " << vy[i]
      << std::endl;
  }
  return o.str();
}

void Nbody::add_force(int idx) {
  float dx,dy,dist,F;
  for (int i=0; i<N; i++) {
    if (i == idx) continue;
    dx = xs[i] - xs[idx];
    dy = ys[i] - ys[idx];

    dist = distance(idx, i); 
    F = (G * ms[idx] * ms[i]) / (dist*dist);
    fx[idx] += F * dx / dist;
    fy[idx] += F * dy / dist;
  }
}

float Nbody::distance(int idx1, int idx2) {
  float dx = xs[idx2] - xs[idx1];
  float dy = ys[idx2] - ys[idx2];
  return std::sqrt(dx*dx + dy*dy);
}
