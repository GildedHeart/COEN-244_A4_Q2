#include "BaseTensor.h"

// Methodes

double BaseTensor::valueGen() {
	std::random_device rd;
	std::mt19937 mt(rd());

	// Create a uniform distribution between 0 and 1
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	// Generate and print a random double value 
	double randomValue = dist(mt);

	return randomValue;
}
