// Description:
// Class for creation and use of layered, feed-forward neural nets.

#ifndef NEURALNET_HPP
#define NEURALNET_HPP

#include <vector>
#include <numeric>
#include <random>
#include <cmath>
#include <cstdlib>

#include "rng.hpp"

namespace z {

class Neuron {
public:
	std::vector<double> weightVector;
	double sigmoidBias;
	
	Neuron(unsigned int numWeights);
};

class NeuronLayer {
public:
	std::vector<z::Neuron> neuronVector;

	NeuronLayer(unsigned int numNeurons, unsigned int numWeights);
	void calculate(const std::vector<double> &layerInput, std::vector<double> &layerOutput);
};

class NeuralNet {
public:
	std::vector<unsigned int> netShape;
	std::vector<z::NeuronLayer> layerVector;
	
	NeuralNet(const std::vector<unsigned int> &netShape);
	
	void randomizeWeights();
	NeuralNet duplicate(double randomization, double mutation);
	NeuralNet mate(NeuralNet &parent2, double mutation);
	void calculate(const std::vector<double> &netInput, std::vector<double> &netOutput);

};
}

#endif