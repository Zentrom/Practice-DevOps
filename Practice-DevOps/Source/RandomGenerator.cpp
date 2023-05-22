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
	delete singleton;
}

RandomGenerator::RandomGenerator() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	//first random not that random, so just drop it
	std::rand();

	// Initialize our mersenne twister with a random seed based on the clock
	mersenne = std::mt19937(static_cast<std::mt19937::result_type>(std::time(nullptr)));
	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	mGenerator = std::uniform_int_distribution<>(minRange, maxRange);
}

//This uses an LCG algoritm(unsigned 15bit period)
int RandomGenerator::getNumLCG()
{
	// static used for efficiency, so we only calculate this value once
	static const double fraction( 1.0 / (RAND_MAX + 1.0) );																 // evenly distribute the random number across our range
	return minRange + static_cast<int>((maxRange - minRange + 1) * (std::rand() * fraction));
}

int RandomGenerator::getNumMersanne() {
	
	// If your compiler doesn't support C++17, use this instead
	// std::uniform_int_distribution<> die{ 1, 6 };
	// Print a bunch of random numbers
	//for (int count{ 1 }; count <= 48; ++count)
	//{
	//	std::cout << die(mersenne) << '\t'; // generate a roll of the die here
	//										// If we've printed 6 numbers, start a new row
	//	if (count % 6 == 0)
	//		std::cout << '\n';
	//}
	return mGenerator(mersenne);
}
