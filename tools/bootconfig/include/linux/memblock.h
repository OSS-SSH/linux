/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _XBC_LINUX_MEMBLOCK_H
#define _XBC_LINUX_MEMBLOCK_H

#include <stdlib.h>

<<<<<<< HEAD
#define SMP_CACHE_BYTES	0
#define memblock_alloc(size, align)	malloc(size)
#define memblock_free_ptr(paddr, size)	free(paddr)
=======
#define __pa(addr)	(addr)
#define SMP_CACHE_BYTES	0
#define memblock_alloc(size, align)	malloc(size)
#define memblock_free(paddr, size)	free(paddr)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#endif
