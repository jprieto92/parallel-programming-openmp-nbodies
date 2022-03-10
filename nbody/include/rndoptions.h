#ifndef OPTIONSRND_H
#define OPTIONSRND_H

#include "options.h"

namespace nbody_app {

class rnd_options : private options_base {
public:

  template <typename I>
  rnd_options(I first, I last);

  using options_base::mode;

  int num_bodies() const { return num_bodies_; }
  int num_iterations() const { return num_iterations_; }
  std::string output() const { return output_name; }

  friend std::ostream & operator<<(std::ostream & os, const rnd_options & op);

private:
  int num_bodies_ = 50;
  int num_iterations_ = 100;
  std::string output_name = "out.txt";
};

std::ostream & operator<<(std::ostream & os, const rnd_options & op);

void print_usage_rnd(std::ostream & os, const std::string & prog);

template <typename I>
rnd_options::rnd_options(I first, I last) :
  options_base{first,last}
{
  auto i = first+1;

  if (std::distance(first,last) < 1) {
    throw options_error{};
  }

  // Start parsing optional parameters
  try {
    // Number of bodies
    if (i == last) return;
    num_bodies_ = std::stoi(*i++);

    // Number of iterations
    if (i == last) return;
    num_iterations_ = std::stoi(*i++);
  } catch(...) {
    throw options_error();
  }

  if (i==last) return;
  output_name = *i++;

  // If more unexpected parameters, it is an error
  if (i != last) {
    throw options_error{};
  }
}

} // namespace nbody_app

#endif
