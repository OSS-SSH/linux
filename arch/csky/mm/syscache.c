// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microsystems co.,ltd.

#include <linux/syscalls.h>
#include <asm/page.h>
#include <asm/cacheflush.h>
#include <asm/cachectl.h>

SYSCALL_DEFINE3(cacheflush,
		void __user *, addr,
		unsigned long, bytes,
		int, cache)
{
	switch (cache) {
	case BCACHE:
<<<<<<< HEAD
		flush_icache_mm_range(current->mm,
				(unsigned long)addr,
				(unsigned long)addr + bytes);
		fallthrough;
=======
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a
	case DCACHE:
		dcache_wb_range((unsigned long)addr,
				(unsigned long)addr + bytes);
		if (cache != BCACHE)
			break;
		fallthrough;
	case ICACHE:
		flush_icache_mm_range(current->mm,
				(unsigned long)addr,
				(unsigned long)addr + bytes);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
