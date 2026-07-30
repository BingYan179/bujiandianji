/* stepper.c
 * Closed-loop position controller for D36A (STEP/DIR) + MS42C motor
 * Requires: Encoder module to provide pulses count in 'encoder_counts'.
 * PPR = motor_steps_per_rev * microstep
 */

#include "stepper.h"
#include "encoder.h"
#include "pid.h"
#include "timers.h"
#include <math.h>

// Configuration
#define MOTOR_STEPS_PER_REV 200
#define MICROSTEP 16
#define PPR (MOTOR_STEPS_PER_REV * MICROSTEP) // 3200

// Driver pins (as assigned)
#define PIN_STEP   /* PB15 */ 15
#define PIN_DIR    /* PB16 */ 16
#define PIN_EN     /* PB0  */ 0

// Minimal helper prototypes - map to actual GPIO APIs in SysConfig
static void gpio_write(int pin, int val);
static void gpio_init_pin(int pin);

// Internal state
static volatile int64_t target_pulses = 0;
static volatile bool moving = false;
static float current_velocity_pps = 0.0f; // pulses per second (signed)

// PID controller instance for position→velocity
static PID_t pos_pid;

void Stepper_init(void)
{
    // init GPIOs
    gpio_init_pin(PIN_STEP);
    gpio_init_pin(PIN_DIR);
    gpio_init_pin(PIN_EN);

    gpio_write(PIN_STEP, 0);
    gpio_write(PIN_EN, 0); // assume active low enable; check your board

    // init PID
    PID_init(&pos_pid, 0.02f, 0.001f, 0.0005f); // example gains

    // register pid tick as callback (Timers module) called every 10ms
    Timers_registerPidCallback(&pos_pid);
}

void Stepper_moveToAngle(float angle_deg, float vmax_rpm)
{
    // convert angle to pulses (absolute)
    int64_t pulses = (int64_t)roundf((angle_deg / 360.0f) * (float)PPR);
    target_pulses = pulses;

    // configure PID limits: vmax
    float vmax_pps = (vmax_rpm * (float)PPR) / 60.0f;
    PID_setOutputLimit(&pos_pid, -vmax_pps, vmax_pps);

    // enable motor
    gpio_write(PIN_EN, 0); // enable low (adjust if board differs)

    moving = true;
}

void Stepper_stop(void)
{
    // simple approach: clear target and let pid drive to zero; or stop timer immediately
    moving = false;
    Timers_stopStepTimer();
    gpio_write(PIN_STEP, 0);
}

float Stepper_getAngle(void)
{
    int64_t enc = Encoder_getCounts(); // encoder counts (increments)
    // Convert encoder counts to motor microstep pulses.
    // Encoder CPR = 500 counts per revolution; we must map encoder units to motor microsteps.
    const int ENC_CPR = 500;
    float revolutions = (float)enc / (float)ENC_CPR;
    float pulses = revolutions * (float)PPR;
    float angle = (pulses / (float)PPR) * 360.0f;
    return angle;
}

// gpio helpers (placeholders)
static void gpio_write(int pin, int val)
{
    (void)pin; (void)val;
    // TODO: replace with SysConfig-generated GPIO write calls, e.g. GPIO_write(PIN_x, val);
}

static void gpio_init_pin(int pin)
{
    (void)pin;
    // TODO: configure pin direction via SysConfig or driverlib
}
