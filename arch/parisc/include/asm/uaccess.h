/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __PARISC_UACCESS_H
#define __PARISC_UACCESS_H

/*
 * User space memory access functions
 */
#include <asm/page.h>
#include <asm/cache.h>

#include <linux/bug.h>
#include <linux/string.h>

<<<<<<< HEAD
=======
#define KERNEL_DS	((mm_segment_t){0})
#define USER_DS 	((mm_segment_t){1})

#define uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

#define get_fs()	(current_thread_info()->addr_limit)
#define set_fs(x)	(current_thread_info()->addr_limit = (x))

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
/*
 * Note that since kernel addresses are in a separate address space on
 * parisc, we don't need to do anything for access_ok().
 * We just let the page fault handler do the right thing. This also means
 * that put_user is the same as __put_user, etc.
 */

#define access_ok(uaddr, size)	\
	( (uaddr) == (uaddr) )

#define put_user __put_user
#define get_user __get_user

#if !defined(CONFIG_64BIT)
<<<<<<< HEAD
#define LDD_USER(sr, val, ptr)	__get_user_asm64(sr, val, ptr)
#define STD_USER(sr, x, ptr)	__put_user_asm64(sr, x, ptr)
#else
#define LDD_USER(sr, val, ptr)	__get_user_asm(sr, val, "ldd", ptr)
#define STD_USER(sr, x, ptr)	__put_user_asm(sr, "std", x, ptr)
=======
#define LDD_USER(val, ptr)	__get_user_asm64(val, ptr)
#define STD_USER(x, ptr)	__put_user_asm64(x, ptr)
#else
#define LDD_USER(val, ptr)	__get_user_asm(val, "ldd", ptr)
#define STD_USER(x, ptr)	__put_user_asm("std", x, ptr)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif

/*
 * The exception table contains two values: the first is the relative offset to
 * the address of the instruction that is allowed to fault, and the second is
 * the relative offset to the address of the fixup routine. Since relative
 * addresses are used, 32bit values are sufficient even on 64bit kernel.
 */

#define ARCH_HAS_RELATIVE_EXTABLE
struct exception_table_entry {
	int insn;	/* relative address of insn that is allowed to fault. */
	int fixup;	/* relative address of fixup routine */
};

#define ASM_EXCEPTIONTABLE_ENTRY( fault_addr, except_addr )\
	".section __ex_table,\"aw\"\n"			   \
	".word (" #fault_addr " - .), (" #except_addr " - .)\n\t" \
	".previous\n"

/*
 * ASM_EXCEPTIONTABLE_ENTRY_EFAULT() creates a special exception table entry
 * (with lowest bit set) for which the fault handler in fixup_exception() will
 * load -EFAULT into %r8 for a read or write fault, and zeroes the target
 * register in case of a read fault in get_user().
 */
#define ASM_EXCEPTIONTABLE_ENTRY_EFAULT( fault_addr, except_addr )\
	ASM_EXCEPTIONTABLE_ENTRY( fault_addr, except_addr + 1)

<<<<<<< HEAD
#define __get_user_internal(sr, val, ptr)		\
=======
/*
 * load_sr2() preloads the space register %%sr2 - based on the value of
 * get_fs() - with either a value of 0 to access kernel space (KERNEL_DS which
 * is 0), or with the current value of %%sr3 to access user space (USER_DS)
 * memory. The following __get_user_asm() and __put_user_asm() functions have
 * %%sr2 hard-coded to access the requested memory.
 */
#define load_sr2() \
	__asm__(" or,=  %0,%%r0,%%r0\n\t"	\
		" mfsp %%sr3,%0\n\t"		\
		" mtsp %0,%%sr2\n\t"		\
		: : "r"(get_fs()) : )

#define __get_user_internal(val, ptr)			\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
({							\
	register long __gu_err __asm__ ("r8") = 0;	\
							\
	switch (sizeof(*(ptr))) {			\
<<<<<<< HEAD
	case 1: __get_user_asm(sr, val, "ldb", ptr); break; \
	case 2: __get_user_asm(sr, val, "ldh", ptr); break; \
	case 4: __get_user_asm(sr, val, "ldw", ptr); break; \
	case 8: LDD_USER(sr, val, ptr); break;		\
=======
	case 1: __get_user_asm(val, "ldb", ptr); break;	\
	case 2: __get_user_asm(val, "ldh", ptr); break; \
	case 4: __get_user_asm(val, "ldw", ptr); break; \
	case 8: LDD_USER(val, ptr); break;		\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	default: BUILD_BUG();				\
	}						\
							\
	__gu_err;					\
})

#define __get_user(val, ptr)				\
({							\
<<<<<<< HEAD
	__get_user_internal("%%sr3,", val, ptr);	\
})

#define __get_user_asm(sr, val, ldx, ptr)		\
{							\
	register long __gu_val;				\
							\
	__asm__("1: " ldx " 0(" sr "%2),%0\n"		\
=======
	load_sr2();					\
	__get_user_internal(val, ptr);			\
})

#define __get_user_asm(val, ldx, ptr)			\
{							\
	register long __gu_val;				\
							\
	__asm__("1: " ldx " 0(%%sr2,%2),%0\n"		\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		"9:\n"					\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	\
		: "=r"(__gu_val), "=r"(__gu_err)        \
		: "r"(ptr), "1"(__gu_err));		\
							\
	(val) = (__force __typeof__(*(ptr))) __gu_val;	\
}

<<<<<<< HEAD
#define HAVE_GET_KERNEL_NOFAULT
#define __get_kernel_nofault(dst, src, type, err_label)	\
{							\
	type __z;					\
	long __err;					\
	__err = __get_user_internal("%%sr0,", __z, (type *)(src)); \
	if (unlikely(__err))				\
		goto err_label;				\
	else						\
		*(type *)(dst) = __z;			\
}


#if !defined(CONFIG_64BIT)

#define __get_user_asm64(sr, val, ptr)			\
=======
#if !defined(CONFIG_64BIT)

#define __get_user_asm64(val, ptr)			\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
{							\
	union {						\
		unsigned long long	l;		\
		__typeof__(*(ptr))	t;		\
	} __gu_tmp;					\
							\
	__asm__("   copy %%r0,%R0\n"			\
<<<<<<< HEAD
		"1: ldw 0(" sr "%2),%0\n"		\
		"2: ldw 4(" sr "%2),%R0\n"		\
=======
		"1: ldw 0(%%sr2,%2),%0\n"		\
		"2: ldw 4(%%sr2,%2),%R0\n"		\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		"9:\n"					\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(2b, 9b)	\
		: "=&r"(__gu_tmp.l), "=r"(__gu_err)	\
		: "r"(ptr), "1"(__gu_err));		\
							\
	(val) = __gu_tmp.t;				\
}

#endif /* !defined(CONFIG_64BIT) */


<<<<<<< HEAD
#define __put_user_internal(sr, x, ptr)				\
=======
#define __put_user_internal(x, ptr)				\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
({								\
	register long __pu_err __asm__ ("r8") = 0;      	\
        __typeof__(*(ptr)) __x = (__typeof__(*(ptr)))(x);	\
								\
	switch (sizeof(*(ptr))) {				\
<<<<<<< HEAD
	case 1: __put_user_asm(sr, "stb", __x, ptr); break;	\
	case 2: __put_user_asm(sr, "sth", __x, ptr); break;	\
	case 4: __put_user_asm(sr, "stw", __x, ptr); break;	\
	case 8: STD_USER(sr, __x, ptr); break;			\
=======
	case 1: __put_user_asm("stb", __x, ptr); break;		\
	case 2: __put_user_asm("sth", __x, ptr); break;		\
	case 4: __put_user_asm("stw", __x, ptr); break;		\
	case 8: STD_USER(__x, ptr); break;			\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	default: BUILD_BUG();					\
	}							\
								\
	__pu_err;						\
})

#define __put_user(x, ptr)					\
({								\
<<<<<<< HEAD
	__put_user_internal("%%sr3,", x, ptr);			\
})

#define __put_kernel_nofault(dst, src, type, err_label)		\
{								\
	type __z = *(type *)(src);				\
	long __err;						\
	__err = __put_user_internal("%%sr0,", __z, (type *)(dst)); \
	if (unlikely(__err))					\
		goto err_label;					\
}



=======
	load_sr2();						\
	__put_user_internal(x, ptr);				\
})

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

/*
 * The "__put_user/kernel_asm()" macros tell gcc they read from memory
 * instead of writing. This is because they do not write to any memory
 * gcc knows about, so there are no aliasing issues. These macros must
 * also be aware that fixups are executed in the context of the fault,
 * and any registers used there must be listed as clobbers.
 * r8 is already listed as err.
 */

<<<<<<< HEAD
#define __put_user_asm(sr, stx, x, ptr)				\
	__asm__ __volatile__ (					\
		"1: " stx " %2,0(" sr "%1)\n"			\
		"9:\n"						\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)		\
		: "=r"(__pu_err)				\
=======
#define __put_user_asm(stx, x, ptr)                         \
	__asm__ __volatile__ (                              \
		"1: " stx " %2,0(%%sr2,%1)\n"		    \
		"9:\n"					    \
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	    \
		: "=r"(__pu_err)                            \
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		: "r"(ptr), "r"(x), "0"(__pu_err))


#if !defined(CONFIG_64BIT)

<<<<<<< HEAD
#define __put_user_asm64(sr, __val, ptr) do {			\
	__asm__ __volatile__ (					\
		"1: stw %2,0(" sr "%1)\n"			\
		"2: stw %R2,4(" sr "%1)\n"			\
		"9:\n"						\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)		\
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(2b, 9b)		\
		: "=r"(__pu_err)				\
		: "r"(ptr), "r"(__val), "0"(__pu_err));		\
=======
#define __put_user_asm64(__val, ptr) do {	    	    \
	__asm__ __volatile__ (				    \
		"1: stw %2,0(%%sr2,%1)\n"		    \
		"2: stw %R2,4(%%sr2,%1)\n"		    \
		"9:\n"					    \
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(1b, 9b)	    \
		ASM_EXCEPTIONTABLE_ENTRY_EFAULT(2b, 9b)	    \
		: "=r"(__pu_err)                            \
		: "r"(ptr), "r"(__val), "0"(__pu_err));	    \
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
} while (0)

#endif /* !defined(CONFIG_64BIT) */


/*
 * Complex access routines -- external declarations
 */

extern long strncpy_from_user(char *, const char __user *, long);
<<<<<<< HEAD
extern __must_check unsigned lclear_user(void __user *, unsigned long);
extern __must_check long strnlen_user(const char __user *src, long n);
/*
 * Complex access routines -- macros
 */

=======
extern unsigned lclear_user(void __user *, unsigned long);
extern long lstrnlen_user(const char __user *, long);
/*
 * Complex access routines -- macros
 */
#define user_addr_max() (~0UL)

#define strnlen_user lstrnlen_user
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#define clear_user lclear_user
#define __clear_user lclear_user

unsigned long __must_check raw_copy_to_user(void __user *dst, const void *src,
					    unsigned long len);
unsigned long __must_check raw_copy_from_user(void *dst, const void __user *src,
					    unsigned long len);
<<<<<<< HEAD
=======
unsigned long __must_check raw_copy_in_user(void __user *dst, const void __user *src,
					    unsigned long len);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#define INLINE_COPY_TO_USER
#define INLINE_COPY_FROM_USER

struct pt_regs;
int fixup_exception(struct pt_regs *regs);

#endif /* __PARISC_UACCESS_H */
