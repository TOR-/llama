#include <stdio.h>

#include <kernel/tty.h>
#include <arch/i386/time.h>
#include <arch/i386/gdt.h>
#include <arch/i386/int.h>
#include <arch/i386/keyboard.h>

void kernel_early(void)
{
  timer_ticks = 0;
  terminal_initialize();
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  __asm__ __volatile__ ("sti");
  keyboard_install();
  timer_install();
}

void kernel_main(void)
{
  printf("Buongiorno Msr Llama!\n");
  timer_wait(18);
  printf("Waited 1 second");
  for(;;) asm("hlt");
  //printf("                    ___~___\n                ___(__((__(___                  /|>\n \   (_((_((_((_((_(                 / |\\\n \   \\=-:--:--:--:--:--.              /__|_\\\n\   ______________\\_o__o__o__o__o_/_______________\\____/__________________________\n^^^^^^^^^^^^^^ ---------------- ^^^^^^^^^^^^^^ ----- ^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^ --------------- ^^^^^^^^^^^^^^^ ---- ^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^ ------------ ^^^^^^^^^^^^^^^^^  -- ^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^^^ --------- ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^^^^^ ------ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
  //printf("%x%x%x",5,0x50,0x506);
}
