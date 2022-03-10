#ifndef FILE_OPTIONS_H
#define FILE_OPTIONS_H

#include <string>
#include <iosfwd>
#include "options.h"

namespace nbody_app {

class file_options : private options_base {
public:

  template <typename I>
  file_options(I first, I last);

  using options_base::mode;

  std::string input() const { return input_name; }
  std::string output() const { return output_name; }


private:
  std::string input_name = "in.txt";
  std::string output_name = "out.txt";
};

std::ostream & operator<<(std::ostream & os, const file_options & op);

void print_usage_file(std::ostream & os,const std::string & prog);

template <typename I>
file_options::file_options(I first, I last) :
  options_base{first,last}
{
  auto i = first+1;
  
  // Start parsing optional parameters
  if (i == last) return;
  input_name = *i++;

  if (i == last) return;
  output_name =  *i++;

  // If more unexpected parameters, it is an error
  if (i != last) {
    throw options_error{};
  }
}

}

#endif
