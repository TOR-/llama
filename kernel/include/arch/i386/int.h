#ifndef _INT_H
#define _INT_H

void idt_install(void);
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void isrs_install();

void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_install();

#endif
