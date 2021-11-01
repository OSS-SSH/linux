// SPDX-License-Identifier: GPL-2.0-only
/* Copyright (c) 2017 Covalent IO, Inc. http://covalent.io
 */
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static const char *__doc__ =
"XDP redirect tool, using BPF_MAP_TYPE_DEVMAP\n"
"Usage: xdp_redirect_map <IFINDEX|IFNAME>_IN <IFINDEX|IFNAME>_OUT\n";

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/bpf.h>
#include <linux/if_link.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <libgen.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <getopt.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "bpf_util.h"
#include "xdp_sample_user.h"
#include "xdp_redirect_map.skel.h"

static int mask = SAMPLE_RX_CNT | SAMPLE_REDIRECT_ERR_MAP_CNT |
		  SAMPLE_EXCEPTION_CNT | SAMPLE_DEVMAP_XMIT_CNT_MULTI;

DEFINE_SAMPLE_INIT(xdp_redirect_map);

static const struct option long_options[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "skb-mode", no_argument, NULL, 'S' },
	{ "force", no_argument, NULL, 'F' },
	{ "load-egress", no_argument, NULL, 'X' },
	{ "stats", no_argument, NULL, 's' },
	{ "interval", required_argument, NULL, 'i' },
	{ "verbose", no_argument, NULL, 'v' },
	{}
};

int main(int argc, char **argv)
{
	struct bpf_devmap_val devmap_val = {};
	bool xdp_devmap_attached = false;
	struct xdp_redirect_map *skel;
	char str[2 * IF_NAMESIZE + 1];
	char ifname_out[IF_NAMESIZE];
	struct bpf_map *tx_port_map;
	char ifname_in[IF_NAMESIZE];
	int ifindex_in, ifindex_out;
	unsigned long interval = 2;
	int ret = EXIT_FAIL_OPTION;
	struct bpf_program *prog;
	bool generic = false;
	bool force = false;
	bool tried = false;
	bool error = true;
	int opt, key = 0;

	while ((opt = getopt_long(argc, argv, "hSFXi:vs",
				  long_options, NULL)) != -1) {
		switch (opt) {
		case 'S':
			generic = true;
			/* devmap_xmit tracepoint not available */
			mask &= ~(SAMPLE_DEVMAP_XMIT_CNT |
				  SAMPLE_DEVMAP_XMIT_CNT_MULTI);
			break;
		case 'F':
			force = true;
=======
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "bpf_util.h"
=======
#include <getopt.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "bpf_util.h"
#include "xdp_sample_user.h"
#include "xdp_redirect_map.skel.h"

static int mask = SAMPLE_RX_CNT | SAMPLE_REDIRECT_ERR_MAP_CNT |
		  SAMPLE_EXCEPTION_CNT | SAMPLE_DEVMAP_XMIT_CNT_MULTI;

DEFINE_SAMPLE_INIT(xdp_redirect_map);

static const struct option long_options[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "skb-mode", no_argument, NULL, 'S' },
	{ "force", no_argument, NULL, 'F' },
	{ "load-egress", no_argument, NULL, 'X' },
	{ "stats", no_argument, NULL, 's' },
	{ "interval", required_argument, NULL, 'i' },
	{ "verbose", no_argument, NULL, 'v' },
	{}
};

int main(int argc, char **argv)
{
	struct bpf_devmap_val devmap_val = {};
	bool xdp_devmap_attached = false;
	struct xdp_redirect_map *skel;
	char str[2 * IF_NAMESIZE + 1];
	char ifname_out[IF_NAMESIZE];
	struct bpf_map *tx_port_map;
	char ifname_in[IF_NAMESIZE];
	int ifindex_in, ifindex_out;
	unsigned long interval = 2;
	int ret = EXIT_FAIL_OPTION;
	struct bpf_program *prog;
	bool generic = false;
	bool force = false;
	bool tried = false;
	bool error = true;
	int opt, key = 0;

	while ((opt = getopt_long(argc, argv, "hSFXi:vs",
				  long_options, NULL)) != -1) {
		switch (opt) {
		case 'S':
			generic = true;
			/* devmap_xmit tracepoint not available */
			mask &= ~(SAMPLE_DEVMAP_XMIT_CNT |
				  SAMPLE_DEVMAP_XMIT_CNT_MULTI);
			break;
		case 'F':
<<<<<<< HEAD
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
			force = true;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			break;
		case 'X':
			xdp_devmap_attached = true;
			break;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		case 'i':
			interval = strtoul(optarg, NULL, 0);
			break;
		case 'v':
			sample_switch_mode();
			break;
		case 's':
			mask |= SAMPLE_REDIRECT_MAP_CNT;
			break;
		case 'h':
			error = false;
<<<<<<< HEAD
		default:
			sample_usage(argv, long_options, __doc__, mask, error);
			return ret;
		}
	}

	if (argc <= optind + 1) {
		sample_usage(argv, long_options, __doc__, mask, true);
		goto end;
=======
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		default:
			sample_usage(argv, long_options, __doc__, mask, error);
			return ret;
		}
	}

<<<<<<< HEAD
	if (!(xdp_flags & XDP_FLAGS_SKB_MODE)) {
		xdp_flags |= XDP_FLAGS_DRV_MODE;
	} else if (xdp_devmap_attached) {
		printf("Load xdp program on egress with SKB mode not supported yet\n");
		return 1;
	}

	if (optind == argc) {
		printf("usage: %s <IFNAME|IFINDEX>_IN <IFNAME|IFINDEX>_OUT\n", argv[0]);
		return 1;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (argc <= optind + 1) {
		sample_usage(argv, long_options, __doc__, mask, true);
		goto end;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	}

	ifindex_in = if_nametoindex(argv[optind]);
	if (!ifindex_in)
		ifindex_in = strtoul(argv[optind], NULL, 0);

	ifindex_out = if_nametoindex(argv[optind + 1]);
	if (!ifindex_out)
		ifindex_out = strtoul(argv[optind + 1], NULL, 0);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (!ifindex_in || !ifindex_out) {
		fprintf(stderr, "Bad interface index or name\n");
		sample_usage(argv, long_options, __doc__, mask, true);
		goto end;
<<<<<<< HEAD
	}

	skel = xdp_redirect_map__open();
	if (!skel) {
		fprintf(stderr, "Failed to xdp_redirect_map__open: %s\n",
			strerror(errno));
		ret = EXIT_FAIL_BPF;
		goto end;
	}

	ret = sample_init_pre_load(skel);
	if (ret < 0) {
		fprintf(stderr, "Failed to sample_init_pre_load: %s\n", strerror(-ret));
		ret = EXIT_FAIL_BPF;
		goto end_destroy;
	}

	/* Load 2nd xdp prog on egress. */
	if (xdp_devmap_attached) {
		ret = get_mac_addr(ifindex_out, skel->rodata->tx_mac_addr);
		if (ret < 0) {
			fprintf(stderr, "Failed to get interface %d mac address: %s\n",
				ifindex_out, strerror(-ret));
			ret = EXIT_FAIL;
			goto end_destroy;
		}
	}

	skel->rodata->from_match[0] = ifindex_in;
	skel->rodata->to_match[0] = ifindex_out;

	ret = xdp_redirect_map__load(skel);
	if (ret < 0) {
		fprintf(stderr, "Failed to xdp_redirect_map__load: %s\n",
			strerror(errno));
		ret = EXIT_FAIL_BPF;
		goto end_destroy;
	}

	ret = sample_init(skel, mask);
	if (ret < 0) {
		fprintf(stderr, "Failed to initialize sample: %s\n", strerror(-ret));
		ret = EXIT_FAIL;
		goto end_destroy;
	}

	prog = skel->progs.xdp_redirect_map_native;
	tx_port_map = skel->maps.tx_port_native;
restart:
	if (sample_install_xdp(prog, ifindex_in, generic, force) < 0) {
		/* First try with struct bpf_devmap_val as value for generic
		 * mode, then fallback to sizeof(int) for older kernels.
		 */
		fprintf(stderr,
			"Trying fallback to sizeof(int) as value_size for devmap in generic mode\n");
		if (generic && !tried) {
			prog = skel->progs.xdp_redirect_map_general;
			tx_port_map = skel->maps.tx_port_general;
			tried = true;
			goto restart;
		}
		ret = EXIT_FAIL_XDP;
		goto end_destroy;
	}

	/* Loading dummy XDP prog on out-device */
	sample_install_xdp(skel->progs.xdp_redirect_dummy_prog, ifindex_out, generic, force);

	devmap_val.ifindex = ifindex_out;
	if (xdp_devmap_attached)
		devmap_val.bpf_prog.fd = bpf_program__fd(skel->progs.xdp_redirect_map_egress);
	ret = bpf_map_update_elem(bpf_map__fd(tx_port_map), &key, &devmap_val, 0);
	if (ret < 0) {
		fprintf(stderr, "Failed to update devmap value: %s\n",
			strerror(errno));
		ret = EXIT_FAIL_BPF;
		goto end_destroy;
	}

	ret = EXIT_FAIL;
	if (!if_indextoname(ifindex_in, ifname_in)) {
		fprintf(stderr, "Failed to if_indextoname for %d: %s\n", ifindex_in,
			strerror(errno));
		goto end_destroy;
	}

	if (!if_indextoname(ifindex_out, ifname_out)) {
		fprintf(stderr, "Failed to if_indextoname for %d: %s\n", ifindex_out,
			strerror(errno));
		goto end_destroy;
	}

	safe_strncpy(str, get_driver_name(ifindex_in), sizeof(str));
	printf("Redirecting from %s (ifindex %d; driver %s) to %s (ifindex %d; driver %s)\n",
	       ifname_in, ifindex_in, str, ifname_out, ifindex_out, get_driver_name(ifindex_out));
	snprintf(str, sizeof(str), "%s->%s", ifname_in, ifname_out);

	ret = sample_run(interval, NULL, NULL);
	if (ret < 0) {
		fprintf(stderr, "Failed during sample run: %s\n", strerror(-ret));
		ret = EXIT_FAIL;
		goto end_destroy;
	}
	ret = EXIT_OK;
end_destroy:
	xdp_redirect_map__destroy(skel);
end:
	sample_exit(ret);
=======
	printf("input: %d output: %d\n", ifindex_in, ifindex_out);

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	if (xdp_flags & XDP_FLAGS_SKB_MODE) {
		prog = bpf_object__find_program_by_name(obj, "xdp_redirect_map_general");
		tx_port_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_port_general");
	} else {
		prog = bpf_object__find_program_by_name(obj, "xdp_redirect_map_native");
		tx_port_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_port_native");
	}
	dummy_prog = bpf_object__find_program_by_name(obj, "xdp_redirect_dummy_prog");
	if (!prog || dummy_prog < 0 || tx_port_map_fd < 0) {
		printf("finding prog/dummy_prog/tx_port_map in obj file failed\n");
		goto out;
	}
	prog_fd = bpf_program__fd(prog);
	dummy_prog_fd = bpf_program__fd(dummy_prog);
	if (prog_fd < 0 || dummy_prog_fd < 0 || tx_port_map_fd < 0) {
		printf("bpf_prog_load_xattr: %s\n", strerror(errno));
		return 1;
	}

	tx_mac_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_mac");
	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	if (tx_mac_map_fd < 0 || rxcnt_map_fd < 0) {
		printf("bpf_object__find_map_fd_by_name failed\n");
		return 1;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	}

	skel = xdp_redirect_map__open();
	if (!skel) {
		fprintf(stderr, "Failed to xdp_redirect_map__open: %s\n",
			strerror(errno));
		ret = EXIT_FAIL_BPF;
		goto end;
	}

	ret = sample_init_pre_load(skel);
	if (ret < 0) {
		fprintf(stderr, "Failed to sample_init_pre_load: %s\n", strerror(-ret));
		ret = EXIT_FAIL_BPF;
		goto end_destroy;
	}

	/* Load 2nd xdp prog on egress. */
	if (xdp_devmap_attached) {
		ret = get_mac_addr(ifindex_out, skel->rodata->tx_mac_addr);
		if (ret < 0) {
			fprintf(stderr, "Failed to get interface %d mac address: %s\n",
				ifindex_out, strerror(-ret));
			ret = EXIT_FAIL;
			goto end_destroy;
		}
	}

	skel->rodata->from_match[0] = ifindex_in;
	skel->rodata->to_match[0] = ifindex_out;

	ret = xdp_redirect_map__load(skel);
	if (ret < 0) {
		fprintf(stderr, "Failed to xdp_redirect_map__load: %s\n",
			strerror(errno));
		ret = EXIT_FAIL_BPF;
		goto end_destroy;
	}

	ret = sample_init(skel, mask);
	if (ret < 0) {
		fprintf(stderr, "Failed to initialize sample: %s\n", strerror(-ret));
		ret = EXIT_FAIL;
		goto end_destroy;
	}

	prog = skel->progs.xdp_redirect_map_native;
	tx_port_map = skel->maps.tx_port_native;
restart:
	if (sample_install_xdp(prog, ifindex_in, generic, force) < 0) {
		/* First try with struct bpf_devmap_val as value for generic
		 * mode, then fallback to sizeof(int) for older kernels.
		 */
		fprintf(stderr,
			"Trying fallback to sizeof(int) as value_size for devmap in generic mode\n");
		if (generic && !tried) {
			prog = skel->progs.xdp_redirect_map_general;
			tx_port_map = skel->maps.tx_port_general;
			tried = true;
			goto restart;
		}
		ret = EXIT_FAIL_XDP;
		goto end_destroy;
	}

	/* Loading dummy XDP prog on out-device */
	sample_install_xdp(skel->progs.xdp_redirect_dummy_prog, ifindex_out, generic, force);

	devmap_val.ifindex = ifindex_out;
<<<<<<< HEAD
	devmap_val.bpf_prog.fd = devmap_prog_fd;
	ret = bpf_map_update_elem(tx_port_map_fd, &key, &devmap_val, 0);
	if (ret) {
		perror("bpf_update_elem");
		goto out;
	}

	poll_stats(2, ifindex_out);

out:
	return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (xdp_devmap_attached)
		devmap_val.bpf_prog.fd = bpf_program__fd(skel->progs.xdp_redirect_map_egress);
	ret = bpf_map_update_elem(bpf_map__fd(tx_port_map), &key, &devmap_val, 0);
	if (ret < 0) {
		fprintf(stderr, "Failed to update devmap value: %s\n",
			strerror(errno));
		ret = EXIT_FAIL_BPF;
		goto end_destroy;
	}

	ret = EXIT_FAIL;
	if (!if_indextoname(ifindex_in, ifname_in)) {
		fprintf(stderr, "Failed to if_indextoname for %d: %s\n", ifindex_in,
			strerror(errno));
		goto end_destroy;
	}

	if (!if_indextoname(ifindex_out, ifname_out)) {
		fprintf(stderr, "Failed to if_indextoname for %d: %s\n", ifindex_out,
			strerror(errno));
		goto end_destroy;
	}

	safe_strncpy(str, get_driver_name(ifindex_in), sizeof(str));
	printf("Redirecting from %s (ifindex %d; driver %s) to %s (ifindex %d; driver %s)\n",
	       ifname_in, ifindex_in, str, ifname_out, ifindex_out, get_driver_name(ifindex_out));
	snprintf(str, sizeof(str), "%s->%s", ifname_in, ifname_out);

	ret = sample_run(interval, NULL, NULL);
	if (ret < 0) {
		fprintf(stderr, "Failed during sample run: %s\n", strerror(-ret));
		ret = EXIT_FAIL;
		goto end_destroy;
	}
	ret = EXIT_OK;
end_destroy:
	xdp_redirect_map__destroy(skel);
end:
	sample_exit(ret);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}
