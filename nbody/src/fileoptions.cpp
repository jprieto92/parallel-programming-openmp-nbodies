#include "fileoptions.h"
#include <iostream>

namespace nbody_app {

std::ostream & operator<<(std::ostream & os, const file_options & ops) {
  using namespace std;
  os << "Mode: " << ops.mode() << endl;
  os << "Input: " << ops.input() << endl;
  os << "Output: " << ops.output() << endl;
  return os;
}

void print_usage_file(std::ostream & os, const std::string & prog) {
  using namespace std;
  os << prog << " mode inname outname" << endl;
  os << "Mandatory parameters: mode" << endl;
  os << "  mode: Either aos or soa" << endl;
  os << "Optional parameters: inname outname" << endl;
  os << "  inname: Input file name." << endl;
  os << "  outname: Output file name." << endl;
}

}
