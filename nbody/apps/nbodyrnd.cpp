#include <iostream>
#include <fstream>
#include <cassert>
#include <chrono>

#include "rndoptions.h"
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
	void run_simulation(const nbody_app::rnd_options & ops) 
	{
		using namespace std;

		constexpr double gravity = 9.8;
		constexpr double step = 0.1;
		constexpr double min_distance = 2.0;
		constexpr double width = 200;
		constexpr double height = 200;

		simulation_parameters param;
		param.set_gravity(gravity);
		param.set_evolution(step, ops.num_iterations(), min_distance);
		param.set_space(width,height);

		constexpr double mass_average = 1000.0;
		constexpr double mass_stddev = 50.0;

		typename grid_type<M>::type grid{param};
		grid.generate_bodies(ops.num_bodies(), mass_average, mass_stddev);
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
	void run_simulation(const nbody_app::rnd_options & ops) 
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
		std::cout << "Total time: " <<chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count()<< " ns." << std::endl;
	}

}

int main(int argc, char ** argv) 
{
	using namespace std;
	using namespace nbody_app;

	try 
	{
	    rnd_options ops{argv+1, argv+argc};
	    cout << "Execution setup" << endl << endl;
	    cout << ops << endl;

	    run_simulation(ops);
	}
	catch (const options_error &) 
	{
	    print_usage_rnd(cerr, argv[0]);
	}
	return 0;
}
