#ifndef _KEYBOARD_H
#define _KEYBOARD_H

void keyboard_install();

struct Special_Keys{
unsigned int shift:1;
unsigned int control:1;
unsigned int  alt:1;
}special_keys;

#endif 
