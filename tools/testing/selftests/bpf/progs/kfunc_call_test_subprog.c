// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2021 Facebook */
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include "bpf_tcp_helpers.h"

extern const int bpf_prog_active __ksym;
extern __u64 bpf_kfunc_call_test1(struct sock *sk, __u32 a, __u64 b,
				  __u32 c, __u64 d) __ksym;
extern struct sock *bpf_kfunc_call_test3(struct sock *sk) __ksym;
int active_res = -1;
<<<<<<< HEAD
<<<<<<< HEAD
int sk_state_res = -1;
=======
int sk_state = -1;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
int sk_state_res = -1;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

int __noinline f1(struct __sk_buff *skb)
{
	struct bpf_sock *sk = skb->sk;
	int *active;

	if (!sk)
		return -1;

	sk = bpf_sk_fullsock(sk);
	if (!sk)
		return -1;

	active = (int *)bpf_per_cpu_ptr(&bpf_prog_active,
					bpf_get_smp_processor_id());
	if (active)
		active_res = *active;

<<<<<<< HEAD
<<<<<<< HEAD
	sk_state_res = bpf_kfunc_call_test3((struct sock *)sk)->sk_state;
=======
	sk_state = bpf_kfunc_call_test3((struct sock *)sk)->__sk_common.skc_state;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	sk_state_res = bpf_kfunc_call_test3((struct sock *)sk)->sk_state;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return (__u32)bpf_kfunc_call_test1((struct sock *)sk, 1, 2, 3, 4);
}

SEC("classifier")
int kfunc_call_test1(struct __sk_buff *skb)
{
	return f1(skb);
}

char _license[] SEC("license") = "GPL";
