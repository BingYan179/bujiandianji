/*
 * main.c
 * Example application: initializes board, stepper, encoder and provides a simple UART CLI.
 * CCS SysConfig note: this file expects SysConfig to generate ti_msp_dl_config.h and
 * timer/uart/qei peripheral config. Replace HAL calls where noted if your SysConfig names differ.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "board_init.h"
#include "stepper.h"
#include "encoder.h"
#include "pid.h"
#include "timers.h"

// Debug UART (K230) usage: we'll use uart_print to interact; SysConfig should map UART2 to K230 pins

int main(void)
{
    Board_init();

    // Initialize modules
    Encoder_init();
    Stepper_init();
    PID_init();
    Timers_init();

    // Start PID scheduler (e.g., 10 ms tick) and leave STEP timer stopped until motion
    Timers_startPidScheduler(10); // 10 ms

    // Example: move to 45 degrees at 100 RPM
    float test_angle = 45.0f;
    float vmax_rpm = 100.0f;
    Stepper_moveToAngle(test_angle, vmax_rpm);

    // Simple CLI loop (blocking) - expects commands like: GOTO 90.0\n
    char line[64];
    while (1)
    {
        // In a real SysConfig project, replace this with non-blocking UART reads
        if (uart_readline(line, sizeof(line))) {
            if (strncmp(line, "GOTO", 4) == 0) {
                float angle = 0.0f;
                if (sscanf(line + 4, "%f", &angle) == 1) {
                    Stepper_moveToAngle(angle, 150.0f); // default vmax 150 RPM
                    uart_printf("Moving to %.2f deg\r\n", angle);
                } else {
                    uart_printf("Usage: GOTO <angle_deg>\r\n");
                }
            } else if (strncmp(line, "POS", 3) == 0) {
                float pos = Stepper_getAngle();
                uart_printf("Position: %.3f deg\r\n", pos);
            } else if (strncmp(line, "STOP", 4) == 0) {
                Stepper_stop();
                uart_printf("Stopped\r\n");
            } else {
                uart_printf("Unknown cmd\r\n");
            }
        }

        // background tasks, could sleep or wait for events
    }

    return 0;
}
