#ifndef PVECTOR_H
#define PVECTOR_H

#include <iostream>
#include <cmath>

namespace nbody_app {

struct phys_vector {
  double x=0, y=0;

  phys_vector() = default;
  phys_vector(double nx, double ny) : x{nx}, y{ny} {}

  phys_vector & operator +=(const phys_vector & v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  phys_vector & operator -=(const phys_vector & v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  phys_vector operator*(double k) const {
    return phys_vector{x*k, y*k};
  }

  phys_vector operator/(double k) const {
    return phys_vector{x/k, y/k};
  }

  friend std::istream & operator>>(std::istream & is, phys_vector & v) {
    return is >> v.x >> v.y;
  }

  friend std::ostream & operator<<(std::ostream & os, const phys_vector & v) {
    return os << v.x << ' ' << v.y;
  }
};

// Distance between two points
inline double distance(const phys_vector & v, const phys_vector & w) {
  return std::sqrt(std::pow(v.x-w.x,2) + std::pow(v.y-w.y,2));
}

// Slope betwee two points
inline double slope(const phys_vector & v, const phys_vector & w) {
  return (w.y - v.y) / (w.x - v.x);
}

}

#endif
