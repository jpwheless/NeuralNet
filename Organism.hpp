#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include "NeuralNet.hpp"

namespace z {

class Organism {
public:
	const uint64_t id;
	NeuralNet brain;
	
	unsigned int energy;
	double x, y;
	double dx, dy;

	Organism();
	
	setID();
};

}

#endif