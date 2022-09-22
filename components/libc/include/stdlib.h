#ifndef __LIBC_STDLIB_H__
#define __LIBC_STDLIB_H__

#include <sys/ctypes.h>
#include <stddef.h>

unsigned long strtoul(const char *nptr, char **endptr, int base);

#endif 
