#include "Organism.hpp"
#include "definitions.hpp"

namespace z {

Organism::Organism() {
	id = getNewID();

}


// Returns a uique identifier number
uint64_t Organism::getNewID() {
	static uint64_t idCounter = 0;
	
	return idCounter++;
}

}