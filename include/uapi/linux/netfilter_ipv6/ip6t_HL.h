/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
<<<<<<< HEAD
/* ip6tables module for matching the Hop Limit value
 * Maciej Soltysiak <solt@dns.toxicfilms.tv>
 * Based on HW's ttl module */
=======
/* Hop Limit modification module for ip6tables
 * Maciej Soltysiak <solt@dns.toxicfilms.tv>
 * Based on HW's TTL module */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#ifndef _IP6T_HL_H
#define _IP6T_HL_H

#include <linux/types.h>

enum {
<<<<<<< HEAD
	IP6T_HL_EQ = 0,		/* equals */
	IP6T_HL_NE,		/* not equals */
	IP6T_HL_LT,		/* less than */
	IP6T_HL_GT,		/* greater than */
};


struct ip6t_hl_info {
=======
	IP6T_HL_SET = 0,
	IP6T_HL_INC,
	IP6T_HL_DEC
};

#define IP6T_HL_MAXMODE	IP6T_HL_DEC

struct ip6t_HL_info {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	__u8	mode;
	__u8	hop_limit;
};


#endif
