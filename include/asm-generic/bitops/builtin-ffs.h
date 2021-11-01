/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_GENERIC_BITOPS_BUILTIN_FFS_H_
#define _ASM_GENERIC_BITOPS_BUILTIN_FFS_H_

/**
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
<<<<<<< HEAD
 * differs in spirit from ffz (man ffs).
=======
 * differs in spirit from the above ffz (man ffs).
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
 */
#define ffs(x) __builtin_ffs(x)

#endif
