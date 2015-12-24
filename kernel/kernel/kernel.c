#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <kernel/tty.h>
#include <arch/i386/gdt.h>
#include <arch/i386/int.h>

void kernel_early(void)
{
  terminal_initialize();
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  __asm__ __volatile__ ("sti");
}

void kernel_main(void)
{
  printf("Buongiorno Msr Llama!\n");
  asm ("int $3");//Testing Breakpoint Exception
  char *s = "string";
  reverse(s);
  char inta[20];
  itoa(90,inta);
  printf("itoa(90,inta);\ninta = %s", inta);
  printf("4 = %d", 4);
  /* printf("                    ___~___\n                ___(__((__(___                  /|>\n \
     (_((_((_((_((_(                 / |\\\n\
     \\=-:--:--:--:--:--.              /__|_\\\n\
     ______________\\_o__o__o__o__o_/_______________\\____/__________________________\n^^^^^^^^^^^^^^ ---------------- ^^^^^^^^^^^^^^ ----- ^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^ --------------- ^^^^^^^^^^^^^^^ ---- ^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^ ------------ ^^^^^^^^^^^^^^^^^  -- ^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^^^ --------- ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^^^^^ ------ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");*/
  //printf("%x%x%x",5,0x50,0x506);
}
