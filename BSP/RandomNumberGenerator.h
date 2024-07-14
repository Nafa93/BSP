#pragma once

#include <random>

using namespace std;

class RandomNumberGenerator
{
public:
	RandomNumberGenerator() {}
	int generate(int lower_bound, int upper_bound);
private:
};

