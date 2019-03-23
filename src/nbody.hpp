#ifndef __NBODY_HPP__
#define __NBODY_HPP__

#include <string>

#include "Constants.h"

namespace nbody {
  class Nbody {
  public:
    Nbody();
    Nbody(int N, T *xs, T *ys, T *ms, T *vx, T *vy, T dt);
    ~Nbody();

    void step();
    void step(int n);

    float get(int i, int j);

    void setDt(float dt) { this->dt = (T) dt; } 
    
    std::string str();
  private:
    T dt;

    T *xs;
    T *ys;
    T *ms;
    T *vx;
    T *vy;

    T *fx;
    T *fy; 

    // # of bodies
    int N;
    size_t tick;

    T distance(int, int);
    void add_force(int);
    void f_reset();

    inline float rescale(T x, T a, T b, T yMin, T yMax) {
	    return (float) (yMin + (x - a) / (b - a) * (yMax - yMin));
    }
  };
}

#endif
