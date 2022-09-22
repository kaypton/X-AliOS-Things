#include <string.h>

void *
memset(void *s, int c, size_t n)
{
	char *_s;

	for (_s = (char *)s; n--; )
		*_s++ = c;
	return s;
}

