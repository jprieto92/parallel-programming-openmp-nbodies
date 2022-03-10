#include "options.h"
#include <iostream>

namespace nbody_app {

std::ostream & operator<<(std::ostream & os, run_mode m) {
  switch (m) {
    case run_mode::aos:
      os << "aos";
      break;
    case run_mode::soa:
      os << "soa";
      break;
    default:
      throw options_error{};
  }
  return os;
}

std::ostream & operator<<(std::ostream & os, const options_base & ops) {
  os << "Mode: " << ops.mode() << std::endl;
  return os;
}

}
