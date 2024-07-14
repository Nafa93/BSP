#include "RandomNumberGenerator.h"

#include <random>

int RandomNumberGenerator::generate(int lower_bound, int upper_bound)
{
	random_device rd;
	mt19937 gen(rd());
    uniform_int_distribution<> threshold(lower_bound, upper_bound);
    return threshold(gen);
}
