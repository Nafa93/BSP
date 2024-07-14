#pragma once

#include <chrono>

using namespace std;

class ExecutionMeasurer
{
public:
	void start();
	void stop();

private:
	chrono::steady_clock::time_point start_timestamp;
	chrono::steady_clock::time_point stop_timestamp;
};

