#ifndef _TIME_H
#define _TIME_H
#include <stdint.h>
/* This will keep track of how many ticks that the system
*  has been running for */
volatile unsigned long timer_ticks;
/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install();

void timer_wait(unsigned long ticks);
#endif
