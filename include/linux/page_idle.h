/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_MM_PAGE_IDLE_H
#define _LINUX_MM_PAGE_IDLE_H

#include <linux/bitops.h>
#include <linux/page-flags.h>
#include <linux/page_ext.h>

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_PAGE_IDLE_FLAG
=======
#ifdef CONFIG_IDLE_PAGE_TRACKING
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifdef CONFIG_PAGE_IDLE_FLAG
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#ifdef CONFIG_64BIT
static inline bool page_is_young(struct page *page)
{
	return PageYoung(page);
}

static inline void set_page_young(struct page *page)
{
	SetPageYoung(page);
}

static inline bool test_and_clear_page_young(struct page *page)
{
	return TestClearPageYoung(page);
}

static inline bool page_is_idle(struct page *page)
{
	return PageIdle(page);
}

static inline void set_page_idle(struct page *page)
{
	SetPageIdle(page);
}

static inline void clear_page_idle(struct page *page)
{
	ClearPageIdle(page);
}
#else /* !CONFIG_64BIT */
/*
 * If there is not enough space to store Idle and Young bits in page flags, use
 * page ext flags instead.
 */
extern struct page_ext_operations page_idle_ops;

static inline bool page_is_young(struct page *page)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	if (unlikely(!page_ext))
		return false;

	return test_bit(PAGE_EXT_YOUNG, &page_ext->flags);
}

static inline void set_page_young(struct page *page)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	if (unlikely(!page_ext))
		return;

	set_bit(PAGE_EXT_YOUNG, &page_ext->flags);
}

static inline bool test_and_clear_page_young(struct page *page)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	if (unlikely(!page_ext))
		return false;

	return test_and_clear_bit(PAGE_EXT_YOUNG, &page_ext->flags);
}

static inline bool page_is_idle(struct page *page)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	if (unlikely(!page_ext))
		return false;

	return test_bit(PAGE_EXT_IDLE, &page_ext->flags);
}

static inline void set_page_idle(struct page *page)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	if (unlikely(!page_ext))
		return;

	set_bit(PAGE_EXT_IDLE, &page_ext->flags);
}

static inline void clear_page_idle(struct page *page)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	if (unlikely(!page_ext))
		return;

	clear_bit(PAGE_EXT_IDLE, &page_ext->flags);
}
#endif /* CONFIG_64BIT */

<<<<<<< HEAD
<<<<<<< HEAD
#else /* !CONFIG_PAGE_IDLE_FLAG */
=======
#else /* !CONFIG_IDLE_PAGE_TRACKING */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#else /* !CONFIG_PAGE_IDLE_FLAG */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

static inline bool page_is_young(struct page *page)
{
	return false;
}

static inline void set_page_young(struct page *page)
{
}

static inline bool test_and_clear_page_young(struct page *page)
{
	return false;
}

static inline bool page_is_idle(struct page *page)
{
	return false;
}

static inline void set_page_idle(struct page *page)
{
}

static inline void clear_page_idle(struct page *page)
{
}

<<<<<<< HEAD
<<<<<<< HEAD
#endif /* CONFIG_PAGE_IDLE_FLAG */
=======
#endif /* CONFIG_IDLE_PAGE_TRACKING */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#endif /* CONFIG_PAGE_IDLE_FLAG */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* _LINUX_MM_PAGE_IDLE_H */
