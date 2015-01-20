#ifndef RNG_HPP
#define RNG_HPP

#include <random>
#include <ctime>

namespace f {

inline double randomUniDist(double low, double high) {
	static std::default_random_engine generator(std::time(NULL));
  static std::uniform_real_distribution<double> distribution(0.0,1.0);
	
	return (high-low)*distribution(generator)+low;
}
}

#endif