#pragma once

#include <cstdlib>
#include <ctime>
#include <random> // for std::mt19937

//Making it singleton, so only there can be only one object
class RandomGenerator {
public:
	~RandomGenerator();
	static RandomGenerator* CreateSingleton();
	int getNumLCG();
	int getNumMersanne();
private:
	RandomGenerator();
	static RandomGenerator* singleton;
	std::mt19937 mersenne;
	std::uniform_int_distribution<> mGenerator;
	const int minRange = 0;
	const int maxRange = 100;
	int number;
};