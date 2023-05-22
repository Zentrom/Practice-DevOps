#pragma once

#include <fstream>

class Writer {
private:
	std::ostream &os1, &os2;
public:
	Writer(std::ostream &os1, std::ostream &os2) : os1(os1), os2(os2) {}

	template <typename T>
	Writer& operator<<(const T &thing) {
		os1 << thing;
		os2 << thing;
		return *this;
	}
};