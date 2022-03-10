#ifndef BODY_H
#define BODY_H

#include "pvector.h"
#include "simparam.h"
#include <iosfwd>

namespace nbody_app {

class body {
public:
  body() = default;
  body(double x, double y, double m) :
    position_{x,y}, velocity_{}, mass_{m} {}

  phys_vector position() const { return position_; }
  phys_vector velocity() const { return velocity_; }
  double mass() const { return mass_; }

  double distance_to(const body & b) const {
    return distance(position_,b.position_);
  }

  double slope_to(const body & b) const {
    return slope(position_, b.position_);
  }

  double attraction_to(const body & b, double grav, double dist) const {
    constexpr double max_force = 200.0;
    double force = grav * mass_ * b.mass_ / (dist * dist);
    return std::min(force,max_force);
  }

  phys_vector acceleration(const phys_vector & force) const {
    return phys_vector{force / mass_};
  }

  void update(const phys_vector & a, const simulation_parameters & param);

  friend std::istream & operator>>(std::istream & is, body & b);
  friend std::ostream & operator<<(std::ostream & os, const body & b);

private:
  phys_vector position_;
  phys_vector velocity_;
  double mass_ = 0;
};

inline double distance(const body & b1, const body & b2) {
  return b1.distance_to(b2);
}

inline double slope(const body & b1, const body & b2) {
  return b1.slope_to(b2);
}

inline double attraction(const body & b1, const body & b2, double grav, double dist) {
  return b1.attraction_to(b2,grav,dist);
}

double angle(const body & b1, const body & b2);

inline phys_vector acceleration(const body & b, const phys_vector & f) {
  return b.acceleration(f);
}

}

#endif
