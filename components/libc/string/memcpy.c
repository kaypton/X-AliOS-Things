#include <string.h>

void *
memcpy(void *dest, const void *src, size_t n)
{
    char *_dest = dest;
    const char *_src = src;

    if(n == 0 || _dest == _src)
        goto done;

    while(n > 0)
    {
        *_dest++ = *_src++;
        n--;
    }
done:
    return _dest;
}


