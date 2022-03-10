#ifndef SIMPARAM_H
#define SIMPARAM_H

#include <iosfwd>

namespace nbody_app {

struct simulation_parameters {
  simulation_parameters() = default;

  void set_gravity(double g) { gravity_=g; }

  void set_evolution(double dt, int n, double md) {
    delta_t_ = dt;
    num_steps_ = n;
    min_distance_ = md;
  }

  void set_space(double w, double h) { width_=w; height_=h; }

  double gravity() const { return gravity_; }
  double delta_t() const { return delta_t_; }
  int steps() const { return num_steps_; }
  double min_distance() const { return min_distance_; }
  double width() const { return width_; }
  double height() const { return height_; }

  friend std::istream & operator>>(std::istream & is, simulation_parameters & p);
  friend std::ostream & operator<<(std::ostream & is, const simulation_parameters & p); 

private:
  double gravity_ = 9.8;
  double delta_t_ = 0.1;
  int num_steps_ = 100;
  double min_distance_= 1;
  double width_ = 500;
  double height_ = 500;
};

void print(std::ostream & os, const simulation_parameters & p);
}

#endif

