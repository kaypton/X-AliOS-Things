#ifndef __LIBC_STRING_H__
#define __LIBC_STRING_H__

#include <stdint.h>
#include <stddef.h>

void * memchr(const void *s, int c, size_t length);
void * memcpy(void *dest, const void *src, size_t n);
#define memmove memcpy
int memcmp(const void *s1, const void *s2, size_t n);
void * memset(void *s, int c, size_t n);

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t maxlen);
char * strrchr(const char *cp, int ch);
char * strchr(const char *cp, int ch);
int strcmp(const char *s1, const char *s2);

#endif 
