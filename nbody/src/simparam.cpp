#include "simparam.h"
#include <iostream>

namespace nbody_app {

std::istream & operator>>(std::istream & is, simulation_parameters & p) {
  is >> p.gravity_
     >> p.delta_t_ >> p.num_steps_ >> p.min_distance_
     >> p.width_ >> p.height_;     
  return is;
}

std::ostream & operator<<(std::ostream & os, const simulation_parameters & p) {
  os << p.gravity_ << ' ';
  os << p.delta_t_ << ' ';
  os << p.num_steps_ << ' ';
  os << p.min_distance_ << ' ';
  os << p.width_ << ' ';
  os << p.height_ << std::endl;     
  return os;
}

void print(std::ostream & os, const simulation_parameters & p) {
  using namespace std;
  os << "Gravitiy: " << p.gravity() << endl;
  os << "Delta time: " << p.delta_t() << endl;
  os << "Number of steps: " << p.steps() << endl;
  os << "Min. distance: " << p.min_distance() << endl;
  os << "Width: " << p.width() << endl;
  os << "Height: " << p.height() << endl;     
}

}
