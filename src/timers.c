/* timers.c
 * Abstraction for two timer roles:
 *  - step pulse generator (toggles STEP pin at half_period_us intervals)
 *  - PID scheduler tick (calls PID compute at fixed dt)
 *
 * Replace placeholders with SysConfig/TI driverlib timer configuration.
 */

#include "timers.h"
#include "stepper.h"
#include "encoder.h"
#include "pid.h"
#include <stdint.h>
#include <stdbool.h>

static PID_t *registered_pid = NULL;
static uint32_t pid_tick_ms = 10;

void Timers_init(void)
{
    // TODO: configure hardware timers via SysConfig
}

void Timers_startStepTimer(uint32_t half_period_us)
{
    // TODO: start hardware timer that calls STEP toggle ISR every half_period_us
    (void)half_period_us;
}

void Timers_stopStepTimer(void)
{
    // TODO: stop hardware step timer
}

void Timers_startPidScheduler(uint32_t tick_ms)
{
    pid_tick_ms = tick_ms;
    // TODO: start a periodic timer that calls the 'pid tick' handler every tick_ms
}

void Timers_registerPidCallback(PID_t *pid)
{
    registered_pid = pid;
}

// Example function: called by PID scheduler timer interrupt every pid_tick_ms
void Timers_pidTickHandler(void)
{
    if (!registered_pid) return;

    // compute error in pulses (target - actual) -- these accessors must be atomic
    int64_t current_enc = Encoder_getCounts();
    // map encoder counts to pulses (microsteps)
    const int ENC_CPR = 500;
    const int PPR = 200 * 16;
    float revolutions = (float)current_enc / (float)ENC_CPR;
    float current_pulses = revolutions * (float)PPR;

    // target_pulses is inside stepper module; for now we fetch via Stepper_getAngle -> convert
    // For a tighter integration, expose Stepper_getTargetPulses();

    // TODO: read target from stepper safely and compute PID
    (void)current_pulses;
}
