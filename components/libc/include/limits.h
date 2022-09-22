#ifndef __LIBC_LIMITS_H__
#define __LIBC_LIMITS_H__

#include <sys/cdefs.h>
#include <machine/_limits.h>

#define	CHAR_BIT	__CHAR_BIT	/* number of bits in a char */

#define	SCHAR_MAX	__SCHAR_MAX	/* max value for a signed char */
#define	SCHAR_MIN	__SCHAR_MIN	/* min value for a signed char */

#define	UCHAR_MAX	__UCHAR_MAX	/* max value for an unsigned char */

#ifdef __CHAR_UNSIGNED__
#define	CHAR_MAX	UCHAR_MAX	/* max value for a char */
#define	CHAR_MIN	0		/* min value for a char */
#else
#define	CHAR_MAX	SCHAR_MAX
#define	CHAR_MIN	SCHAR_MIN
#endif

#define	USHRT_MAX	__USHRT_MAX	/* max value for an unsigned short */
#define	SHRT_MAX	__SHRT_MAX	/* max value for a short */
#define	SHRT_MIN	__SHRT_MIN	/* min value for a short */

#define	UINT_MAX	__UINT_MAX	/* max value for an unsigned int */
#define	INT_MAX		__INT_MAX	/* max value for an int */
#define	INT_MIN		__INT_MIN	/* min value for an int */

#define	ULONG_MAX	__ULONG_MAX	/* max for an unsigned long */
#define	LONG_MAX	__LONG_MAX	/* max for a long */
#define	LONG_MIN	__LONG_MIN	/* min for a long */

#ifdef __LONG_LONG_SUPPORTED
#define	ULLONG_MAX	__ULLONG_MAX	/* max for an unsigned long long */
#define	LLONG_MAX	__LLONG_MAX	/* max for a long long */
#define	LLONG_MIN	__LLONG_MIN	/* min for a long long */
#endif

#if __POSIX_VISIBLE || __XSI_VISIBLE
#define	SSIZE_MAX	__SSIZE_MAX	/* max value for an ssize_t */
#endif

#if __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE
#define	SIZE_T_MAX	__SIZE_T_MAX	/* max value for a size_t */

#define	OFF_MAX		__OFF_MAX	/* max value for an off_t */
#define	OFF_MIN		__OFF_MIN	/* min value for an off_t */
#endif

#if __BSD_VISIBLE
#define	GID_MAX		UINT_MAX	/* max value for a gid_t */
#define	UID_MAX		UINT_MAX	/* max value for a uid_t */

#define	UQUAD_MAX	(__UQUAD_MAX)	/* max value for a uquad_t */
#define	QUAD_MAX	(__QUAD_MAX)	/* max value for a quad_t */
#define	QUAD_MIN	(__QUAD_MIN)	/* min value for a quad_t */
#endif

#if __XSI_VISIBLE || __POSIX_VISIBLE >= 200809
#define	LONG_BIT	__LONG_BIT
#define	WORD_BIT	__WORD_BIT
#endif

#if __POSIX_VISIBLE
#define	MQ_PRIO_MAX	64
#endif

#endif 
