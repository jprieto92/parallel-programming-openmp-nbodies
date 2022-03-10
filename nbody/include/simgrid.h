#ifndef SIMGRID_H
#define SIMGRID_H

#include "simparam.h"
#include <iostream>

namespace nbody_app {

// Grid parametrized by bodies collection BC
template<typename BC>
class simulation_grid {
public:
  simulation_grid() = default;
  simulation_grid(const simulation_parameters & p) : param{p}, bodies{} {}

  void print_parameters(std::ostream & os) const;

  void generate_bodies(int n, double m, double sdm) { 
    bodies.generate(n, param.width(), param.height(), m, sdm); 
  }

  void simulate();

  template <typename C>
  friend std::istream & operator>>(std::istream & is, simulation_grid<C> & sg);

  template <typename C>
  friend std::ostream & operator<<(std::ostream & os, const simulation_grid<C> & sg);

private:
  simulation_parameters param;
  BC bodies;
};

template <typename BC>
void simulation_grid<BC>::print_parameters(std::ostream & os) const { 
  os << "Numbrer of bodies: " << bodies.num_bodies() << std::endl;
  print(os,param); 
}

template <typename BC>
void simulation_grid<BC>::simulate() {
  for (int i=0; i<param.steps(); ++i) {
    bodies.advance(param);
  }
}

template <typename BC>
std::istream & operator>>(std::istream & is, simulation_grid<BC> & sg) {
  is >> sg.param;
  is >> sg.bodies;
  return is;
}

template <typename BC>
std::ostream & operator<<(std::ostream & os, const simulation_grid<BC> & sg) {
  os << sg.param;
  os << sg.bodies;
  return os;
}

}

#endif
