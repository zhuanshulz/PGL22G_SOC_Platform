#ifndef _PANGO_M1_PRINTK_H_
#define _PANGO_M1_PRINTK_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "PANGO_M1.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

#define DEBUG
#ifdef 	DEBUG
#define DEBUG_P(format, arg...) printf(format, ## arg)
#else
#define DEBUG_P(format, arg...) do {} while(0)	 
#endif	 
	 
extern void put_char(char c);
extern void print_num(uint32_t num, int base);
extern void print_str(const char *p);
extern void print_hex(uint32_t v, int digits);
extern void print_hex2(uint32_t hex);
extern void print_dec(uint32_t v);
extern void print_flt(double flt);
extern void printk(char *fmt, ...);
#ifdef __cplusplus
}
#endif

#endif //_PANGO_M1_PRINTK_H_
