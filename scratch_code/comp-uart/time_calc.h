#ifndef TIME_CALC_H
#define TIME_CALC_H

#include "standard_libs.h"

extern bool firstLoopAfterStartup;
extern long long startTimeMS;
extern long long elapsedTimeMS;

void calcStartTimeMS(void);
void calcExecutionTime(void);

#endif // TIME_CALC_H