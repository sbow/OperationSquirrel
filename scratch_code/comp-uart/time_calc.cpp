#include "time_calc.h"

bool firstLoopAfterStartup = true;
long long startTimeMS = 0;
long long elapsedTimeMS = 0;

void calcStartTimeMS(void)
{
    // Get the start time
    auto now = std::chrono::high_resolution_clock::now();
    startTimeMS = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

void calcExecutionTime(void)
{
    // Get the current timestamp in milliseconds
    auto now = std::chrono::high_resolution_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    // Calculate the elapsed time since the start of the program
    elapsedTimeMS = timestamp - startTimeMS;

    elapsedTimeMS = elapsedTimeMS - (long long)25;
}