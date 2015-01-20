
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <stdio.h>

#include "NeuralNet.hpp"
#include "rng.hpp"

using namespace std;

int main() {
	vector<unsigned int> netShape = {2,20,100,20,1};
	vector<double> testInput = {0,0};
	vector<double> testOutput = {0};
	
	z::NeuralNet testNet(netShape);
	string fileName;
	
	while(1) {
		for (int k = 1; k <= 10; k++) {
			testNet.randomizeWeights();
			
			fileName = "output" + to_string(k) + ".txt";
			
			remove(fileName.c_str());
			ofstream writeData(fileName);
			if (writeData.is_open()) {
				for (double x = 0.0; x <= 1.0; x += 0.01) {
					testInput[0] = x;
					for (double y = 0.0; y <= 1.0; y += 0.01) {
						testInput[1] = y;
						testNet.calculate(testInput, testOutput);
						writeData << testOutput[0] << "\t";
						// testInput[0] << "\t" << testInput[1] << "\t" <<
					}
					writeData << "\n";
				}
				writeData.close();
				cout << "Write success.\n";
			}
			else {
				cout << "Write failure.\n";
			}
		}
		system("pause");
	}
	
	/*
	while(1) {
		testNet.randomizeWeights();
		for (int k = 1; k <= 3; k++) {
			
			cout << "Inputs are:\t";
			
			testInput.clear();
			for (int i = 0; i < netShape.front(); i++) {
				testInput.push_back(f::randomUniDist(0.0,1.0));
				cout << setprecision(3) << testInput[i] << "\t";
			}
			cout << "\n";
		
			testOutput.clear();
			testNet.calculate(testInput, testOutput);
			cout << "Outputs are:\t";
			for (int i = 0; i < testOutput.size(); i++) {
				cout << setprecision(3) << testOutput[i] << "\t";
			}
			cout << "\n\n";
		}
		system("pause");
	}
	*/
	
	return 1;
}

