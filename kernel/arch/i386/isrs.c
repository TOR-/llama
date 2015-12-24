#include <stdio.h>
#include <arch/i386/gdt.h>
#include <arch/i386/int.h>

void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

/* This is a very repetitive function... it's not hard, it's
 *  just annoying. As you can see, we set the first 32 entries
 *  in the IDT to the first 32 ISRs. We can't use a for loop
 *  for this, because there is no way to get the function names
 *  that correspond to that given entry. We set the access
 *  flags to 0x8E. This means that the entry is present, is
 *  running in ring 0 (kernel level), and has the lower 5 bits
 *  set to the required '14', which is represented by 'E' in
 *  hex. */
void isrs_install()
{
  idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
  idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
  idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
  idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
  idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
  idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
  idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
  idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);

  idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
  idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
  idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
  idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
  idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
  idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
  idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
  idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
  
  idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
  idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
  idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
  idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
  idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
  idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
  idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
  idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);

  idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
  idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
  idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
  idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
  idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
  idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
  idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
  idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
}

/* This is a simple string array. It contains the message that
 *  corresponds to each and every exception. We get the correct
 *  message by accessing like:
 *  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
  {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
  };

/* All of our Exception handling Interrupt Service Routines will
 *  point to this function. This will tell us what exception has
 *  happened! Right now, we simply halt the system by hitting an
 *  endless loop. All ISRs disable interrupts while they are being
 *  serviced as a 'locking' mechanism to prevent an IRQ from
 *  happening and messing up kernel data structures */
void fault_handler(struct regs *r)
{
  if (r->int_no < 32)
    {	
      printf(exception_messages[r->int_no]);
      printf(" Exception. System Halted!\n");
      switch(r->int_no)
	{
	case 3:
	  printf("ds:%d es:%d fs:%d gs:%d\n",r->ds,r->es,r->fs,r->gs);
	  printf("edi:%d esi:%d ebp:%d eax:%d ebx:%d ecx:%d edx:%d\n", 
		 r->edi,r->esi,r->ebp,r->eax,r->ebx,r->ecx,r->edx);
	  printf("eip:%d cs:%d eflags:%d useresp:%d ss:%d\n",
		 r->eip,r->cs,r->eflags,r->useresp,r->ss);
	  printf("int_no:%d err_code:%d\n", r->int_no, r->err_code);
	  break;
	default:
	  break; 
	}  
      for (;;);
    }
}

