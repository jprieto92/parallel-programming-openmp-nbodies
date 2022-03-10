#ifndef OPTIONS_H
#define OPTIONS_H

#include <iosfwd>
#include <string>

namespace nbody_app {

struct options_error {};

enum class run_mode { aos, soa };
std::ostream & operator<<(std::ostream & os, run_mode m); 

class options_base {
public:
  template <typename I>
  options_base(I first, I last);

  run_mode mode() const { return rmode; }

private:
  run_mode rmode;
};

std::ostream & operator<<(std::ostream & os, const options_base & op);

template <typename I>
options_base::options_base(I first, I last) 
{
  auto i = first;

  // -- Check mandatory options --

  // mode
  if (i== last) throw options_error{};
  if (std::string{"aos"} == *i) { rmode = run_mode::aos; }
  else if (std::string{"soa"} == *i) { rmode = run_mode::soa; }
  else throw options_error{};
  ++i;
}


}

#endif
