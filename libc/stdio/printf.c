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

#define MAX_INT_SIZE 12

int printint ( int i, int capital, int base )
{
  char retbuf[MAX_INT_SIZE];
  int r = 0, neg = 0, u = i;
  char *bc;
  if (i == 0)
    return 0;
  else if (i < 0)
    {
      u *= -1;
      neg = 1;
    }
  for (int h = 0; h < MAX_INT_SIZE; h++)
	{
		retbuf[h]='\0';
	}
  bc = retbuf + MAX_INT_SIZE - 1;
  *--bc = '\0';
  while (u) {
		r = u % base;
		if( r >= 10 )
			r += capital - '0' - 10;
		*--bc = r + '0';
		u /= base;
	}
	
	if(neg) *--bc = '-';
	print(retbuf, MAX_INT_SIZE);
	return 0;
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
	  printint(d, 'a' , 10);
	}
      else if ( *format == 'x' )
	{
	  format++;
		int x = va_arg(parameters, const int);
		printint(x, 'a' , 16);
	}
      else
	{
	  goto incomprehensible_conversion;
	}
    }
	
  va_end(parameters);
	
  return written;
}
