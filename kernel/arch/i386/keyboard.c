#include <stdio.h>
#include <arch/i386/inoutb.h>
#include <arch/i386/int.h>
#include <arch/i386/keyboard.h>

unsigned char kbdus[128] =
  {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
    '9', '0', '-', '=', '\b',	/* Backspace */
    '\t',			/* Tab */
    'q', 'w', 'e', 'r',	/* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
    '\'', '`',   0,		/* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
    'm', ',', '.', '/',   0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
  };	

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
  unsigned int scancode;
  unsigned int scancodebuf[5];
  unsigned int *sc = scancodebuf;
  /* Read from the keyboard's data buffer */
  *sc = inb(0x60);
  
  printf("\nscancode = %x ", scancode);
  /* If the top bit of the byte we read from the keyboard is
   *  set, that means that a key has just been released */
  if (*sc & 0x80)
    {
      /* see if user released shift, alt, or control keys */
      switch(*sc)
	{
	case 0xaa:
	  special_keys.shift = 0;
	  printf("LSHIFT RELEASED");
	  //lshift
	  break;
	case 0xb6:
	  special_keys.shift = 0;
	  printf("RSHIFT RELEASED");
	  //rshift
	  break;
	case 0x9d:
	  if (sc[0] == 0xe0) {
	    special_keys.control = 0; //rctl
	    sc--;
	  }	  
	  special_keys.control = 0; //lctl
	  printf("CTL RELEASED");
	  break;
	case 0xe0:
	  sc++;
	  //rctl
	  //0xe0 0x1d
	  //0xe0 0x9d
	  break;
	case 0xb8:
	  if (sc[0] == 0xe0){
	    special_keys.alt = 0; //ralt
	    sc--;
	  }
	  special_keys.alt = 0; //lalt
	  printf("ALT RELEASED");
	  //lalt
	  break;
	  //ralt
	  //0xe0 0x38
	  //0xe0 0xb8
	default:
	  break;
	}
    }
  else
    {
      switch(*sc)
	{      /* Key just pressed */
	case 0x2A:
	  special_keys.shift = 1;
	  printf("LSHIFT PRESSED");
	  //lshift
	  break;
	case 0x36:
	  special_keys.shift = 1;
	  printf("RSHIFT PRESSED");
	  //rshift
	  break;
	case 0x1D:
	  if (sc[0] == 0xe0) {
	    special_keys.control = 1; //rctl
	    sc--;
	  }	  
	  special_keys.control = 1; //lctl
	  printf("CTL PRESSED");
	  break;
	case 0xe0:
	  sc++;
	  //rctl
	  //0xe0 0x1d
	  //0xe0 0x9d
	  break;
	case 0x38:
	  if (sc[0] == 0xe0){
	    special_keys.alt = 1; //ralt
	    sc--;
	  }
	  special_keys.alt = 1; //lalt
	  //lalt
	  printf("ALT PRESSED");
	  break;
	default:	  
	  printf("%c",kbdus[*sc]);
	  break;
	}
    }
}

void keyboard_install()
{
  special_keys.shift = 0;
  special_keys.control = 0;
  special_keys.alt = 0;

  irq_install_handler(1, keyboard_handler);
}
