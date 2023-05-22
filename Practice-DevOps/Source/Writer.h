#pragma once

#include <fstream>

//Class that outputs in console and file aswell
class Writer {
private:
	std::ostream &os1, &os2; //The 2 output streams
public:
	Writer(std::ostream &os1, std::ostream &os2) : os1(os1), os2(os2) {}
	//Does the writing
	template <typename T>
	Writer& operator<<(const T &thing) {
		os1 << thing;
		os2 << thing;
		return *this;
	}
};