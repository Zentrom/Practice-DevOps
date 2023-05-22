#include "RandomGenerator.h"

//Initialize to nullptr, so it can be initialized at the first call
RandomGenerator* RandomGenerator::singleton = nullptr;

RandomGenerator* RandomGenerator::CreateSingleton() {
	if (!singleton) {
		singleton = new RandomGenerator();
	}
	return singleton;
}

RandomGenerator::~RandomGenerator() {
	if (singleton) {
		delete singleton;
	}
}

RandomGenerator::RandomGenerator() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	//first random not that random, so just drop it
	std::rand();

	// Initialize our mersenne twister with a random seed based on the clock
	mersenne = std::mt19937(static_cast<std::mt19937::result_type>(std::time(nullptr)));
	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	mIntGenerator = std::uniform_int_distribution<int>(minRange, maxRange);
	mFloatGenerator = std::uniform_real_distribution<float>(static_cast<float>(minRange), static_cast<float>(maxRange));
}

//This uses an LCG algoritm(unsigned 15bit period)
int RandomGenerator::getIntLCG()
{
	// static used for efficiency, so we only calculate this value once
	static const double fraction( 1.0 / (RAND_MAX + 1.0) );																 // evenly distribute the random number across our range
	return minRange + static_cast<int>((maxRange - minRange + 1) * (std::rand() * fraction));
}
//Generate with Mersenne algorithm
int RandomGenerator::getIntMersenne() 
{
	return mIntGenerator(mersenne);
}

float RandomGenerator::getFloatLCG() 
{
	return minRange + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / (maxRange - minRange)));
}

float RandomGenerator::getFloatMersenne() {
	return mFloatGenerator(mersenne);
}