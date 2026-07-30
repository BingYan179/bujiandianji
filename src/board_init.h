#ifndef BOARD_INIT_H
#define BOARD_INIT_H

#include <stdint.h>

void Board_init(void);

// Minimal UART helpers used by main.c - map these to your SysConfig UART driver
int uart_readline(char *buf, int len); // blocking convenience for demo
void uart_printf(const char *fmt, ...);

#endif // BOARD_INIT_H
