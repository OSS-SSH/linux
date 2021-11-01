/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
<<<<<<< HEAD
#ifndef _XT_MARK_H
#define _XT_MARK_H

#include <linux/types.h>

struct xt_mark_tginfo2 {
	__u32 mark, mask;
};

struct xt_mark_mtinfo1 {
	__u32 mark, mask;
	__u8 invert;
};

#endif /*_XT_MARK_H*/
=======
#ifndef _XT_MARK_H_target
#define _XT_MARK_H_target

#include <linux/netfilter/xt_mark.h>

#endif /*_XT_MARK_H_target */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
