#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>
#include "pid.h"

// initialize timers subsystem
void Timers_init(void);

// start/stop the step pulse generation timer
void Timers_startStepTimer(uint32_t half_period_us);
void Timers_stopStepTimer(void);

// PID scheduler registration and control (tick in ms)
void Timers_startPidScheduler(uint32_t tick_ms);
void Timers_registerPidCallback(PID_t *pid);

#endif // TIMERS_H
