#ifndef BODIESAOS_H
#define BODIESAOS_H

#include <vector>
#include <iosfwd>
#include "body.h"

namespace nbody_app {

class bodies_aos {
public:
  bodies_aos() = default;

  size_t num_bodies() const { return bodies.size(); }

  void generate(int n, double w, double h, double m, double sdm);
  void advance(const simulation_parameters & param);

  friend std::istream & operator>>(std::istream & is, bodies_aos & bset);
  friend std::ostream & operator<<(std::ostream & os, const bodies_aos & bset);
private:

  std::vector<phys_vector> compute_forces(const simulation_parameters & param);
  void apply_forces(const std::vector<phys_vector> & forces, const simulation_parameters & param);

private:
  std::vector<body> bodies;
};

}

#endif
