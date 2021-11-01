// SPDX-License-Identifier: GPL-2.0
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/once.h>
#include <linux/random.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <linux/module.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

struct once_work {
	struct work_struct work;
	struct static_key_true *key;
<<<<<<< HEAD
<<<<<<< HEAD
	struct module *module;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct module *module;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

static void once_deferred(struct work_struct *w)
{
	struct once_work *work;

	work = container_of(w, struct once_work, work);
	BUG_ON(!static_key_enabled(work->key));
	static_branch_disable(work->key);
<<<<<<< HEAD
<<<<<<< HEAD
	module_put(work->module);
	kfree(work);
}

static void once_disable_jump(struct static_key_true *key, struct module *mod)
=======
	kfree(work);
}

static void once_disable_jump(struct static_key_true *key)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	module_put(work->module);
	kfree(work);
}

static void once_disable_jump(struct static_key_true *key, struct module *mod)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct once_work *w;

	w = kmalloc(sizeof(*w), GFP_ATOMIC);
	if (!w)
		return;

	INIT_WORK(&w->work, once_deferred);
	w->key = key;
<<<<<<< HEAD
<<<<<<< HEAD
	w->module = mod;
	__module_get(mod);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	w->module = mod;
	__module_get(mod);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	schedule_work(&w->work);
}

static DEFINE_SPINLOCK(once_lock);

bool __do_once_start(bool *done, unsigned long *flags)
	__acquires(once_lock)
{
	spin_lock_irqsave(&once_lock, *flags);
	if (*done) {
		spin_unlock_irqrestore(&once_lock, *flags);
		/* Keep sparse happy by restoring an even lock count on
		 * this lock. In case we return here, we don't call into
		 * __do_once_done but return early in the DO_ONCE() macro.
		 */
		__acquire(once_lock);
		return false;
	}

	return true;
}
EXPORT_SYMBOL(__do_once_start);

void __do_once_done(bool *done, struct static_key_true *once_key,
<<<<<<< HEAD
<<<<<<< HEAD
		    unsigned long *flags, struct module *mod)
=======
		    unsigned long *flags)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		    unsigned long *flags, struct module *mod)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	__releases(once_lock)
{
	*done = true;
	spin_unlock_irqrestore(&once_lock, *flags);
<<<<<<< HEAD
<<<<<<< HEAD
	once_disable_jump(once_key, mod);
=======
	once_disable_jump(once_key);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	once_disable_jump(once_key, mod);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}
EXPORT_SYMBOL(__do_once_done);
