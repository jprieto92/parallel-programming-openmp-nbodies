#include "rndoptions.h"

#include <iostream>

namespace nbody_app {

std::ostream & operator<<(std::ostream & os, const rnd_options & ops) {
  using namespace std;
  os << "Number of bodies: " << ops.num_bodies() << endl;
  os << "Number of iteratios: " << ops.num_iterations() << endl;
  os << "Output file: " << ops.output() << endl;
  return os;
}

void print_usage_rnd(std::ostream & os, const std::string & prog) {
  using namespace std;
  os << prog << " mode nbodies" << endl;
  os << "Mandatory parameters: mode" << endl;
  os << "  mode: Either aos or soa" << endl;
  os << "Optional parameters: nbodies niter outname" << endl;
  os << "  nbodies: Number of bodies to generate." << endl;
  os << "  niter: Number of iterations." << endl;
  os << "  outname: Output file name." << endl;
}

}
