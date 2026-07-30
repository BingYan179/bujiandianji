# MSPM0G3507 Stepper Control (D36A + MS42C) - CCS SysConfig project skeleton

This branch contains a CCS SysConfig-compatible skeleton project to control a MS42C stepper motor (200 steps/rev) driven by a D36A (STEP/DIR) with 16x microstepping and a 500 CPR incremental encoder (A/B). The project is prepared for CCS v20.5.0.28__1.11.0.

Files included:
- src/main.c                : example main, CLI over UART, K230-compatible serial stub
- src/board_init.*          : SysConfig glue and board-level init
- src/stepper.*             : stepper control (non-blocking, closed-loop position PID)
- src/encoder.*             : encoder (QEI/incremental) interface
- src/pid.*                 : PID controller used for position→velocity
- src/timers.*              : timer abstraction (STEP timer + PID scheduler)
- README.md                 : import/build/flash instructions and SysConfig guide
- sysconfig-guides.txt      : step-by-step SysConfig settings to create in CCS
- debug/serial_k230.txt     : K230 serial notes / example frames

IMPORTANT
- This skeleton expects you to run SysConfig in CCS to generate device headers (ti_msp_dl_config.h, etc.). Do NOT hand-edit generated files.
- Pin mapping (accepted): STEP=PB15, DIR=PB16, EN=PB0, ENC_A=PA15, ENC_B=PA16.
- PPR = 200 * 16 = 3200 pulses per rev.

See README.md for instructions to import into CCS, configure SysConfig, and build/flash.
