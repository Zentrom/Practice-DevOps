
#include "Source\RandomGenerator.h"
#include "Source\Writer.h"

#include <glm\vec3.hpp>
#include <glm\mat3x3.hpp>

#include <iostream>
#include <fstream>
#include <array>

int main() {
	//Create writers
	std::ofstream outFile{ "Result.txt", std::ios::trunc };
	Writer output(std::cout, outFile);

	output << "Hello world!" << '\n';
	output << "Max random is: " << RAND_MAX << '\n';
	output << "Min random is: " << 0 << '\n';
	//Create random generator
	RandomGenerator* pRandGen = RandomGenerator::CreateSingleton();
	//Generate int vectors
	output << '\n' << "[[[INTARRAY]]]" << '\n';
	std::array<glm::ivec3, 10> vIntArray;
	for (glm::ivec3& elem : vIntArray) {
		elem = glm::ivec3(pRandGen->getIntLCG(), pRandGen->getIntLCG(), pRandGen->getIntLCG());
		output << '[' << elem.x << ' ' << elem.y << ' ' << elem.z << ']' << '\n';
	}
	//Generate float vectors
	output << '\n' << "[[[FLOATARRAY]]]" << '\n';
	std::array<glm::vec3, 10> vFloatArray;
	for (glm::vec3& elem : vFloatArray) {
		elem = glm::vec3(pRandGen->getFloatMersenne(), pRandGen->getFloatMersenne(), pRandGen->getFloatMersenne());
		output << '[' << elem.x << ' ' << elem.y << ' ' << elem.z << ']' << '\n';
	}
	//Generate float matrices
	output << '\n' << "[[[FLOATMATRIX]]]" << '\n';
	std::array<glm::mat3, 4> matrixArray;
	for (glm::mat3& elem : matrixArray) {
		elem = glm::mat3(pRandGen->getFloatMersenne(), pRandGen->getFloatMersenne(), pRandGen->getFloatMersenne(),
			pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), 
			pRandGen->getFloatLCG(), pRandGen->getFloatLCG(), pRandGen->getFloatLCG());
		output << '|' << elem[0].x << ' ' << elem[0].y << ' ' << elem[0].z << '|' << '\n';
		output << '|' << elem[1].x << ' ' << elem[1].y << ' ' << elem[1].z << '|' << '\n';
		output << '|' << elem[2].x << ' ' << elem[2].y << ' ' << elem[2].z << '|' << '\n';
		output << '\n';
	}
	//Round up
	output << '\n' << "[[[CEIL]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		glm::vec3 result = glm::ceil(elem);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//Round down
	output << '\n' << "[[[FLOOR]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		glm::vec3 result = glm::floor(elem);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//Fraction
	output << '\n' << "[[[FRACT]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		glm::vec3 result = glm::fract(elem);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//Clamp between two values
	output << '\n' << "[[[CLAMP]]]" << '\n';
	for (glm::ivec3 elem : vIntArray) {
		glm::ivec3 result = glm::clamp(elem, 25, 75);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//x*y+z
	output << '\n' << "[[[FMA]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		float result = glm::fma(elem.x, elem.y, elem.z);
		output << result << '\n';
	}
	//x=float * 2^exponent --- LDEXP is to get back original value
	output << '\n' << "[[[FREXP]]]" << '\n';
	for (int i = 0; i < 10;i++) {
		glm::ivec3 exp = vIntArray[i];
		glm::vec3 result = glm::frexp(vFloatArray[i], exp);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << ' ' 
			<< '[' << exp.x << ' ' << exp.y << ' ' << exp.z << ']' << '\n';
		glm::vec3 resultLD = glm::ldexp(result, exp);
		output << "---LDEXP---" << '[' << resultLD.x << ' ' << resultLD.y << ' ' << resultLD.z << ']' << ' '
			<< '[' << exp.x << ' ' << exp.y << ' ' << exp.z << ']' << '\n';
	}
	//Mix 2 values based on bias
	output << '\n' << "[[[MIX]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		glm::vec3 result = glm::mix(vFloatArray[i], static_cast<glm::vec3>(vIntArray[i]), 0.5f);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//Remainder of vector division
	output << '\n' << "[[[MOD]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		glm::vec3 result = glm::mod(static_cast<glm::vec3>(vIntArray[i]), vFloatArray[i]);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//Gives back value in [0,1] interval based on edges
	output << '\n' << "[[[SMOOTHSTEP]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		glm::vec3 result = glm::smoothstep(0.0f, 50.0f, elem);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//0 if smaller then edge, 1 otherwise
	output << '\n' << "[[[STEP]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		glm::vec3 result = glm::step(50.0f, elem);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}

	output << '\n' << '\n' << '\n' << "(GEOMETRIC FUNCTIONS)" << '\n' << '\n';

	//[x[1]*y[2]−y[1]*x[2]]
	//[x[2]*y[0]−y[2]*x[0]]
	//[x[0]*y[1]−y[0]*x[1]]
	output << '\n' << "[[[CROSS]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		glm::vec3 result = glm::cross(vFloatArray[i], static_cast<glm::vec3>(vIntArray[i]));
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//length(v0 - v1)
	output << '\n' << "[[[DISTANCE]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		float result = glm::distance(vFloatArray[i], static_cast<glm::vec3>(vIntArray[i]));
		output << result << '\n';
	}
	//sqrt(v * v)
	output << '\n' << "[[[LENGTH]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		float result = glm::length(elem);
		output << result << '\n';
	}
	//x[0]*y[0]+x[1]*y[1]+x[2]*y[2]
	output << '\n' << "[[[DOT]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		float result = glm::dot(vFloatArray[i], static_cast<glm::vec3>(vIntArray[i]));
		output << result << '\n';
	}
	//Same direction, but length=1
	output << '\n' << "[[[NORMALIZE]]]" << '\n';
	for (glm::vec3 elem : vFloatArray) {
		glm::vec3 result = glm::normalize(elem);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//v0 - 2.0 * dot(v1, v0) * v1 - Normalize v1
	output << '\n' << "[[[REFLECT]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		glm::vec3 result = glm::reflect(vFloatArray[i], glm::normalize(static_cast<glm::vec3>(vIntArray[i])));
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//3rd parameter is material refraction index - Normalize v0 and v1
	output << '\n' << "[[[REFRACT]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		float waterRefraction = 1.33f;
		glm::vec3 result = glm::refract(glm::normalize(vFloatArray[i]),
			glm::normalize(static_cast<glm::vec3>(vIntArray[i])),
			waterRefraction);
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}
	//Good to make v0 always orient towards v1 i guess
	//v0 - vector to orient
	//v1 - incident vector
	//v2 - reference vector(normal of a surface)
	output << '\n' << "[[[FACEFORWARD]]]" << '\n';
	for (int i = 0; i < 10; i++) {
		glm::vec3 result = glm::faceforward(vFloatArray[i],
			static_cast<glm::vec3>(vIntArray[i]),
			glm::vec3(0,1,0));
		output << '[' << result.x << ' ' << result.y << ' ' << result.z << ']' << '\n';
	}

	output << '\n' << '\n' << '\n' << "(MATRIX FUNCTIONS)" << '\n' << '\n';

	//Determinant of squared M for area/volume measure
	output << '\n' << "[[[DETERMINANT]]]" << '\n';
	for (glm::mat3 elem : matrixArray) {
		float result = glm::determinant(elem);
		output << result << '\n';
	}
	//Inverse of squared M
	output << '\n' << "[[[INVERSE]]]" << '\n';
	for (glm::mat3 elem : matrixArray) {
		glm::mat3 result = glm::inverse(elem);
		output << '|' << result[0].x << ' ' << result[0].y << ' ' << result[0].z << '|' << '\n';
		output << '|' << result[1].x << ' ' << result[1].y << ' ' << result[1].z << '|' << '\n';
		output << '|' << result[2].x << ' ' << result[2].y << ' ' << result[2].z << '|' << '\n';
		output << '\n';
	}
	//Transpose - Rows become columns
	output << '\n' << "[[[TRANSPOSE]]]" << '\n';
	for (glm::mat3 elem : matrixArray) {
		glm::mat3 result = glm::transpose(elem);
		output << '|' << result[0].x << ' ' << result[0].y << ' ' << result[0].z << '|' << '\n';
		output << '|' << result[1].x << ' ' << result[1].y << ' ' << result[1].z << '|' << '\n';
		output << '|' << result[2].x << ' ' << result[2].y << ' ' << result[2].z << '|' << '\n';
		output << '\n';
	}
	//resMatrix[i][j] is the scalar product of m0[i][j] and m1[i][j] - Multiply each component
	output << '\n' << "[[[MATRIXCOMPMULT]]]" << '\n';
	glm::mat3 resMatrix = glm::matrixCompMult(matrixArray[0], matrixArray[1]);
	output << '|' << resMatrix[0].x << ' ' << resMatrix[0].y << ' ' << resMatrix[0].z << '|' << '\n';
	output << '|' << resMatrix[1].x << ' ' << resMatrix[1].y << ' ' << resMatrix[1].z << '|' << '\n';
	output << '|' << resMatrix[2].x << ' ' << resMatrix[2].y << ' ' << resMatrix[2].z << '|' << '\n';
	output << '\n';
	//Multiplies 2 vectors, each component with each to create a matrix
	output << '\n' << "[[[OUTERPRODUCT]]]" << '\n';
	resMatrix = glm::outerProduct(vFloatArray[0], vFloatArray[1]);
	output << '|' << resMatrix[0].x << ' ' << resMatrix[0].y << ' ' << resMatrix[0].z << '|' << '\n';
	output << '|' << resMatrix[1].x << ' ' << resMatrix[1].y << ' ' << resMatrix[1].z << '|' << '\n';
	output << '|' << resMatrix[2].x << ' ' << resMatrix[2].y << ' ' << resMatrix[2].z << '|' << '\n';
	output << '\n';

	outFile.close();
	int vlm;
	std::cin >> vlm;
}