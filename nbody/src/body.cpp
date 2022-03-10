#include "body.h"
#include <iostream>

namespace nbody_app {

void body::update(const phys_vector & a, const simulation_parameters & param) {
  velocity_ += a * param.delta_t();
  position_ += velocity_ * param.delta_t();
  if (position_.x <= 0) {
    position_.x = 2;
    velocity_.x = -velocity_.x;
  }
  if (position_.x >= param.width()) {
    position_.x = param.width() -2;
    velocity_.x = -velocity_.x;
  }
  if (position_.y <= 0) {
    position_.y = 2;
    velocity_.y = -velocity_.y;
  }
  if (position_.y >= param.height()) {
    position_.y = param.height()-2;
    velocity_.y = -velocity_.y;
  }
}

std::istream & operator>>(std::istream & is, body & b) {
  is >> b.position_ >> b.velocity_ >> b.mass_;
  return is;
}

std::ostream & operator<<(std::ostream & os, const body & b) {
  os << b.position_ << ' ';
  os << b.velocity_ << ' ';
  os << b.mass_;
  return os;
}

double angle(const body & b1, const body & b2) {
  double aux = slope(b1,b2);
  if (aux>1) {
    aux = aux - (static_cast<int>(aux)/1);
  }
  else if (aux<-1) {
    aux = aux + (static_cast<int>(aux)/-1);
  }
  return std::atan(aux);
}

}
