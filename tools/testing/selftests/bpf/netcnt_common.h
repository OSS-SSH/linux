// SPDX-License-Identifier: GPL-2.0
#ifndef __NETCNT_COMMON_H
#define __NETCNT_COMMON_H

#include <linux/types.h>

#define MAX_PERCPU_PACKETS 32

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/* sizeof(struct bpf_local_storage_elem):
 *
 * It really is about 128 bytes on x86_64, but allocate more to account for
 * possible layout changes, different architectures, etc.
 * The kernel will wrap up to PAGE_SIZE internally anyway.
 */
#define SIZEOF_BPF_LOCAL_STORAGE_ELEM		256
<<<<<<< HEAD

/* Try to estimate kernel's BPF_LOCAL_STORAGE_MAX_VALUE_SIZE: */
#define BPF_LOCAL_STORAGE_MAX_VALUE_SIZE	(0xFFFF - \
						 SIZEOF_BPF_LOCAL_STORAGE_ELEM)

#define PCPU_MIN_UNIT_SIZE			32768

union percpu_net_cnt {
	struct {
		__u64 packets;
		__u64 bytes;

		__u64 prev_ts;

		__u64 prev_packets;
		__u64 prev_bytes;
	};
	__u8 data[PCPU_MIN_UNIT_SIZE];
};

union net_cnt {
	struct {
		__u64 packets;
		__u64 bytes;
	};
	__u8 data[BPF_LOCAL_STORAGE_MAX_VALUE_SIZE];
=======
struct percpu_net_cnt {
	__u64 packets;
	__u64 bytes;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

/* Try to estimate kernel's BPF_LOCAL_STORAGE_MAX_VALUE_SIZE: */
#define BPF_LOCAL_STORAGE_MAX_VALUE_SIZE	(0xFFFF - \
						 SIZEOF_BPF_LOCAL_STORAGE_ELEM)

#define PCPU_MIN_UNIT_SIZE			32768

union percpu_net_cnt {
	struct {
		__u64 packets;
		__u64 bytes;

		__u64 prev_ts;

		__u64 prev_packets;
		__u64 prev_bytes;
	};
	__u8 data[PCPU_MIN_UNIT_SIZE];
};

<<<<<<< HEAD
struct net_cnt {
	__u64 packets;
	__u64 bytes;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
union net_cnt {
	struct {
		__u64 packets;
		__u64 bytes;
	};
	__u8 data[BPF_LOCAL_STORAGE_MAX_VALUE_SIZE];
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

#endif
