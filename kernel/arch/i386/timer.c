#include <arch/i386/time.h>
#include <arch/i386/int.h>

/* By default, the timer fires at 18.222Hz */
void timer_handler(struct regs *r)
{

  /* Increment our 'tick count' */
  timer_ticks++;
}

/* This will continuously loop until the given time has
*  been reached */
void timer_wait(unsigned long ticks)
{
    unsigned long eticks;
 
    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks) 
    {
        __asm__ __volatile__ ("sti//hlt//cli");
    }
}
/* Sets up the system clock by installing the timer handler
 *  into IRQ0 */
void timer_install()
{
  /* Installs 'timer_handler' to IRQ0 */
  irq_install_handler(0, timer_handler);
}
