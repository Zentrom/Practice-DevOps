
#include "Source\RandomGenerator.h"
#include "Source\Writer.h"

#include <glm\vec3.hpp>
#include <glm\mat3x3.hpp>

#include <iostream>
#include <fstream>
#include <array>
#include <sstream>



int main() {
	std::cout << "Hello world!" << std::endl;
	std::cout << "Max random is: " << RAND_MAX << std::endl;
	std::cout << "Min random is: " << 0 << std::endl;

	std::ofstream outFile{ "Result.txt", std::ios::trunc };
	Writer output(std::cout, outFile);

	RandomGenerator* pRandGen = RandomGenerator::CreateSingleton();

	output << "[[[INTARRAY]]]" << '\n';
	std::array<glm::ivec3, 10> vIntArray;
	for (glm::ivec3 elem : vIntArray) {
		elem = glm::ivec3(pRandGen->getIntLCG(), pRandGen->getIntLCG(), pRandGen->getIntLCG());
		output << '[' << elem.x << ' ' << elem.y << ' ' << elem.z << ']' << '\n';
	}
	output << "[[[FLOATARRAY]]]" << '\n';
	std::array<glm::vec3, 10> vFloatArray;
	for (glm::vec3 elem : vFloatArray) {
		elem = glm::vec3(pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), pRandGen->getFloatLCG());
		output << '[' << elem.x << ' ' << elem.y << ' ' << elem.z << ']' << '\n';
	}
	output << "[[[FLOATMATRIX]]]" << '\n';
	std::array<glm::mat3, 10> matrixArray;
	for (glm::mat3 elem : matrixArray) {
		elem = glm::mat3(pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), 
			pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), 
			pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), pRandGen->getFloatLCG());
		output << '|' << elem[0].x << ' ' << elem[0].y << ' ' << elem[0].z << '|' << '\n';
		output << '|' << elem[1].x << ' ' << elem[1].y << ' ' << elem[1].z << '|' << '\n';
		output << '|' << elem[2].x << ' ' << elem[2].y << ' ' << elem[2].z << '|' << '\n';
		output << '\n';
	}

	outFile.close();
	int vlm;
	std::cin >> vlm;
}