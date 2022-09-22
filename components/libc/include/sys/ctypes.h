#ifndef __LIBC_CTYPE_H__
#define	__LIBC_CTYPE_H__

static __inline int
isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static __inline int
isascii(int c)
{
	return ((c & ~0x7f) == 0);
}

static __inline int
isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static __inline int
islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

static __inline int
isalpha(int c)
{
	return (isupper(c) || islower(c));
}

static __inline int
isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static __inline int
isxdigit(int c)
{
	return (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

static __inline int
isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

static __inline int
toupper(int c)
{
	return (c - 0x20 * ((c >= 'a') && (c <= 'z')));
}

static __inline int
tolower(int c)
{
	return (c + 0x20 * ((c >= 'A') && (c <= 'Z')));
}

#endif /* !_SYS_CTYPE_H_ */