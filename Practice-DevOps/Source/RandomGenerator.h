#pragma once

#include <cstdlib>
#include <ctime>
#include <random> // for std::mt19937

//Making it singleton, so only there can be only one object
class RandomGenerator {
public:
	~RandomGenerator();
	static RandomGenerator* CreateSingleton();
	int getIntLCG();
	int getIntMersenne();
	float getFloatLCG();
	float getFloatMersenne();
	RandomGenerator(const RandomGenerator&) = delete; // non construction-copyable
	RandomGenerator& operator=(const RandomGenerator&) = delete; // non copyable
private:
	RandomGenerator();
	static RandomGenerator* singleton;
	std::mt19937 mersenne;
	std::uniform_int_distribution<int> mIntGenerator;
	std::uniform_real_distribution<float> mFloatGenerator;
	const int minRange = 0;
	const int maxRange = 100;
};