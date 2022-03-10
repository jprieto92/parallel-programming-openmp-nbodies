#ifndef BODIESSOA_H
#define BODIESSOA_H

#include <vector>
#include <iosfwd>
#include <cassert>


namespace nbody_app {

class simulation_parameters;

class bodies_soa {
public:
  bodies_soa() = default;

  size_t num_bodies() const;

  double x_pos(int i) const { return xpos_[i]; }
  double y_pos(int i) const { return ypos_[i]; }
  double x_vel(int i) const { return xvel_[i]; }
  double y_vel(int i) const { return yvel_[i]; }
  double mass(int i) const { return mass_[i]; }

  void add_body(double x, double y, double xv, double yv, double m);

  void generate(int n, double w, double h, double m, double sdm);
  void advance(const simulation_parameters & param);

  friend std::istream & operator>>(std::istream & is, bodies_soa & b);
  friend std::ostream & operator<<(std::ostream & os, const bodies_soa & b);

private:

  void compute_forces(std::vector<double> & fx, std::vector<double> & fy, 
                      double g, double mind) const;

  void apply_forces(const std::vector<double> & fx, const std::vector<double> & fy, 
                    double dt, double w, double h);

  double distance(int i, int j) const;
  double angle(int i, int j) const;
  double slope(int i, int j) const;
  double attraction(int i, int j, double grav, double dist) const;

  bool invariants() const;

private:
  std::vector<double> xpos_;
  std::vector<double> ypos_;
  std::vector<double> xvel_;
  std::vector<double> yvel_;
  std::vector<double> mass_;
};

inline size_t bodies_soa::num_bodies() const {
  assert(invariants());
  return xpos_.size();
}

inline bool bodies_soa::invariants() const {
  return
    (xpos_.size() == ypos_.size()) &&
    (xpos_.size() == ypos_.size()) &&
    (xpos_.size() == xvel_.size()) &&
    (xpos_.size() == yvel_.size()) &&
    (xpos_.size() == mass_.size());
}

}

#endif
