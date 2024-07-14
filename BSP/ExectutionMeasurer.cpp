#include "ExecutionMeasurer.h"

#include <chrono>
#include <iostream>

using namespace std;

using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

void ExecutionMeasurer::start()
{
    start_timestamp = high_resolution_clock::now();
}

void ExecutionMeasurer::stop()
{
    stop_timestamp = high_resolution_clock::now();

    duration<double, milli> ms_double = stop_timestamp - start_timestamp;

    cout << ms_double.count() << "ms" << endl;
}
