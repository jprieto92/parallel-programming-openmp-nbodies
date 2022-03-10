#include "bodiessoa.h"
#include <iostream>
#include <random>
#include <cassert>

#include "simparam.h"

namespace nbody_app 
{

void bodies_soa::add_body(double x, double y, double vx, double vy, double m) 
{
	xpos_.push_back(x);
	ypos_.push_back(y);
	xvel_.push_back(vx);
	yvel_.push_back(vy);
	mass_.push_back(m);
}

/**
 * Generates bodies at random positions with random mass.
 *
 * Each body is generated at a random position with x and y uniformly
 * distributed between (0,0) and (w,h). The mass follows a uniform
 * distribution with average m and std deviation sdm.
 *
 * Note: Current implementation uses always the same seed.
 */
void bodies_soa::generate(int n, double w, double h, double m, double sdm) 
{
	using namespace std;

	// Random distributions
	default_random_engine re;
	uniform_real_distribution<double> xdist{0.0, w};
	uniform_real_distribution<double> ydist{0.0, h};
	normal_distribution<double> mdist{m, sdm};

	// Hints for reducing allocation calls
	xpos_.reserve(n);
	ypos_.reserve(n);
	mass_.reserve(n);

	// Fill n elements with 0 for velocity
	xvel_.resize(n);
	yvel_.resize(n);

	// Bodies generation
	for (int i=0; i<n; ++i) 
	{
		xpos_.push_back(xdist(re));
		ypos_.push_back(ydist(re));
		mass_.push_back(mdist(re));
	}
}

void bodies_soa::advance(const simulation_parameters & param) 
{
	using namespace std;

	// Vectors x and y for forces
	std::vector<double> xforces(xpos_.size());
	std::vector<double> yforces(xpos_.size());

	// Compute forces for each particle
	compute_forces(xforces,yforces,param.gravity(),param.min_distance());

	// Apply forces to each particle
	apply_forces(xforces,yforces,param.delta_t(), param.width(), param.height());
}

std::istream & operator>>(std::istream & is, bodies_soa & bset) 
{
	while (true) 
	{
	    double px, py, vx, vy, m;
	    is >> px >> py >> vx >> vy >> m;
	    if (!is) break;
	    bset.xpos_.push_back(px);
	    bset.ypos_.push_back(py);
	    bset.xvel_.push_back(vx);
	    bset.yvel_.push_back(vy);
	    bset.mass_.push_back(m);
	}
	return is;
}

std::ostream & operator<<(std::ostream & os, const bodies_soa & bset) 
{
	for (size_t i=0; i<bset.xpos_.size(); ++i) 
	{
	      os << bset.xpos_[i] << ' '
	      << bset.ypos_[i] << ' '
	      << bset.xvel_[i] << ' '
	      << bset.yvel_[i] << ' '
	      << bset.mass_[i] << std::endl;
	}
	return os;
}

void bodies_soa::compute_forces(std::vector<double> & xforces, 
                                std::vector<double> & yforces,
                                double grav, double mind) const {
	size_t size = xpos_.size();
 
	for (size_t i=0; i<size; ++i) 
	{
	    /*Auxiliar variables for reduction*/
	    double acumulatedForcesX=0.0;
	    double acumulatedForcesY=0.0;
	    #pragma omp parallel for reduction(+:acumulatedForcesX, acumulatedForcesY)
	    for (size_t j=i+1; j<size; ++j) 
	    {
	    	double dist = distance(i,j);

	    	if (dist > mind) 
		{
			// Compute attraction force between particles i and j
			double f 	= attraction(i, j, grav, dist);
			double alpha 	= angle(i,j);
			double xdeltaf 	= f * cos(alpha);
			double ydeltaf 	= f * sin(alpha);

			// Increase force for particle i and decrease for j
			//#pragma omp critical
			//{
			//	xforces[i] 	+= xdeltaf;
			//	yforces[i] 	+= ydeltaf;
			//}
			/*Acumulate forces in auxiliar variables*/
			acumulatedForcesX  +=  xdeltaf;
			acumulatedForcesY  +=  ydeltaf;

			xforces[j] 	-= xdeltaf;
			yforces[j] 	-= ydeltaf;
		}
	    }
	    /*insert acumulated forces in i vector position*/
	    xforces[i] += acumulatedForcesX;
	    yforces[i] += acumulatedForcesY;
	
	    /*secuential*/
	    //std::cerr << "cos: " << xforces[i] << " , sin: " << yforces[i] << std::endl; 
	}

}

void bodies_soa::apply_forces(const std::vector<double> & xforces,
                              const std::vector<double> & yforces,
                              double dt, double w, double h) {
	//#pragma omp parallel for
	for (size_t i=0; i<xforces.size(); ++i) 
	{
	    double ax = xforces[i]/ mass_[i];
	    double ay = yforces[i]/ mass_[i];
	    xvel_[i] += ax * dt;
	    yvel_[i] += ay * dt;
	    xpos_[i] += xvel_[i] * dt;
	    ypos_[i] += yvel_[i] * dt;

	    if (xpos_[i] <= 0) 
	    {
	      xpos_[i] = 2;
	      xvel_[i] = -xvel_[i];
	    }
	    if (xpos_[i] >= w) 
	    {
	      xpos_[i] = w-2;
	      xvel_[i] = -xvel_[i];
	    }
	    if (ypos_[i] <= 0) 
	    {
	      ypos_[i] = 2;
	      yvel_[i] = -yvel_[i];
	    }
	    if (ypos_[i] >= h) 
	    {
	      ypos_[i] = h-2;
	      yvel_[i] = -yvel_[i];
	    }
	    assert(0<= xpos_[i] && xpos_[i] <=w);
	    assert(0<= ypos_[i] && ypos_[i] <=h);
	}
}

double bodies_soa::distance(int i, int j) const 
{
	return std::sqrt(std::pow(xpos_[i]-xpos_[j],2) + std::pow(ypos_[i]-ypos_[j],2));
}

double bodies_soa::angle(int i, int j) const 
{
	double aux = slope(i,j);
	if (aux>1) 
	{
	    aux = aux - (static_cast<int>(aux)/1);
	}
	else if (aux<-1) 
	{
	    aux = aux + (static_cast<int>(aux)/-1);
	}
	return std::atan(aux);
}

double bodies_soa::slope(int i, int j) const 
{
	return (ypos_[j]-ypos_[i])/(xpos_[j]-xpos_[i]);
}

double bodies_soa::attraction(int i, int j, double grav, double dist) const 
{
	constexpr double max_force = 200.0;
	double force = grav * mass_[i] * mass_[j] / (dist * dist);
	return std::min(force,max_force);
}

} // namespace nbody_app
