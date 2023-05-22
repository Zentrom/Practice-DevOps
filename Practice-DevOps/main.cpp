
#include "Source\RandomGenerator.h"

#include <iostream>


int main() {
	std::cout << "Hello world!" << std::endl;
	std::cout << "Max random is: " << RAND_MAX << std::endl;
	std::cout << "Min random is: " << 0 << std::endl;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	RandomGenerator* pRandGen = RandomGenerator::CreateSingleton();

	for (int i = 0; i < 10; i++) {
		std::cout << pRandGen->getNumMersanne() << std::endl;
	}

	int vlm;
	std::cin >> vlm;
}