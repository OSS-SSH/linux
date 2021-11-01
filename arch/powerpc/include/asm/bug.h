/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_POWERPC_BUG_H
#define _ASM_POWERPC_BUG_H
#ifdef __KERNEL__

#include <asm/asm-compat.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <asm/extable.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <asm/extable.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#ifdef CONFIG_BUG

#ifdef __ASSEMBLY__
#include <asm/asm-offsets.h>
#ifdef CONFIG_DEBUG_BUGVERBOSE
.macro EMIT_BUG_ENTRY addr,file,line,flags
	 .section __bug_table,"aw"
5001:	 .4byte \addr - 5001b, 5002f - 5001b
	 .short \line, \flags
	 .org 5001b+BUG_ENTRY_SIZE
	 .previous
	 .section .rodata,"a"
5002:	 .asciz "\file"
	 .previous
.endm
#else
.macro EMIT_BUG_ENTRY addr,file,line,flags
	 .section __bug_table,"aw"
5001:	 .4byte \addr - 5001b
	 .short \flags
	 .org 5001b+BUG_ENTRY_SIZE
	 .previous
.endm
#endif /* verbose */

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
.macro EMIT_WARN_ENTRY addr,file,line,flags
	EX_TABLE(\addr,\addr+4)
	EMIT_BUG_ENTRY \addr,\file,\line,\flags
.endm

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#else /* !__ASSEMBLY__ */
/* _EMIT_BUG_ENTRY expects args %0,%1,%2,%3 to be FILE, LINE, flags and
   sizeof(struct bug_entry), respectively */
#ifdef CONFIG_DEBUG_BUGVERBOSE
#define _EMIT_BUG_ENTRY				\
	".section __bug_table,\"aw\"\n"		\
	"2:\t.4byte 1b - 2b, %0 - 2b\n"		\
	"\t.short %1, %2\n"			\
	".org 2b+%3\n"				\
	".previous\n"
#else
#define _EMIT_BUG_ENTRY				\
	".section __bug_table,\"aw\"\n"		\
	"2:\t.4byte 1b - 2b\n"			\
	"\t.short %2\n"				\
	".org 2b+%3\n"				\
	".previous\n"
#endif

#define BUG_ENTRY(insn, flags, ...)			\
	__asm__ __volatile__(				\
		"1:	" insn "\n"			\
		_EMIT_BUG_ENTRY				\
		: : "i" (__FILE__), "i" (__LINE__),	\
		  "i" (flags),				\
		  "i" (sizeof(struct bug_entry)),	\
		  ##__VA_ARGS__)

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define WARN_ENTRY(insn, flags, label, ...)		\
	asm_volatile_goto(				\
		"1:	" insn "\n"			\
		EX_TABLE(1b, %l[label])			\
		_EMIT_BUG_ENTRY				\
		: : "i" (__FILE__), "i" (__LINE__),	\
		  "i" (flags),				\
		  "i" (sizeof(struct bug_entry)),	\
		  ##__VA_ARGS__ : : label)

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * BUG_ON() and WARN_ON() do their best to cooperate with compile-time
 * optimisations. However depending on the complexity of the condition
 * some compiler versions may not produce optimal results.
 */

#define BUG() do {						\
	BUG_ENTRY("twi 31, 0, 0", 0);				\
	unreachable();						\
} while (0)
<<<<<<< HEAD
<<<<<<< HEAD
#define HAVE_ARCH_BUG

#define __WARN_FLAGS(flags) do {				\
	__label__ __label_warn_on;				\
								\
	WARN_ENTRY("twi 31, 0, 0", BUGFLAG_WARNING | (flags), __label_warn_on); \
	unreachable();						\
								\
__label_warn_on:						\
	break;							\
} while (0)

#ifdef CONFIG_PPC64
=======

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define HAVE_ARCH_BUG

#define __WARN_FLAGS(flags) do {				\
	__label__ __label_warn_on;				\
								\
	WARN_ENTRY("twi 31, 0, 0", BUGFLAG_WARNING | (flags), __label_warn_on); \
	unreachable();						\
								\
__label_warn_on:						\
	break;							\
} while (0)

#ifdef CONFIG_PPC64
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define BUG_ON(x) do {						\
	if (__builtin_constant_p(x)) {				\
		if (x)						\
			BUG();					\
	} else {						\
		BUG_ENTRY(PPC_TLNEI " %4, 0", 0, "r" ((__force long)(x)));	\
	}							\
} while (0)

<<<<<<< HEAD
<<<<<<< HEAD
#define WARN_ON(x) ({						\
	bool __ret_warn_on = false;				\
	do {							\
		if (__builtin_constant_p((x))) {		\
			if (!(x)) 				\
				break; 				\
			__WARN();				\
			__ret_warn_on = true;			\
		} else {					\
			__label__ __label_warn_on;		\
								\
			WARN_ENTRY(PPC_TLNEI " %4, 0",		\
				   BUGFLAG_WARNING | BUGFLAG_TAINT(TAINT_WARN),	\
				   __label_warn_on,		\
				   "r" ((__force long)(x)));	\
			break;					\
__label_warn_on:						\
			__ret_warn_on = true;			\
		}						\
	} while (0);						\
	unlikely(__ret_warn_on);				\
})

#define HAVE_ARCH_BUG_ON
#define HAVE_ARCH_WARN_ON
#endif

=======
#define __WARN_FLAGS(flags) BUG_ENTRY("twi 31, 0, 0", BUGFLAG_WARNING | (flags))

=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define WARN_ON(x) ({						\
	bool __ret_warn_on = false;				\
	do {							\
		if (__builtin_constant_p((x))) {		\
			if (!(x)) 				\
				break; 				\
			__WARN();				\
			__ret_warn_on = true;			\
		} else {					\
			__label__ __label_warn_on;		\
								\
			WARN_ENTRY(PPC_TLNEI " %4, 0",		\
				   BUGFLAG_WARNING | BUGFLAG_TAINT(TAINT_WARN),	\
				   __label_warn_on,		\
				   "r" ((__force long)(x)));	\
			break;					\
__label_warn_on:						\
			__ret_warn_on = true;			\
		}						\
	} while (0);						\
	unlikely(__ret_warn_on);				\
})

#define HAVE_ARCH_BUG_ON
#define HAVE_ARCH_WARN_ON
<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#endif

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif /* __ASSEMBLY __ */
#else
#ifdef __ASSEMBLY__
.macro EMIT_BUG_ENTRY addr,file,line,flags
.endm
<<<<<<< HEAD
<<<<<<< HEAD
.macro EMIT_WARN_ENTRY addr,file,line,flags
.endm
#else /* !__ASSEMBLY__ */
#define _EMIT_BUG_ENTRY
#define _EMIT_WARN_ENTRY
=======
#else /* !__ASSEMBLY__ */
#define _EMIT_BUG_ENTRY
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
.macro EMIT_WARN_ENTRY addr,file,line,flags
.endm
#else /* !__ASSEMBLY__ */
#define _EMIT_BUG_ENTRY
#define _EMIT_WARN_ENTRY
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif
#endif /* CONFIG_BUG */

#include <asm-generic/bug.h>

#ifndef __ASSEMBLY__

struct pt_regs;
void hash__do_page_fault(struct pt_regs *);
void bad_page_fault(struct pt_regs *, int);
extern void _exception(int, struct pt_regs *, int, unsigned long);
extern void _exception_pkey(struct pt_regs *, unsigned long, int);
extern void die(const char *, struct pt_regs *, long);
void die_mce(const char *str, struct pt_regs *regs, long err);
extern bool die_will_crash(void);
extern void panic_flush_kmsg_start(void);
extern void panic_flush_kmsg_end(void);
#endif /* !__ASSEMBLY__ */

#endif /* __KERNEL__ */
#endif /* _ASM_POWERPC_BUG_H */
