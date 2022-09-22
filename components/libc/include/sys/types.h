#ifndef __LIBC_TYPES_H__
#define __LIBC_TYPES_H__

#include <sys/_stdint.h>
#include <sys/cdefs.h>

#define offsetof(type, field) __offsetof(type, field)

typedef __uint64_t u_quad_t;
typedef __int64_t quad_t;
typedef quad_t * qaddr_t;

#endif 