#include <iostream>
#include <iomanip>
#include "NeuralNet.hpp"

namespace z {

// ------------------------------------------------------------------------------

// Constructor
NeuralNet::NeuralNet(const std::vector<unsigned int> &netShape) {
	this->netShape = netShape;
	
	layerVector.reserve(netShape.size());
	
	// First value in vector is the number of inputs,so it is not created as a layer
	// The first NeuronLayer is the first hidden layer
	for (int i = 1; i < netShape.size(); i++) {
		layerVector.push_back(NeuronLayer(netShape[i], netShape[i-1]));
	}
}

void NeuralNet::randomizeWeights() {
	// Layer loop
	for (int i = 0; i < layerVector.size(); i++) {
		// Neuron loop
		for (int j = 0; j < layerVector[i].neuronVector.size(); j++) {
			layerVector[i].neuronVector[j].sigmoidBias = f::randomUniDist(-1.0, 1.0);
			//std::cout << std::setprecision(3) << layerVector[i].neuronVector[j].sigmoidBias << "\t";
			// Weight loop
			for (int k = 0; k < layerVector[i].neuronVector[j].weightVector.size(); k++) {
				layerVector[i].neuronVector[j].weightVector[k] = f::randomUniDist(-1.0, 1.0);
				//std::cout << std::setprecision(3) << layerVector[i].neuronVector[j].weightVector[k] << "\t";
			}
			//std::cout << "\n";
		}
	}
	//std::cout << "\n";
}

// Move through net and calculate output
void NeuralNet::calculate(const std::vector<double> &netInput, std::vector<double> &netOutput) {
	std::vector<double> layerInput = netInput;
	std::vector<double> layerOutput;
	
	// Layer loop
	for (int i = 0; i < layerVector.size(); i++) {
		// Neuron loop
		for (int j = 0; j < layerVector[i].neuronVector.size(); j++) {
			// Weight loop
			double neuronSum = 0;
			for (int k = 0; k < layerVector[i].neuronVector[j].weightVector.size(); k++) {
				neuronSum += layerInput[k]*layerVector[i].neuronVector[j].weightVector[k];
			}
			// 0.5*std::tanh(x)+0.5 is roughly equivalent to 1/(1+exp(x)), but faster.
			layerOutput.push_back(0.5*std::tanh(2*neuronSum - layerVector[i].neuronVector[j].sigmoidBias) + 0.5);
			//layerOutput.push_back(neuronSum - layerVector[i].neuronVector[j].sigmoidBias);
		}
		
		/*
		for (int i = 0; i < layerOutput.size(); i++) {
			std::cout << std::setprecision(3) << layerOutput[i] << "\t";
		}
		std::cout << "\n";
		*/
			
		layerInput = layerOutput;
		layerOutput.clear();
	}
	netOutput = layerInput;
}

// ------------------------------------------------------------------------------

// Constructor
NeuronLayer::NeuronLayer(unsigned int numNeurons, unsigned int numWeights) {
	neuronVector.reserve(numNeurons);
	
	for (int i = 0; i < numNeurons; i++) {
		neuronVector.push_back(Neuron(numWeights));
	}
}

// ------------------------------------------------------------------------------

// Constructor
Neuron::Neuron(unsigned int numWeights) {
	weightVector.reserve(numWeights);
	
	sigmoidBias = 0;
	
	for (int i = 0; i < numWeights; i++) {
		weightVector.push_back(0);
	}
}

}




