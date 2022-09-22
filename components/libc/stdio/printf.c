#include <stdio.h>

#include <sys/cdefs.h>
#include <stdarg.h>

int printf(const char * __restrict format, ...)
{
    int retval;
    va_list ap;
    va_start(ap, format);

    // TODO 

    va_end(ap);
    return retval;
}



