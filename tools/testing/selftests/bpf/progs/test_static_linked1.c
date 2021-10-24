// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2021 Facebook */

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

<<<<<<< HEAD
/* 8-byte aligned .bss */
static volatile long static_var1;
static volatile int static_var11;
int var1 = 0;
=======
/* 8-byte aligned .data */
static volatile long static_var1 = 2;
static volatile int static_var2 = 3;
int var1 = -1;
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a
/* 4-byte aligned .rodata */
const volatile int rovar1;

/* same "subprog" name in both files */
static __noinline int subprog(int x)
{
	/* but different formula */
	return x * 2;
}

SEC("raw_tp/sys_enter")
int handler1(const void *ctx)
{
<<<<<<< HEAD
	var1 = subprog(rovar1) + static_var1 + static_var11;
=======
	var1 = subprog(rovar1) + static_var1 + static_var2;
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a

	return 0;
}

char LICENSE[] SEC("license") = "GPL";
int VERSION SEC("version") = 1;
