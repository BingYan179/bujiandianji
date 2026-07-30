#ifndef PID_H
#define PID_H

#include <stdint.h>

typedef struct {
    float Kp, Ki, Kd;
    float integral;
    float last_error;
    float out_min, out_max;
} PID_t;

void PID_init(PID_t *pid, float Kp, float Ki, float Kd);
float PID_compute(PID_t *pid, float error, float dt);
void PID_setOutputLimit(PID_t *pid, float min, float max);
void PID_registerOutputCallback(void (*cb)(float));

#endif // PID_H
