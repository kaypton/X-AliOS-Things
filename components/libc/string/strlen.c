#include <string.h>

size_t strlen(const char *s)
{
    size_t len = 0;
    for (const char *_s = s; *_s; _s++) {
        len += 1;
    }
    return len;
}

