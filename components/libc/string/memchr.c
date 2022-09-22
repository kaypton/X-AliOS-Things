

#include <sys/cdefs.h>
#include <string.h>

void * 
memchr(const void *s, int c, size_t length)
{
    if(length != 0) 
    {
        const unsigned char *p = s;

        do {
			if (*p++ == (unsigned char)c)
				return ((void *)(uintptr_t)(p - 1));
		} while (--length != 0);
    }
    return (NULL);
}



