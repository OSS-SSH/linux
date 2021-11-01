/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
<<<<<<< HEAD
/* IP tables module for matching the value of the TTL
 * (C) 2000 by Harald Welte <laforge@gnumonks.org> */
=======
/* TTL modification module for IP tables
 * (C) 2000 by Harald Welte <laforge@netfilter.org> */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#ifndef _IPT_TTL_H
#define _IPT_TTL_H

#include <linux/types.h>

enum {
<<<<<<< HEAD
	IPT_TTL_EQ = 0,		/* equals */
	IPT_TTL_NE,		/* not equals */
	IPT_TTL_LT,		/* less than */
	IPT_TTL_GT,		/* greater than */
};


struct ipt_ttl_info {
=======
	IPT_TTL_SET = 0,
	IPT_TTL_INC,
	IPT_TTL_DEC
};

#define IPT_TTL_MAXMODE	IPT_TTL_DEC

struct ipt_TTL_info {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	__u8	mode;
	__u8	ttl;
};


#endif
