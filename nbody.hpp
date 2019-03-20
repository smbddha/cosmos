#ifndef __NBODY_HPP__
#define __NBODY_HPP__

#include <string>

namespace nbody {
  class Nbody {
  public:
    Nbody();
    Nbody(float *xs, float *ys, float *ms, float *vx, float *vy, float dt);
    ~Nbody();

    void step();
    void step(int n);

    std::string str();
  private:
    float dt;

    float *xs;
    float *ys;
    float *ms;
    float *vx;
    float *vy;

    float *fx;
    float *fy; 

    // # of bodies
    int N;
    size_t tick;

    float distance(int, int);
    void add_force(int);
    void f_reset();

    static constexpr float G = 6.673e-11f;
  };
}

#endif
