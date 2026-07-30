#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include <stdbool.h>

void Stepper_init(void);

// Non-blocking: command motor to move to absolute angle (deg), sets internal target
void Stepper_moveToAngle(float angle_deg, float vmax_rpm);

// Stop motion immediately (safe stop with decel)
void Stepper_stop(void);

// Query current estimated angle from encoder
float Stepper_getAngle(void);

#endif // STEPPER_H
