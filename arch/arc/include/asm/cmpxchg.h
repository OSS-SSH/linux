/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_ARC_CMPXCHG_H
#define __ASM_ARC_CMPXCHG_H

<<<<<<< HEAD
#include <linux/build_bug.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#include <linux/types.h>

#include <asm/barrier.h>
#include <asm/smp.h>

#ifdef CONFIG_ARC_HAS_LLSC

<<<<<<< HEAD
/*
 * if (*ptr == @old)
 *      *ptr = @new
 */
#define __cmpxchg(ptr, old, new)					\
({									\
	__typeof__(*(ptr)) _prev;					\
									\
	__asm__ __volatile__(						\
	"1:	llock  %0, [%1]	\n"					\
	"	brne   %0, %2, 2f	\n"				\
	"	scond  %3, [%1]	\n"					\
	"	bnz     1b		\n"				\
	"2:				\n"				\
	: "=&r"(_prev)	/* Early clobber prevent reg reuse */		\
	: "r"(ptr),	/* Not "m": llock only supports reg */		\
	  "ir"(old),							\
	  "r"(new)	/* Not "ir": scond can't take LIMM */		\
	: "cc",								\
	  "memory");	/* gcc knows memory is clobbered */		\
									\
	_prev;								\
})

#define arch_cmpxchg_relaxed(ptr, old, new)				\
({									\
	__typeof__(ptr) _p_ = (ptr);					\
	__typeof__(*(ptr)) _o_ = (old);					\
	__typeof__(*(ptr)) _n_ = (new);					\
	__typeof__(*(ptr)) _prev_;					\
									\
	switch(sizeof((_p_))) {						\
	case 4:								\
		_prev_ = __cmpxchg(_p_, _o_, _n_);			\
		break;							\
	default:							\
		BUILD_BUG();						\
	}								\
	_prev_;								\
})

#else

#define arch_cmpxchg(ptr, old, new)				        \
({									\
	volatile __typeof__(ptr) _p_ = (ptr);				\
	__typeof__(*(ptr)) _o_ = (old);					\
	__typeof__(*(ptr)) _n_ = (new);					\
	__typeof__(*(ptr)) _prev_;					\
	unsigned long __flags;						\
									\
	BUILD_BUG_ON(sizeof(_p_) != 4);					\
									\
	/*								\
	 * spin lock/unlock provide the needed smp_mb() before/after	\
	 */								\
	atomic_ops_lock(__flags);					\
	_prev_ = *_p_;							\
	if (_prev_ == _o_)						\
		*_p_ = _n_;						\
	atomic_ops_unlock(__flags);					\
	_prev_;								\
})

#endif

/*
 * xchg
 */
#ifdef CONFIG_ARC_HAS_LLSC

#define __xchg(ptr, val)						\
({									\
	__asm__ __volatile__(						\
	"	ex  %0, [%1]	\n"	/* set new value */	        \
	: "+r"(val)							\
	: "r"(ptr)							\
	: "memory");							\
	_val_;		/* get old value */				\
})

#define arch_xchg_relaxed(ptr, val)					\
({									\
	__typeof__(ptr) _p_ = (ptr);					\
	__typeof__(*(ptr)) _val_ = (val);				\
									\
	switch(sizeof(*(_p_))) {					\
	case 4:								\
		_val_ = __xchg(_p_, _val_);				\
		break;							\
	default:							\
		BUILD_BUG();						\
	}								\
	_val_;								\
})

#else  /* !CONFIG_ARC_HAS_LLSC */

/*
 * EX instructions is baseline and present in !LLSC too. But in this
 * regime it still needs use @atomic_ops_lock spinlock to allow interop
 * with cmpxchg() which uses spinlock in !LLSC
 * (llist.h use xchg and cmpxchg on sama data)
 */

#define arch_xchg(ptr, val)					        \
({									\
	__typeof__(ptr) _p_ = (ptr);					\
	__typeof__(*(ptr)) _val_ = (val);				\
									\
	unsigned long __flags;						\
									\
	atomic_ops_lock(__flags);					\
									\
	__asm__ __volatile__(						\
	"	ex  %0, [%1]	\n"					\
	: "+r"(_val_)							\
	: "r"(_p_)							\
	: "memory");							\
									\
	atomic_ops_unlock(__flags);					\
	_val_;								\
})

#endif

=======
static inline unsigned long
__cmpxchg(volatile void *ptr, unsigned long expected, unsigned long new)
{
	unsigned long prev;

	/*
	 * Explicit full memory barrier needed before/after as
	 * LLOCK/SCOND themselves don't provide any such semantics
	 */
	smp_mb();

	__asm__ __volatile__(
	"1:	llock   %0, [%1]	\n"
	"	brne    %0, %2, 2f	\n"
	"	scond   %3, [%1]	\n"
	"	bnz     1b		\n"
	"2:				\n"
	: "=&r"(prev)	/* Early clobber, to prevent reg reuse */
	: "r"(ptr),	/* Not "m": llock only supports reg direct addr mode */
	  "ir"(expected),
	  "r"(new)	/* can't be "ir". scond can't take LIMM for "b" */
	: "cc", "memory"); /* so that gcc knows memory is being written here */

	smp_mb();

	return prev;
}

#else /* !CONFIG_ARC_HAS_LLSC */

static inline unsigned long
__cmpxchg(volatile void *ptr, unsigned long expected, unsigned long new)
{
	unsigned long flags;
	int prev;
	volatile unsigned long *p = ptr;

	/*
	 * spin lock/unlock provide the needed smp_mb() before/after
	 */
	atomic_ops_lock(flags);
	prev = *p;
	if (prev == expected)
		*p = new;
	atomic_ops_unlock(flags);
	return prev;
}

#endif

#define arch_cmpxchg(ptr, o, n) ({			\
	(typeof(*(ptr)))__cmpxchg((ptr),		\
				  (unsigned long)(o),	\
				  (unsigned long)(n));	\
})

/*
 * atomic_cmpxchg is same as cmpxchg
 *   LLSC: only different in data-type, semantics are exactly same
 *  !LLSC: cmpxchg() has to use an external lock atomic_ops_lock to guarantee
 *         semantics, and this lock also happens to be used by atomic_*()
 */
#define arch_atomic_cmpxchg(v, o, n) ((int)arch_cmpxchg(&((v)->counter), (o), (n)))


/*
 * xchg (reg with memory) based on "Native atomic" EX insn
 */
static inline unsigned long __xchg(unsigned long val, volatile void *ptr,
				   int size)
{
	extern unsigned long __xchg_bad_pointer(void);

	switch (size) {
	case 4:
		smp_mb();

		__asm__ __volatile__(
		"	ex  %0, [%1]	\n"
		: "+r"(val)
		: "r"(ptr)
		: "memory");

		smp_mb();

		return val;
	}
	return __xchg_bad_pointer();
}

#define _xchg(ptr, with) ((typeof(*(ptr)))__xchg((unsigned long)(with), (ptr), \
						 sizeof(*(ptr))))

/*
 * xchg() maps directly to ARC EX instruction which guarantees atomicity.
 * However in !LLSC config, it also needs to be use @atomic_ops_lock spinlock
 * due to a subtle reason:
 *  - For !LLSC, cmpxchg() needs to use that lock (see above) and there is lot
 *    of  kernel code which calls xchg()/cmpxchg() on same data (see llist.h)
 *    Hence xchg() needs to follow same locking rules.
 *
 * Technically the lock is also needed for UP (boils down to irq save/restore)
 * but we can cheat a bit since cmpxchg() atomic_ops_lock() would cause irqs to
 * be disabled thus can't possibly be interrupted/preempted/clobbered by xchg()
 * Other way around, xchg is one instruction anyways, so can't be interrupted
 * as such
 */

#if !defined(CONFIG_ARC_HAS_LLSC) && defined(CONFIG_SMP)

#define arch_xchg(ptr, with)		\
({					\
	unsigned long flags;		\
	typeof(*(ptr)) old_val;		\
					\
	atomic_ops_lock(flags);		\
	old_val = _xchg(ptr, with);	\
	atomic_ops_unlock(flags);	\
	old_val;			\
})

#else

#define arch_xchg(ptr, with)  _xchg(ptr, with)

#endif

/*
 * "atomic" variant of xchg()
 * REQ: It needs to follow the same serialization rules as other atomic_xxx()
 * Since xchg() doesn't always do that, it would seem that following definition
 * is incorrect. But here's the rationale:
 *   SMP : Even xchg() takes the atomic_ops_lock, so OK.
 *   LLSC: atomic_ops_lock are not relevant at all (even if SMP, since LLSC
 *         is natively "SMP safe", no serialization required).
 *   UP  : other atomics disable IRQ, so no way a difft ctxt atomic_xchg()
 *         could clobber them. atomic_xchg() itself would be 1 insn, so it
 *         can't be clobbered by others. Thus no serialization required when
 *         atomic_xchg is involved.
 */
#define arch_atomic_xchg(v, new) (arch_xchg(&((v)->counter), new))

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif
