#ifndef __SYS_TYPES_H__
#define __SYS_TYPES_H__

#include <sys/cdefs.h>

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
#if __SIZEOF_LONG__ == 8
typedef long __int64_t;
typedef unsigned long __uint64_t;
#elif __SIZEOF_LONG__ == 4 
__extension__ 
typedef long long __int64_t;
__extension__ 
typedef unsigned long long __uint64_t;
#else 
#error unsupported long size 
#endif 

typedef	__int64_t	__intmax_t;
typedef	__uint64_t	__uintmax_t;

#if __SIZEOF_POINTER__ == 8
typedef __int64_t __intptr_t;
typedef __int64_t __intfptr_t;
typedef __uint64_t __uintptr_t;
typedef __uint64_t __uintfptr_t;
#elif __SIZEOF_POINTER__ == 4 
typedef __int32_t __intptr_t;
typedef __int32_t __intfptr_t;
typedef __uint32_t __uintptr_t;
typedef __uint32_t __uintfptr_t;
#else 
#error unsupport pointer size 
#endif 

#if __SIZEOF_SIZE_T__ == 8
typedef	__uint64_t	__size_t;	
typedef	__int64_t	__ssize_t;	
#elif __SIZEOF_SIZE_T__ == 4
typedef	__uint32_t	__size_t;	
typedef	__int32_t	__ssize_t;	
#else
#error unsupported size_t size
#endif

#if __SIZEOF_PTRDIFF_T__ == 8
typedef __int64_t __ptrdiff_t;
#elif __SIZEOF_PTRDIFF_T__ == 4
typedef __int32_t __ptrdiff_t;
#else 
#error unsupport ptrdiff_t size 
#endif 

#endif 