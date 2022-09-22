#include <string.h>

char *
strrchr(const char *cp, int ch)
{
	char *p, *save;

	p = __DECONST(char *, cp);
	for (save = NULL;; ++p) {
		if (*p == ch)
			save = p;
		if (*p == '\0')
			return save;
	}
}

