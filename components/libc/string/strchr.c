#include <string.h>


char *
strchr(const char *cp, int ch)
{
	char *p;

	p = __DECONST(char *, cp);
	for (;; ++p) {
		if (*p == ch)
			return (p);
		if (*p == '\0')
			return NULL;
	}
}

