#include "bodiesaos.h"
#include <iostream>
#include <random>

namespace nbody_app 
{

/**
 * Generates bodies at random positions with random mass.
 *
 * Each body is generated at a random position with x and y uniformly
 * distributed between (0,0) and (w,h). The mass follows a uniform
 * distribution with average m and std deviation sdm.
 *
 * Note: Current implementation uses always the same seed.
 */
void bodies_aos::generate(int n, double w, double h, double m, double sdm) 
{
	using namespace std;

	// Random distributions
	default_random_engine re;
	uniform_real_distribution<double> xdist{0.0, w};
	uniform_real_distribution<double> ydist{0.0, h};
	normal_distribution<double> mdist{m, sdm};

	// Hints for reducing allocation calls
	bodies.reserve(n);

	// Bodies generation
	for (int i=0; i<n; ++i) 
	{
		phys_vector pos{xdist(re), ydist(re)};
		double mass = mdist(re);
		body b{pos.x, pos.y, mass};
		bodies.push_back(b);
	}
}

void bodies_aos::advance(const simulation_parameters & param) 
{
	using namespace std;
	vector<phys_vector> forces {compute_forces(param)};
	apply_forces(forces,param);
}

std::istream & operator>>(std::istream & is, bodies_aos & bset) 
{
	while (is) 
	{
		body b;
		is >> b;
		if (!is) break;
		bset.bodies.push_back(b);
	}
	return is;
}

std::ostream & operator<<(std::ostream & os, const bodies_aos & bset) 
{
	for (auto & b : bset.bodies) 
	{
		os << b << std::endl;
	}
	return os;
}

std::vector<phys_vector> bodies_aos::compute_forces(const simulation_parameters & param) 
{
	std::vector<phys_vector> forces(bodies.size());
        	

	for (size_t i=0; i<bodies.size(); ++i) 
	{
		/*auxiliar variables for reduction*/
		double acumulatedCos=0.0;
		double acumulatedSin=0.0;
		
		#pragma omp parallel for reduction(+:acumulatedCos,acumulatedSin) 
		for (size_t j=i+1; j<bodies.size(); ++j) 
		{
			double dist = distance(bodies[i], bodies[j]);
			if (dist > param.min_distance()) 
			{

				double f 	= attraction(bodies[i], bodies[j], param.gravity(), dist);
				double alpha 	= angle(bodies[i],bodies[j]);
				phys_vector deltaf{ f * cos(alpha) , f * sin(alpha) };
				
				/*#pragma omp critical
				forces[i] 	+= deltaf;*/
				/*acumulate forces in auxiliar variables*/	
				acumulatedCos+=( f * cos(alpha) );
				acumulatedSin+=( f * sin(alpha) );

				forces[j] 	-= deltaf;
			}
		}
                


		/*created a object of forces type for insert in i position*/
		phys_vector acumulatedForce{acumulatedCos , acumulatedSin};
		forces[i] += acumulatedForce;
		
		/*secuential*/
		//std::cerr << "cos: " << forces[i].x << " , sin:" << forces[i].y << std::endl;
	}


	return forces;
}

void bodies_aos::apply_forces(const std::vector<phys_vector> & forces, const simulation_parameters & param) 
{
	//#pragma omp parallel for
	for (size_t i=0; i<forces.size(); ++i) 
	{
		auto accel = acceleration(bodies[i], forces[i]);
		bodies[i].update(accel, param);
	}
}

}
