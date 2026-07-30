#include "pid.h"
#include <stddef.h>

static void (*output_cb)(float) = NULL;

void PID_init(PID_t *pid, float Kp, float Ki, float Kd)
{
    if (!pid) return;
    pid->Kp = Kp; pid->Ki = Ki; pid->Kd = Kd;
    pid->integral = 0.0f; pid->last_error = 0.0f;
    pid->out_min = -1e6f; pid->out_max = 1e6f;
}

float PID_compute(PID_t *pid, float error, float dt)
{
    if (!pid) return 0.0f;
    pid->integral += error * dt;
    float derivative = (error - pid->last_error) / dt;
    float out = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
    if (out > pid->out_max) out = pid->out_max;
    if (out < pid->out_min) out = pid->out_min;
    pid->last_error = error;
    if (output_cb) output_cb(out);
    return out;
}

void PID_setOutputLimit(PID_t *pid, float min, float max)
{
    if (!pid) return;
    pid->out_min = min; pid->out_max = max;
}

void PID_registerOutputCallback(void (*cb)(float))
{
    output_cb = cb;
}
