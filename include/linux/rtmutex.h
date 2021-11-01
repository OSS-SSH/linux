/* SPDX-License-Identifier: GPL-2.0 */
/*
 * RT Mutexes: blocking mutual exclusion locks with PI support
 *
 * started by Ingo Molnar and Thomas Gleixner:
 *
 *  Copyright (C) 2004-2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2006, Timesys Corp., Thomas Gleixner <tglx@timesys.com>
 *
 * This file contains the public data structure and API definitions.
 */

#ifndef __LINUX_RT_MUTEX_H
#define __LINUX_RT_MUTEX_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/rbtree_types.h>
#include <linux/spinlock_types_raw.h>

extern int max_lock_depth; /* for sysctl */

struct rt_mutex_base {
	raw_spinlock_t		wait_lock;
	struct rb_root_cached   waiters;
	struct task_struct	*owner;
};

#define __RT_MUTEX_BASE_INITIALIZER(rtbasename)				\
{									\
	.wait_lock = __RAW_SPIN_LOCK_UNLOCKED(rtbasename.wait_lock),	\
	.waiters = RB_ROOT_CACHED,					\
	.owner = NULL							\
}

/**
 * rt_mutex_base_is_locked - is the rtmutex locked
 * @lock: the mutex to be queried
 *
 * Returns true if the mutex is locked, false if unlocked.
 */
static inline bool rt_mutex_base_is_locked(struct rt_mutex_base *lock)
{
	return READ_ONCE(lock->owner) != NULL;
}

extern void rt_mutex_base_init(struct rt_mutex_base *rtb);

=======
=======
#include <linux/compiler.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/linkage.h>
#include <linux/rbtree_types.h>
#include <linux/spinlock_types_raw.h>

extern int max_lock_depth; /* for sysctl */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
struct rt_mutex_base {
	raw_spinlock_t		wait_lock;
	struct rb_root_cached   waiters;
	struct task_struct	*owner;
};

#define __RT_MUTEX_BASE_INITIALIZER(rtbasename)				\
{									\
	.wait_lock = __RAW_SPIN_LOCK_UNLOCKED(rtbasename.wait_lock),	\
	.waiters = RB_ROOT_CACHED,					\
	.owner = NULL							\
}

/**
 * rt_mutex_base_is_locked - is the rtmutex locked
 * @lock: the mutex to be queried
 *
 * Returns true if the mutex is locked, false if unlocked.
 */
static inline bool rt_mutex_base_is_locked(struct rt_mutex_base *lock)
{
	return READ_ONCE(lock->owner) != NULL;
}

extern void rt_mutex_base_init(struct rt_mutex_base *rtb);

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/**
 * The rt_mutex structure
 *
 * @wait_lock:	spinlock to protect the structure
 * @waiters:	rbtree root to enqueue waiters in priority order;
 *              caches top-waiter (leftmost node).
 * @owner:	the mutex owner
 */
struct rt_mutex {
<<<<<<< HEAD
<<<<<<< HEAD
	struct rt_mutex_base	rtmutex;
=======
	raw_spinlock_t		wait_lock;
	struct rb_root_cached   waiters;
	struct task_struct	*owner;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct rt_mutex_base	rtmutex;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map	dep_map;
#endif
};

struct rt_mutex_waiter;
struct hrtimer_sleeper;

#ifdef CONFIG_DEBUG_RT_MUTEXES
extern void rt_mutex_debug_task_free(struct task_struct *tsk);
#else
static inline void rt_mutex_debug_task_free(struct task_struct *tsk) { }
#endif

#define rt_mutex_init(mutex) \
do { \
	static struct lock_class_key __key; \
	__rt_mutex_init(mutex, __func__, &__key); \
} while (0)

#ifdef CONFIG_DEBUG_LOCK_ALLOC
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define __DEP_MAP_RT_MUTEX_INITIALIZER(mutexname)	\
	.dep_map = {					\
		.name = #mutexname,			\
		.wait_type_inner = LD_WAIT_SLEEP,	\
	}
<<<<<<< HEAD
=======
#define __DEP_MAP_RT_MUTEX_INITIALIZER(mutexname) \
	, .dep_map = { .name = #mutexname }
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#else
#define __DEP_MAP_RT_MUTEX_INITIALIZER(mutexname)
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define __RT_MUTEX_INITIALIZER(mutexname)				\
{									\
	.rtmutex = __RT_MUTEX_BASE_INITIALIZER(mutexname.rtmutex),	\
	__DEP_MAP_RT_MUTEX_INITIALIZER(mutexname)			\
}
<<<<<<< HEAD
=======
#define __RT_MUTEX_INITIALIZER(mutexname) \
	{ .wait_lock = __RAW_SPIN_LOCK_UNLOCKED(mutexname.wait_lock) \
	, .waiters = RB_ROOT_CACHED \
	, .owner = NULL \
	__DEP_MAP_RT_MUTEX_INITIALIZER(mutexname)}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#define DEFINE_RT_MUTEX(mutexname) \
	struct rt_mutex mutexname = __RT_MUTEX_INITIALIZER(mutexname)

<<<<<<< HEAD
<<<<<<< HEAD
=======
/**
 * rt_mutex_is_locked - is the mutex locked
 * @lock: the mutex to be queried
 *
 * Returns 1 if the mutex is locked, 0 if unlocked.
 */
static inline int rt_mutex_is_locked(struct rt_mutex *lock)
{
	return lock->owner != NULL;
}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
extern void __rt_mutex_init(struct rt_mutex *lock, const char *name, struct lock_class_key *key);

#ifdef CONFIG_DEBUG_LOCK_ALLOC
extern void rt_mutex_lock_nested(struct rt_mutex *lock, unsigned int subclass);
#define rt_mutex_lock(lock) rt_mutex_lock_nested(lock, 0)
#else
extern void rt_mutex_lock(struct rt_mutex *lock);
#define rt_mutex_lock_nested(lock, subclass) rt_mutex_lock(lock)
#endif

extern int rt_mutex_lock_interruptible(struct rt_mutex *lock);
extern int rt_mutex_trylock(struct rt_mutex *lock);

extern void rt_mutex_unlock(struct rt_mutex *lock);

#endif
