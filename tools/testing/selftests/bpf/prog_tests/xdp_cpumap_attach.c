// SPDX-License-Identifier: GPL-2.0
#include <uapi/linux/bpf.h>
#include <linux/if_link.h>
#include <test_progs.h>

#include "test_xdp_with_cpumap_helpers.skel.h"

#define IFINDEX_LO	1

<<<<<<< HEAD
<<<<<<< HEAD
void test_xdp_cpumap_attach(void)
{
	struct test_xdp_with_cpumap_helpers *skel;
	struct bpf_prog_info info = {};
	__u32 len = sizeof(info);
	struct bpf_cpumap_val val = {
		.qsize = 192,
	};
	int err, prog_fd, map_fd;
	__u32 idx = 0;

	skel = test_xdp_with_cpumap_helpers__open_and_load();
	if (!ASSERT_OK_PTR(skel, "test_xdp_with_cpumap_helpers__open_and_load"))
		return;

	prog_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
	if (!ASSERT_OK(err, "Generic attach of program with 8-byte CPUMAP"))
		goto out_close;

	err = bpf_set_link_xdp_fd(IFINDEX_LO, -1, XDP_FLAGS_SKB_MODE);
	ASSERT_OK(err, "XDP program detach");
=======
void test_xdp_with_cpumap_helpers(void)
=======
void test_xdp_cpumap_attach(void)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct test_xdp_with_cpumap_helpers *skel;
	struct bpf_prog_info info = {};
	__u32 len = sizeof(info);
	struct bpf_cpumap_val val = {
		.qsize = 192,
	};
	int err, prog_fd, map_fd;
	__u32 idx = 0;

	skel = test_xdp_with_cpumap_helpers__open_and_load();
	if (!ASSERT_OK_PTR(skel, "test_xdp_with_cpumap_helpers__open_and_load"))
		return;

	prog_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
<<<<<<< HEAD
	CHECK(err == 0, "Generic attach of program with 8-byte CPUMAP",
	      "should have failed\n");
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!ASSERT_OK(err, "Generic attach of program with 8-byte CPUMAP"))
		goto out_close;

	err = bpf_set_link_xdp_fd(IFINDEX_LO, -1, XDP_FLAGS_SKB_MODE);
	ASSERT_OK(err, "XDP program detach");
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	prog_fd = bpf_program__fd(skel->progs.xdp_dummy_cm);
	map_fd = bpf_map__fd(skel->maps.cpu_map);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &len);
<<<<<<< HEAD
<<<<<<< HEAD
	if (!ASSERT_OK(err, "bpf_obj_get_info_by_fd"))
=======
	if (CHECK_FAIL(err))
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!ASSERT_OK(err, "bpf_obj_get_info_by_fd"))
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		goto out_close;

	val.bpf_prog.fd = prog_fd;
	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
<<<<<<< HEAD
<<<<<<< HEAD
	ASSERT_OK(err, "Add program to cpumap entry");

	err = bpf_map_lookup_elem(map_fd, &idx, &val);
	ASSERT_OK(err, "Read cpumap entry");
	ASSERT_EQ(info.id, val.bpf_prog.id, "Match program id to cpumap entry prog_id");

	/* can not attach BPF_XDP_CPUMAP program to a device */
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
	if (!ASSERT_NEQ(err, 0, "Attach of BPF_XDP_CPUMAP program"))
		bpf_set_link_xdp_fd(IFINDEX_LO, -1, XDP_FLAGS_SKB_MODE);
=======
	CHECK(err, "Add program to cpumap entry", "err %d errno %d\n",
	      err, errno);
=======
	ASSERT_OK(err, "Add program to cpumap entry");
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	err = bpf_map_lookup_elem(map_fd, &idx, &val);
	ASSERT_OK(err, "Read cpumap entry");
	ASSERT_EQ(info.id, val.bpf_prog.id, "Match program id to cpumap entry prog_id");

	/* can not attach BPF_XDP_CPUMAP program to a device */
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
<<<<<<< HEAD
	CHECK(err == 0, "Attach of BPF_XDP_CPUMAP program",
	      "should have failed\n");
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!ASSERT_NEQ(err, 0, "Attach of BPF_XDP_CPUMAP program"))
		bpf_set_link_xdp_fd(IFINDEX_LO, -1, XDP_FLAGS_SKB_MODE);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	val.qsize = 192;
	val.bpf_prog.fd = bpf_program__fd(skel->progs.xdp_dummy_prog);
	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
<<<<<<< HEAD
<<<<<<< HEAD
	ASSERT_NEQ(err, 0, "Add non-BPF_XDP_CPUMAP program to cpumap entry");
=======
	CHECK(err == 0, "Add non-BPF_XDP_CPUMAP program to cpumap entry",
	      "should have failed\n");
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	ASSERT_NEQ(err, 0, "Add non-BPF_XDP_CPUMAP program to cpumap entry");
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

out_close:
	test_xdp_with_cpumap_helpers__destroy(skel);
}
<<<<<<< HEAD
<<<<<<< HEAD
=======

void test_xdp_cpumap_attach(void)
{
	if (test__start_subtest("cpumap_with_progs"))
		test_xdp_with_cpumap_helpers();
}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
