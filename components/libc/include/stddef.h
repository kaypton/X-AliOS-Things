#ifndef __LIBC_STDDEF_H__
#define __LIBC_STDDEF_H__

#include <sys/_types.h>
#include <sys/_null.h>

#ifndef _PTRDIFF_T_DECLARED
typedef	__ptrdiff_t	ptrdiff_t;
#define	_PTRDIFF_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif 

#ifndef _SSIZE_T_DECLARED
typedef __ssize_t ssize_t;
#define _SSIZE_T_DECLARED
#endif 

#endif 