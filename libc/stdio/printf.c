#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void print(const char* data, size_t data_length)
{
  for ( size_t i = 0; i < data_length; i++ )
    putchar((int) ((const unsigned char*) data)[i]);
}

int printf(const char* restrict format, ...)
{
  va_list parameters;
  va_start(parameters, format);

  int written = 0;
  size_t amount;
  bool rejected_bad_specifier = false;

  while ( *format != '\0' )
    {
      if ( *format != '%' )
	{
	print_c:
	  amount = 1;
	  while ( format[amount] && format[amount] != '%' )
	    amount++;
	  print(format, amount);
	  format += amount;
	  written += amount;
	  continue;
	}

      const char* format_begun_at = format;

      if ( *(++format) == '%' )
	goto print_c;

      if ( rejected_bad_specifier )
	{
	incomprehensible_conversion:
	  rejected_bad_specifier = true;
	  format = format_begun_at;
	  goto print_c;
	}

      if ( *format == 'c' )
	{
	  format++;
	  char c = (char) va_arg(parameters, int /* char promotes to int */);
	  print(&c, sizeof(c));
	}
      else if ( *format == 's' )
	{
	  format++;
	  const char* s = va_arg(parameters, const char*);
	  print(s, strlen(s));
	}
      else if ( *format == 'd' )
	{
	  format++;
	  int d = va_arg(parameters, const int);
	  if ( d < 0 )
	    {
	      print('-', 1);
	      d *= -1;
	    }
	  char s[sizeof d]; //CAUTION Compile time only
	  itoa(d,s);
	  print(s, strlen(s));
	}
      else if ( *format == 'x' )
	{
	  format++;
	  /*int hex = va_arg(parameters, int);
	    char *buf = NULL;
	    int i=0;
	    int j=30;
	    printf("hex");
	    for(;hex!=0;i++)
	    {
	    printf("%d%d\n",i,hex);
	    switch(hex%16){
	    case 0x0:
	    buf[i] = '0';
	    break;
	    case 0x1:
	    buf[i] = '1';
	    break;
	    case 0x2:
	    buf[i] = '2';
	    break;
	    case 0x3:
	    buf[i] = '3';
	    break;
	    case 0x4:
	    buf[i] = '4';
	    break;
	    case 0x5:
	    buf[i] = '5';
	    break;
	    case 0x6:
	    buf[i] = '6';
	    break;
	    case 0x7:
	    buf[i] = '7';
	    break;
	    case 0x8:
	    buf[i] = '8';
	    break;
	    case 0x9:
	    buf[i] = '9';
	    break;
	    case 0xA:
	    buf[i] = 'A';
	    break;
	    case 0xB:
	    buf[i] = 'B';
	    break;
	    case 0xC:
	    buf[i] = 'C';
	    break;
	    case 0xD:
	    buf[i] = 'D';
	    break;
	    case 0xE:
	    buf[i] = 'E';
	    break;
	    case 0xF:
	    buf[i] = 'F';
	    break;
	    default:
	    print("NaN",3);
	    break;
	    }
	    hex = hex/16;
	    }
	    i=0;
	    j=30;
	    char retbuf[30];
	    for(;i++,j--;i<30) retbuf[i] = buf[j];
	    print("0x",2);
	    print(retbuf, strlen(retbuf));*/
	}
      else
	{
	  goto incomprehensible_conversion;
	}
    }
	
  va_end(parameters);
	
  return written;
}
