/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ALPHA_COMPILER_H
#define __ALPHA_COMPILER_H

#include <uapi/asm/compiler.h>

<<<<<<< HEAD
=======
/* Some idiots over in <linux/compiler.h> thought inline should imply
   always_inline.  This breaks stuff.  We'll include this file whenever
   we run into such problems.  */

#include <linux/compiler.h>
#undef inline
#undef __inline__
#undef __inline
#undef __always_inline
#define __always_inline		inline __attribute__((always_inline))

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif /* __ALPHA_COMPILER_H */
