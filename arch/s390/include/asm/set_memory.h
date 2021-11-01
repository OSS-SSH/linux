/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASMS390_SET_MEMORY_H
#define _ASMS390_SET_MEMORY_H

#include <linux/mutex.h>

extern struct mutex cpa_mutex;

#define SET_MEMORY_RO	1UL
#define SET_MEMORY_RW	2UL
#define SET_MEMORY_NX	4UL
#define SET_MEMORY_X	8UL
<<<<<<< HEAD
<<<<<<< HEAD
#define SET_MEMORY_4K  16UL
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define SET_MEMORY_4K  16UL
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

int __set_memory(unsigned long addr, int numpages, unsigned long flags);

static inline int set_memory_ro(unsigned long addr, int numpages)
{
	return __set_memory(addr, numpages, SET_MEMORY_RO);
}

static inline int set_memory_rw(unsigned long addr, int numpages)
{
	return __set_memory(addr, numpages, SET_MEMORY_RW);
}

static inline int set_memory_nx(unsigned long addr, int numpages)
{
	return __set_memory(addr, numpages, SET_MEMORY_NX);
}

static inline int set_memory_x(unsigned long addr, int numpages)
{
	return __set_memory(addr, numpages, SET_MEMORY_X);
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static inline int set_memory_4k(unsigned long addr, int numpages)
{
	return __set_memory(addr, numpages, SET_MEMORY_4K);
}

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif
