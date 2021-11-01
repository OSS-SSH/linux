#ifndef _ASM_POWERPC_ASM_CONST_H
#define _ASM_POWERPC_ASM_CONST_H

#ifdef __ASSEMBLY__
#  define stringify_in_c(...)	__VA_ARGS__
#  define ASM_CONST(x)		x
#else
/* This version of stringify will deal with commas... */
#  define __stringify_in_c(...)	#__VA_ARGS__
#  define stringify_in_c(...)	__stringify_in_c(__VA_ARGS__) " "
#  define __ASM_CONST(x)	x##UL
#  define ASM_CONST(x)		__ASM_CONST(x)
#endif

<<<<<<< HEAD
<<<<<<< HEAD
#define UPD_CONSTR "<>"
=======
/*
 * Inline assembly memory constraint
 *
 * GCC 4.9 doesn't properly handle pre update memory constraint "m<>"
 *
 */
#if defined(GCC_VERSION) && GCC_VERSION < 50000
#define UPD_CONSTR ""
#else
#define UPD_CONSTR "<>"
#endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define UPD_CONSTR "<>"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* _ASM_POWERPC_ASM_CONST_H */
