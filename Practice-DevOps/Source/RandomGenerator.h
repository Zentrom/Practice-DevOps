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
	std::mt19937 mersenne; //Mersenne engine
	std::uniform_int_distribution<int> mIntGenerator; //int generator
	std::uniform_real_distribution<float> mFloatGenerator; //float generator
	const int minRange = 0; //min generated number
	const int maxRange = 100; //max generated number
};