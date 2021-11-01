// SPDX-License-Identifier: GPL-2.0

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

<<<<<<< HEAD
SEC("xdp")
=======
SEC("tx")
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
int xdp_tx(struct xdp_md *xdp)
{
	return XDP_TX;
}

char _license[] SEC("license") = "GPL";
