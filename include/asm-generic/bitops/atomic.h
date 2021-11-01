/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_GENERIC_BITOPS_ATOMIC_H_
#define _ASM_GENERIC_BITOPS_ATOMIC_H_

#include <linux/atomic.h>
#include <linux/compiler.h>
#include <asm/barrier.h>

/*
 * Implementation of atomic bitops using atomic-fetch ops.
 * See Documentation/atomic_bitops.txt for details.
 */

<<<<<<< HEAD
<<<<<<< HEAD
static __always_inline void
arch_set_bit(unsigned int nr, volatile unsigned long *p)
{
	p += BIT_WORD(nr);
	arch_atomic_long_or(BIT_MASK(nr), (atomic_long_t *)p);
}

static __always_inline void
arch_clear_bit(unsigned int nr, volatile unsigned long *p)
{
	p += BIT_WORD(nr);
	arch_atomic_long_andnot(BIT_MASK(nr), (atomic_long_t *)p);
}

static __always_inline void
arch_change_bit(unsigned int nr, volatile unsigned long *p)
{
	p += BIT_WORD(nr);
	arch_atomic_long_xor(BIT_MASK(nr), (atomic_long_t *)p);
}

static __always_inline int
arch_test_and_set_bit(unsigned int nr, volatile unsigned long *p)
=======
static __always_inline void set_bit(unsigned int nr, volatile unsigned long *p)
=======
static __always_inline void
arch_set_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	p += BIT_WORD(nr);
	arch_atomic_long_or(BIT_MASK(nr), (atomic_long_t *)p);
}

static __always_inline void
arch_clear_bit(unsigned int nr, volatile unsigned long *p)
{
	p += BIT_WORD(nr);
	arch_atomic_long_andnot(BIT_MASK(nr), (atomic_long_t *)p);
}

static __always_inline void
arch_change_bit(unsigned int nr, volatile unsigned long *p)
{
	p += BIT_WORD(nr);
	arch_atomic_long_xor(BIT_MASK(nr), (atomic_long_t *)p);
}

<<<<<<< HEAD
static inline int test_and_set_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static __always_inline int
arch_test_and_set_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	long old;
	unsigned long mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	if (READ_ONCE(*p) & mask)
		return 1;

<<<<<<< HEAD
<<<<<<< HEAD
	old = arch_atomic_long_fetch_or(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

static __always_inline int
arch_test_and_clear_bit(unsigned int nr, volatile unsigned long *p)
=======
	old = atomic_long_fetch_or(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

static inline int test_and_clear_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	old = arch_atomic_long_fetch_or(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

static __always_inline int
arch_test_and_clear_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	long old;
	unsigned long mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	if (!(READ_ONCE(*p) & mask))
		return 0;

<<<<<<< HEAD
<<<<<<< HEAD
	old = arch_atomic_long_fetch_andnot(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

static __always_inline int
arch_test_and_change_bit(unsigned int nr, volatile unsigned long *p)
=======
	old = atomic_long_fetch_andnot(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

static inline int test_and_change_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	old = arch_atomic_long_fetch_andnot(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

static __always_inline int
arch_test_and_change_bit(unsigned int nr, volatile unsigned long *p)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	long old;
	unsigned long mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
<<<<<<< HEAD
<<<<<<< HEAD
	old = arch_atomic_long_fetch_xor(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

#include <asm-generic/bitops/instrumented-atomic.h>

=======
	old = atomic_long_fetch_xor(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	old = arch_atomic_long_fetch_xor(mask, (atomic_long_t *)p);
	return !!(old & mask);
}

#include <asm-generic/bitops/instrumented-atomic.h>

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif /* _ASM_GENERIC_BITOPS_ATOMIC_H */
