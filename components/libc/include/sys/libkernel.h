#ifndef __SYS_LIBKERNEL_H__
#define __SYS_LIBKERNEL_H__

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

struct stdout_ops
{
    void (*putc) (char);
};

int k_printf(char const *fmt, ...);

int k_vprintf(
    char const *fmt, 
    void (*func)(int, void*),
    void *arg, int radix, va_list ap);

int k_snprintf(char *str, size_t size, const char *format, ...);
int k_vsnprintf(char *str, size_t size, const char *format, va_list ap);

#endif 

