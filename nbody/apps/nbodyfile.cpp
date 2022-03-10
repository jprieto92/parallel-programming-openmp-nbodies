#include <iostream>
#include <fstream>
#include <cassert>
#include <chrono>


#include "fileoptions.h"
#include "simgrid.h"
#include "bodiessoa.h"
#include "bodiesaos.h"

namespace nbody_app 
{

	// Template for defining the simulation grid
	template <run_mode M>
	struct grid_type{};

	// Grid type for soa
	template <>
	struct grid_type<run_mode::soa> 
	{
		using type = simulation_grid<bodies_soa>;
	};

	// Grid type for aos
	template <>
	struct grid_type<run_mode::aos> 
	{
		using type = simulation_grid<bodies_aos>;
	};


	// Runs simulation for given options in mode M
	template <nbody_app::run_mode M>
	void run_simulation(const nbody_app::file_options & ops) 
	{
		using namespace std;
		ifstream input{ops.input()};
		if (!input) 
		{
			cerr << "Cannot open file " << ops.input()<< endl;
	    		return;
	  	}

	  	typename grid_type<M>::type grid;
	  	input >> grid;
	  	grid.print_parameters(cout);
	  	grid.simulate();

	  	ofstream output{ops.output()};
	  	if (!output) 
		{
	    		cerr << "Cannot open file " << ops.output() << endl;
	    		return;
	  	}    

	  	output << grid;
	}

	// Invokes a simulation in the mode selected by the compiler
	void run_simulation(const nbody_app::file_options & ops) 
	{
	  	using namespace nbody_app;
		using namespace std;
		auto start_time = chrono::high_resolution_clock::now();
		switch (ops.mode()) 
		{
			case run_mode::aos:
			      	run_simulation<run_mode::aos>(ops);
		    	break;
		    	case run_mode::soa:
		      		run_simulation<run_mode::soa>(ops);
		      	break;
		}
		auto end_time = chrono::high_resolution_clock::now();
		std::cout << "Total time: " << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << "ns." << std::endl;
	}

}

int main(int argc, char ** argv) 
{
	using namespace std;
	using namespace nbody_app;

	try 
	{
		file_options ops{argv+1, argv+argc};
		cout << "Execution setup" << endl << endl;
		cout << ops << endl;

		run_simulation(ops);
	}
	catch (const options_error &) 
	{
		print_usage_file(cerr, argv[0]);
	}
	return 0;
}
