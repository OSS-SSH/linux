// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2020 Intel Corporation. */

/*
 * Some functions in this program are taken from
 * Linux kernel samples/bpf/xdpsock* and modified
 * for use.
 *
 * See test_xsk.sh for detailed information on test topology
 * and prerequisite network setup.
 *
 * This test program contains two threads, each thread is single socket with
 * a unique UMEM. It validates in-order packet delivery and packet content
 * by sending packets to each other.
 *
 * Tests Information:
 * ------------------
 * These selftests test AF_XDP SKB and Native/DRV modes using veth
 * Virtual Ethernet interfaces.
 *
 * For each mode, the following tests are run:
 *    a. nopoll - soft-irq processing
 *    b. poll - using poll() syscall
 *    c. Socket Teardown
 *       Create a Tx and a Rx socket, Tx from one socket, Rx on another. Destroy
 *       both sockets, then repeat multiple times. Only nopoll mode is used
 *    d. Bi-directional sockets
 *       Configure sockets as bi-directional tx/rx sockets, sets up fill and
 *       completion rings on each socket, tx/rx in both directions. Only nopoll
 *       mode is used
 *    e. Statistics
 *       Trigger some error conditions and ensure that the appropriate statistics
 *       are incremented. Within this test, the following statistics are tested:
 *       i.   rx dropped
 *            Increase the UMEM frame headroom to a value which results in
 *            insufficient space in the rx buffer for both the packet and the headroom.
 *       ii.  tx invalid
 *            Set the 'len' field of tx descriptors to an invalid value (umem frame
 *            size + 1).
 *       iii. rx ring full
 *            Reduce the size of the RX ring to a fraction of the fill ring size.
 *       iv.  fill queue empty
 *            Do not populate the fill queue and then try to receive pkts.
 *    f. bpf_link resource persistence
 *       Configure sockets at indexes 0 and 1, run a traffic on queue ids 0,
 *       then remove xsk sockets from queue 0 on both veth interfaces and
 *       finally run a traffic on queues ids 1
 *
 * Total tests: 12
 *
 * Flow:
 * -----
 * - Single process spawns two threads: Tx and Rx
 * - Each of these two threads attach to a veth interface within their assigned
 *   namespaces
 * - Each thread Creates one AF_XDP socket connected to a unique umem for each
 *   veth interface
 * - Tx thread Transmits 10k packets from veth<xxxx> to veth<yyyy>
 * - Rx thread verifies if all 10k packets were received and delivered in-order,
 *   and have the right content
 *
 * Enable/disable packet dump mode:
 * --------------------------
 * To enable L2 - L4 headers and payload dump of each packet on STDOUT, add
 * parameter -D to params array in test_xsk.sh, i.e. params=("-S" "-D")
 */

#define _GNU_SOURCE
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>
#include <asm/barrier.h>
<<<<<<< HEAD
=======
typedef __u16 __sum16;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#include <linux/if_link.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <locale.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/queue.h>
#include <time.h>
#include <unistd.h>
#include <stdatomic.h>
#include <bpf/xsk.h>
#include "xdpxceiver.h"
#include "../kselftest.h"

static const char *MAC1 = "\x00\x0A\x56\x9E\xEE\x62";
static const char *MAC2 = "\x00\x0A\x56\x9E\xEE\x61";
static const char *IP1 = "192.168.100.162";
static const char *IP2 = "192.168.100.161";
static const u16 UDP_PORT1 = 2020;
static const u16 UDP_PORT2 = 2121;

static void __exit_with_error(int error, const char *file, const char *func, int line)
{
<<<<<<< HEAD
	ksft_test_result_fail("[%s:%s:%i]: ERROR: %d/\"%s\"\n", file, func, line, error,
			      strerror(error));
	ksft_exit_xfail();
=======
	if (configured_mode == TEST_MODE_UNCONFIGURED) {
		ksft_exit_fail_msg
		("[%s:%s:%i]: ERROR: %d/\"%s\"\n", file, func, line, error, strerror(error));
	} else {
		ksft_test_result_fail
		("[%s:%s:%i]: ERROR: %d/\"%s\"\n", file, func, line, error, strerror(error));
		ksft_exit_xfail();
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}

#define exit_with_error(error) __exit_with_error(error, __FILE__, __func__, __LINE__)

#define print_ksft_result(void)\
	(ksft_test_result_pass("PASS: %s %s %s%s%s%s\n", configured_mode ? "DRV" : "SKB",\
			       test_type == TEST_TYPE_POLL ? "POLL" : "NOPOLL",\
			       test_type == TEST_TYPE_TEARDOWN ? "Socket Teardown" : "",\
			       test_type == TEST_TYPE_BIDI ? "Bi-directional Sockets" : "",\
			       test_type == TEST_TYPE_STATS ? "Stats" : "",\
			       test_type == TEST_TYPE_BPF_RES ? "BPF RES" : ""))

<<<<<<< HEAD
static void memset32_htonl(void *dest, u32 val, u32 size)
=======
static void *memset32_htonl(void *dest, u32 val, u32 size)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
{
	u32 *ptr = (u32 *)dest;
	int i;

	val = htonl(val);

	for (i = 0; i < (size & (~0x3)); i += 4)
		ptr[i >> 2] = val;
<<<<<<< HEAD
=======

	for (; i < size; i++)
		((char *)dest)[i] = ((char *)&val)[i & 3];

	return dest;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}

/*
 * Fold a partial checksum
 * This function code has been taken from
 * Linux kernel include/asm-generic/checksum.h
 */
static __u16 csum_fold(__u32 csum)
{
	u32 sum = (__force u32)csum;

	sum = (sum & 0xffff) + (sum >> 16);
	sum = (sum & 0xffff) + (sum >> 16);
	return (__force __u16)~sum;
}

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
static u32 from64to32(u64 x)
{
	/* add up 32-bit and 32-bit for 32+c bit */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up carry.. */
	x = (x & 0xffffffff) + (x >> 32);
	return (u32)x;
}

/*
 * This function code has been taken from
 * Linux kernel lib/checksum.c
 */
static __u32 csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len, __u8 proto, __u32 sum)
{
	unsigned long long s = (__force u32)sum;

	s += (__force u32)saddr;
	s += (__force u32)daddr;
#ifdef __BIG_ENDIAN__
	s += proto + len;
#else
	s += (proto + len) << 8;
#endif
	return (__force __u32)from64to32(s);
}

/*
 * This function has been taken from
 * Linux kernel include/asm-generic/checksum.h
 */
static __u16 csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len, __u8 proto, __u32 sum)
{
	return csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
}

static u16 udp_csum(u32 saddr, u32 daddr, u32 len, u8 proto, u16 *udp_pkt)
{
	u32 csum = 0;
	u32 cnt = 0;

	/* udp hdr and data */
	for (; cnt < len; cnt += 2)
		csum += udp_pkt[cnt >> 1];

	return csum_tcpudp_magic(saddr, daddr, len, proto, csum);
}

static void gen_eth_hdr(struct ifobject *ifobject, struct ethhdr *eth_hdr)
{
	memcpy(eth_hdr->h_dest, ifobject->dst_mac, ETH_ALEN);
	memcpy(eth_hdr->h_source, ifobject->src_mac, ETH_ALEN);
	eth_hdr->h_proto = htons(ETH_P_IP);
}

static void gen_ip_hdr(struct ifobject *ifobject, struct iphdr *ip_hdr)
{
	ip_hdr->version = IP_PKT_VER;
	ip_hdr->ihl = 0x5;
	ip_hdr->tos = IP_PKT_TOS;
	ip_hdr->tot_len = htons(IP_PKT_SIZE);
	ip_hdr->id = 0;
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = IPDEFTTL;
	ip_hdr->protocol = IPPROTO_UDP;
	ip_hdr->saddr = ifobject->src_ip;
	ip_hdr->daddr = ifobject->dst_ip;
	ip_hdr->check = 0;
}

<<<<<<< HEAD
static void gen_udp_hdr(u32 payload, void *pkt, struct ifobject *ifobject,
=======
static void gen_udp_hdr(struct generic_data *data, struct ifobject *ifobject,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
			struct udphdr *udp_hdr)
{
	udp_hdr->source = htons(ifobject->src_port);
	udp_hdr->dest = htons(ifobject->dst_port);
	udp_hdr->len = htons(UDP_PKT_SIZE);
<<<<<<< HEAD
	memset32_htonl(pkt + PKT_HDR_SIZE, payload, UDP_PKT_DATA_SIZE);
=======
	memset32_htonl(pkt_data + PKT_HDR_SIZE, htonl(data->seqnum), UDP_PKT_DATA_SIZE);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}

static void gen_udp_csum(struct udphdr *udp_hdr, struct iphdr *ip_hdr)
{
	udp_hdr->check = 0;
	udp_hdr->check =
	    udp_csum(ip_hdr->saddr, ip_hdr->daddr, UDP_PKT_SIZE, IPPROTO_UDP, (u16 *)udp_hdr);
}

<<<<<<< HEAD
static void xsk_configure_umem(struct ifobject *data, void *buffer, u64 size, int idx)
=======
static void gen_eth_frame(struct xsk_umem_info *umem, u64 addr)
{
	memcpy(xsk_umem__get_data(umem->buffer, addr), pkt_data, PKT_SIZE);
}

static void xsk_configure_umem(struct ifobject *data, void *buffer, int idx)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
{
	struct xsk_umem_config cfg = {
		.fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS,
		.comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS,
		.frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE,
		.frame_headroom = frame_headroom,
		.flags = XSK_UMEM__DEFAULT_FLAGS
	};
<<<<<<< HEAD
=======
	int size = num_frames * XSK_UMEM__DEFAULT_FRAME_SIZE;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	struct xsk_umem_info *umem;
	int ret;

	umem = calloc(1, sizeof(struct xsk_umem_info));
	if (!umem)
		exit_with_error(errno);

	ret = xsk_umem__create(&umem->umem, buffer, size,
			       &umem->fq, &umem->cq, &cfg);
	if (ret)
<<<<<<< HEAD
		exit_with_error(-ret);
=======
		exit_with_error(ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	umem->buffer = buffer;

	data->umem_arr[idx] = umem;
}

static void xsk_populate_fill_ring(struct xsk_umem_info *umem)
{
	int ret, i;
	u32 idx = 0;

	ret = xsk_ring_prod__reserve(&umem->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS, &idx);
	if (ret != XSK_RING_PROD__DEFAULT_NUM_DESCS)
<<<<<<< HEAD
		exit_with_error(-ret);
=======
		exit_with_error(ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	for (i = 0; i < XSK_RING_PROD__DEFAULT_NUM_DESCS; i++)
		*xsk_ring_prod__fill_addr(&umem->fq, idx++) = i * XSK_UMEM__DEFAULT_FRAME_SIZE;
	xsk_ring_prod__submit(&umem->fq, XSK_RING_PROD__DEFAULT_NUM_DESCS);
}

static int xsk_configure_socket(struct ifobject *ifobject, int idx)
{
	struct xsk_socket_config cfg;
	struct xsk_socket_info *xsk;
	struct xsk_ring_cons *rxr;
	struct xsk_ring_prod *txr;
	int ret;

	xsk = calloc(1, sizeof(struct xsk_socket_info));
	if (!xsk)
		exit_with_error(errno);

	xsk->umem = ifobject->umem;
	cfg.rx_size = rxqsize;
	cfg.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
	cfg.libbpf_flags = 0;
	cfg.xdp_flags = xdp_flags;
	cfg.bind_flags = xdp_bind_flags;

	if (test_type != TEST_TYPE_BIDI) {
		rxr = (ifobject->fv.vector == rx) ? &xsk->rx : NULL;
		txr = (ifobject->fv.vector == tx) ? &xsk->tx : NULL;
	} else {
		rxr = &xsk->rx;
		txr = &xsk->tx;
	}

	ret = xsk_socket__create(&xsk->xsk, ifobject->ifname, idx,
				 ifobject->umem->umem, rxr, txr, &cfg);
	if (ret)
		return 1;

	ifobject->xsk_arr[idx] = xsk;

	return 0;
}

static struct option long_options[] = {
	{"interface", required_argument, 0, 'i'},
	{"queue", optional_argument, 0, 'q'},
	{"dump-pkts", optional_argument, 0, 'D'},
	{"verbose", no_argument, 0, 'v'},
<<<<<<< HEAD
=======
	{"tx-pkt-count", optional_argument, 0, 'C'},
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	{0, 0, 0, 0}
};

static void usage(const char *prog)
{
	const char *str =
<<<<<<< HEAD
		"  Usage: %s [OPTIONS]\n"
		"  Options:\n"
		"  -i, --interface      Use interface\n"
		"  -q, --queue=n        Use queue n (default 0)\n"
		"  -D, --dump-pkts      Dump packets L2 - L5\n"
		"  -v, --verbose        Verbose output\n";

=======
	    "  Usage: %s [OPTIONS]\n"
	    "  Options:\n"
	    "  -i, --interface      Use interface\n"
	    "  -q, --queue=n        Use queue n (default 0)\n"
	    "  -D, --dump-pkts      Dump packets L2 - L5\n"
	    "  -v, --verbose        Verbose output\n"
	    "  -C, --tx-pkt-count=n Number of packets to send\n";
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	ksft_print_msg(str, prog);
}

static int switch_namespace(const char *nsname)
{
	char fqns[26] = "/var/run/netns/";
	int nsfd;

	if (!nsname || strlen(nsname) == 0)
		return -1;

	strncat(fqns, nsname, sizeof(fqns) - strlen(fqns) - 1);
	nsfd = open(fqns, O_RDONLY);

	if (nsfd == -1)
		exit_with_error(errno);

	if (setns(nsfd, 0) == -1)
		exit_with_error(errno);

	print_verbose("NS switched: %s\n", nsname);

	return nsfd;
}

static int validate_interfaces(void)
{
	bool ret = true;

	for (int i = 0; i < MAX_INTERFACES; i++) {
		if (!strcmp(ifdict[i]->ifname, "")) {
			ret = false;
			ksft_test_result_fail("ERROR: interfaces: -i <int>,<ns> -i <int>,<ns>.");
		}
	}
	return ret;
}

static void parse_command_line(int argc, char **argv)
{
	int option_index, interface_index = 0, c;

	opterr = 0;

	for (;;) {
<<<<<<< HEAD
		c = getopt_long(argc, argv, "i:Dv", long_options, &option_index);
=======
		c = getopt_long(argc, argv, "i:DC:v", long_options, &option_index);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

		if (c == -1)
			break;

		switch (c) {
		case 'i':
			if (interface_index == MAX_INTERFACES)
				break;
			char *sptr, *token;

			sptr = strndupa(optarg, strlen(optarg));
			memcpy(ifdict[interface_index]->ifname,
			       strsep(&sptr, ","), MAX_INTERFACE_NAME_CHARS);
			token = strsep(&sptr, ",");
			if (token)
				memcpy(ifdict[interface_index]->nsname, token,
				       MAX_INTERFACES_NAMESPACE_CHARS);
			interface_index++;
			break;
		case 'D':
<<<<<<< HEAD
			opt_pkt_dump = true;
			break;
		case 'v':
			opt_verbose = true;
=======
			debug_pkt_dump = 1;
			break;
		case 'C':
			opt_pkt_count = atoi(optarg);
			break;
		case 'v':
			opt_verbose = 1;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
			break;
		default:
			usage(basename(argv[0]));
			ksft_exit_xfail();
		}
	}

<<<<<<< HEAD
=======
	if (!opt_pkt_count) {
		print_verbose("No tx-pkt-count specified, using default %u\n", DEFAULT_PKT_CNT);
		opt_pkt_count = DEFAULT_PKT_CNT;
	}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	if (!validate_interfaces()) {
		usage(basename(argv[0]));
		ksft_exit_xfail();
	}
}

<<<<<<< HEAD
static struct pkt *pkt_stream_get_pkt(struct pkt_stream *pkt_stream, u32 pkt_nb)
{
	if (pkt_nb >= pkt_stream->nb_pkts)
		return NULL;

	return &pkt_stream->pkts[pkt_nb];
}

static struct pkt_stream *pkt_stream_generate(u32 nb_pkts, u32 pkt_len)
{
	struct pkt_stream *pkt_stream;
	u32 i;

	pkt_stream = malloc(sizeof(*pkt_stream));
	if (!pkt_stream)
		exit_with_error(ENOMEM);

	pkt_stream->pkts = calloc(nb_pkts, sizeof(*pkt_stream->pkts));
	if (!pkt_stream->pkts)
		exit_with_error(ENOMEM);

	pkt_stream->nb_pkts = nb_pkts;
	for (i = 0; i < nb_pkts; i++) {
		pkt_stream->pkts[i].addr = (i % num_frames) * XSK_UMEM__DEFAULT_FRAME_SIZE;
		pkt_stream->pkts[i].len = pkt_len;
		pkt_stream->pkts[i].payload = i;
	}

	return pkt_stream;
}

static struct pkt *pkt_generate(struct ifobject *ifobject, u32 pkt_nb)
{
	struct pkt *pkt = pkt_stream_get_pkt(ifobject->pkt_stream, pkt_nb);
	struct udphdr *udp_hdr;
	struct ethhdr *eth_hdr;
	struct iphdr *ip_hdr;
	void *data;

	if (!pkt)
		return NULL;

	data = xsk_umem__get_data(ifobject->umem->buffer, pkt->addr);
	udp_hdr = (struct udphdr *)(data + sizeof(struct ethhdr) + sizeof(struct iphdr));
	ip_hdr = (struct iphdr *)(data + sizeof(struct ethhdr));
	eth_hdr = (struct ethhdr *)data;

	gen_udp_hdr(pkt_nb, data, ifobject, udp_hdr);
	gen_ip_hdr(ifobject, ip_hdr);
	gen_udp_csum(udp_hdr, ip_hdr);
	gen_eth_hdr(ifobject, eth_hdr);

	return pkt;
}

static void pkt_dump(void *pkt, u32 len)
{
	char s[INET_ADDRSTRLEN];
	struct ethhdr *ethhdr;
	struct udphdr *udphdr;
	struct iphdr *iphdr;
	int payload, i;

	ethhdr = pkt;
	iphdr = pkt + sizeof(*ethhdr);
	udphdr = pkt + sizeof(*ethhdr) + sizeof(*iphdr);

	/*extract L2 frame */
	fprintf(stdout, "DEBUG>> L2: dst mac: ");
	for (i = 0; i < ETH_ALEN; i++)
		fprintf(stdout, "%02X", ethhdr->h_dest[i]);

	fprintf(stdout, "\nDEBUG>> L2: src mac: ");
	for (i = 0; i < ETH_ALEN; i++)
		fprintf(stdout, "%02X", ethhdr->h_source[i]);

	/*extract L3 frame */
	fprintf(stdout, "\nDEBUG>> L3: ip_hdr->ihl: %02X\n", iphdr->ihl);
	fprintf(stdout, "DEBUG>> L3: ip_hdr->saddr: %s\n",
		inet_ntop(AF_INET, &iphdr->saddr, s, sizeof(s)));
	fprintf(stdout, "DEBUG>> L3: ip_hdr->daddr: %s\n",
		inet_ntop(AF_INET, &iphdr->daddr, s, sizeof(s)));
	/*extract L4 frame */
	fprintf(stdout, "DEBUG>> L4: udp_hdr->src: %d\n", ntohs(udphdr->source));
	fprintf(stdout, "DEBUG>> L4: udp_hdr->dst: %d\n", ntohs(udphdr->dest));
	/*extract L5 frame */
	payload = *((uint32_t *)(pkt + PKT_HDR_SIZE));

	fprintf(stdout, "DEBUG>> L5: payload: %d\n", payload);
	fprintf(stdout, "---------------------------------------\n");
}

static bool is_pkt_valid(struct pkt *pkt, void *buffer, const struct xdp_desc *desc)
{
	void *data = xsk_umem__get_data(buffer, desc->addr);
	struct iphdr *iphdr = (struct iphdr *)(data + sizeof(struct ethhdr));

	if (!pkt) {
		ksft_test_result_fail("ERROR: [%s] too many packets received\n", __func__);
		return false;
	}

	if (iphdr->version == IP_PKT_VER && iphdr->tos == IP_PKT_TOS) {
		u32 seqnum = ntohl(*((u32 *)(data + PKT_HDR_SIZE)));

		if (opt_pkt_dump && test_type != TEST_TYPE_STATS)
			pkt_dump(data, PKT_SIZE);

		if (pkt->len != desc->len) {
			ksft_test_result_fail
				("ERROR: [%s] expected length [%d], got length [%d]\n",
					__func__, pkt->len, desc->len);
			return false;
		}

		if (pkt->payload != seqnum) {
			ksft_test_result_fail
				("ERROR: [%s] expected seqnum [%d], got seqnum [%d]\n",
					__func__, pkt->payload, seqnum);
			return false;
		}
	} else {
		ksft_print_msg("Invalid frame received: ");
		ksft_print_msg("[IP_PKT_VER: %02X], [IP_PKT_TOS: %02X]\n", iphdr->version,
			       iphdr->tos);
		return false;
	}

	return true;
}

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
static void kick_tx(struct xsk_socket_info *xsk)
{
	int ret;

	ret = sendto(xsk_socket__fd(xsk->xsk), NULL, 0, MSG_DONTWAIT, NULL, 0);
	if (ret >= 0 || errno == ENOBUFS || errno == EAGAIN || errno == EBUSY || errno == ENETDOWN)
		return;
	exit_with_error(errno);
}

<<<<<<< HEAD
static void complete_pkts(struct xsk_socket_info *xsk, int batch_size)
=======
static void complete_tx_only(struct xsk_socket_info *xsk, int batch_size)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
{
	unsigned int rcvd;
	u32 idx;

	if (!xsk->outstanding_tx)
		return;

	if (xsk_ring_prod__needs_wakeup(&xsk->tx))
		kick_tx(xsk);

	rcvd = xsk_ring_cons__peek(&xsk->umem->cq, batch_size, &idx);
	if (rcvd) {
		xsk_ring_cons__release(&xsk->umem->cq, rcvd);
		xsk->outstanding_tx -= rcvd;
<<<<<<< HEAD
	}
}

static void receive_pkts(struct pkt_stream *pkt_stream, struct xsk_socket_info *xsk,
			 struct pollfd *fds)
{
	u32 idx_rx = 0, idx_fq = 0, rcvd, i, pkt_count = 0;
	struct pkt *pkt;
	int ret;

	pkt = pkt_stream_get_pkt(pkt_stream, pkt_count++);
	while (pkt) {
		rcvd = xsk_ring_cons__peek(&xsk->rx, BATCH_SIZE, &idx_rx);
		if (!rcvd) {
			if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) {
				ret = poll(fds, 1, POLL_TMOUT);
				if (ret < 0)
					exit_with_error(-ret);
			}
			continue;
		}

		ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
		while (ret != rcvd) {
			if (ret < 0)
				exit_with_error(-ret);
			if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) {
				ret = poll(fds, 1, POLL_TMOUT);
				if (ret < 0)
					exit_with_error(-ret);
			}
			ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
		}

		for (i = 0; i < rcvd; i++) {
			const struct xdp_desc *desc = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++);
			u64 addr = desc->addr, orig;

			orig = xsk_umem__extract_addr(addr);
			addr = xsk_umem__add_offset_to_addr(addr);
			if (!is_pkt_valid(pkt, xsk->umem->buffer, desc))
				return;

			*xsk_ring_prod__fill_addr(&xsk->umem->fq, idx_fq++) = orig;
			pkt = pkt_stream_get_pkt(pkt_stream, pkt_count++);
		}

		xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
		xsk_ring_cons__release(&xsk->rx, rcvd);
	}
}

static u32 __send_pkts(struct ifobject *ifobject, u32 pkt_nb)
{
	struct xsk_socket_info *xsk = ifobject->xsk;
	u32 i, idx;

	while (xsk_ring_prod__reserve(&xsk->tx, BATCH_SIZE, &idx) < BATCH_SIZE)
		complete_pkts(xsk, BATCH_SIZE);

	for (i = 0; i < BATCH_SIZE; i++) {
		struct xdp_desc *tx_desc = xsk_ring_prod__tx_desc(&xsk->tx, idx + i);
		struct pkt *pkt = pkt_generate(ifobject, pkt_nb);

		if (!pkt)
			break;

		tx_desc->addr = pkt->addr;
		tx_desc->len = pkt->len;
		pkt_nb++;
	}

	xsk_ring_prod__submit(&xsk->tx, i);
	if (stat_test_type != STAT_TEST_TX_INVALID)
		xsk->outstanding_tx += i;
	else if (xsk_ring_prod__needs_wakeup(&xsk->tx))
		kick_tx(xsk);
	complete_pkts(xsk, i);

	return i;
}

static void wait_for_tx_completion(struct xsk_socket_info *xsk)
{
	while (xsk->outstanding_tx)
		complete_pkts(xsk, BATCH_SIZE);
}

static void send_pkts(struct ifobject *ifobject)
{
	struct pollfd fds[MAX_SOCKS] = { };
	u32 pkt_cnt = 0;
=======
		xsk->tx_npkts += rcvd;
	}
}

static void rx_pkt(struct xsk_socket_info *xsk, struct pollfd *fds)
{
	unsigned int rcvd, i;
	u32 idx_rx = 0, idx_fq = 0;
	int ret;

	rcvd = xsk_ring_cons__peek(&xsk->rx, BATCH_SIZE, &idx_rx);
	if (!rcvd) {
		if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) {
			ret = poll(fds, 1, POLL_TMOUT);
			if (ret < 0)
				exit_with_error(ret);
		}
		return;
	}

	ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	while (ret != rcvd) {
		if (ret < 0)
			exit_with_error(ret);
		if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq)) {
			ret = poll(fds, 1, POLL_TMOUT);
			if (ret < 0)
				exit_with_error(ret);
		}
		ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	}

	for (i = 0; i < rcvd; i++) {
		u64 addr, orig;

		addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
		xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++);
		orig = xsk_umem__extract_addr(addr);

		addr = xsk_umem__add_offset_to_addr(addr);
		pkt_node_rx = malloc(sizeof(struct pkt) + PKT_SIZE);
		if (!pkt_node_rx)
			exit_with_error(errno);

		pkt_node_rx->pkt_frame = malloc(PKT_SIZE);
		if (!pkt_node_rx->pkt_frame)
			exit_with_error(errno);

		memcpy(pkt_node_rx->pkt_frame, xsk_umem__get_data(xsk->umem->buffer, addr),
		       PKT_SIZE);

		TAILQ_INSERT_HEAD(&head, pkt_node_rx, pkt_nodes);

		*xsk_ring_prod__fill_addr(&xsk->umem->fq, idx_fq++) = orig;
	}

	xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
	xsk_ring_cons__release(&xsk->rx, rcvd);
	xsk->rx_npkts += rcvd;
}

static void tx_only(struct xsk_socket_info *xsk, u32 *frameptr, int batch_size)
{
	u32 idx = 0;
	unsigned int i;
	bool tx_invalid_test = stat_test_type == STAT_TEST_TX_INVALID;
	u32 len = tx_invalid_test ? XSK_UMEM__DEFAULT_FRAME_SIZE + 1 : PKT_SIZE;

	while (xsk_ring_prod__reserve(&xsk->tx, batch_size, &idx) < batch_size)
		complete_tx_only(xsk, batch_size);

	for (i = 0; i < batch_size; i++) {
		struct xdp_desc *tx_desc = xsk_ring_prod__tx_desc(&xsk->tx, idx + i);

		tx_desc->addr = (*frameptr + i) << XSK_UMEM__DEFAULT_FRAME_SHIFT;
		tx_desc->len = len;
	}

	xsk_ring_prod__submit(&xsk->tx, batch_size);
	if (!tx_invalid_test) {
		xsk->outstanding_tx += batch_size;
	} else if (xsk_ring_prod__needs_wakeup(&xsk->tx)) {
		kick_tx(xsk);
	}
	*frameptr += batch_size;
	*frameptr %= num_frames;
	complete_tx_only(xsk, batch_size);
}

static int get_batch_size(int pkt_cnt)
{
	if (!opt_pkt_count)
		return BATCH_SIZE;

	if (pkt_cnt + BATCH_SIZE <= opt_pkt_count)
		return BATCH_SIZE;

	return opt_pkt_count - pkt_cnt;
}

static void complete_tx_only_all(struct ifobject *ifobject)
{
	bool pending;

	do {
		pending = false;
		if (ifobject->xsk->outstanding_tx) {
			complete_tx_only(ifobject->xsk, BATCH_SIZE);
			pending = !!ifobject->xsk->outstanding_tx;
		}
	} while (pending);
}

static void tx_only_all(struct ifobject *ifobject)
{
	struct pollfd fds[MAX_SOCKS] = { };
	u32 frame_nb = 0;
	int pkt_cnt = 0;
	int ret;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	fds[0].fd = xsk_socket__fd(ifobject->xsk->xsk);
	fds[0].events = POLLOUT;

<<<<<<< HEAD
	while (pkt_cnt < ifobject->pkt_stream->nb_pkts) {
		u32 sent;

		if (test_type == TEST_TYPE_POLL) {
			int ret;

=======
	while ((opt_pkt_count && pkt_cnt < opt_pkt_count) || !opt_pkt_count) {
		int batch_size = get_batch_size(pkt_cnt);

		if (test_type == TEST_TYPE_POLL) {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
			ret = poll(fds, 1, POLL_TMOUT);
			if (ret <= 0)
				continue;

			if (!(fds[0].revents & POLLOUT))
				continue;
		}

<<<<<<< HEAD
		sent = __send_pkts(ifobject, pkt_cnt);
		pkt_cnt += sent;
		usleep(10);
	}

	wait_for_tx_completion(ifobject->xsk);
}

static bool rx_stats_are_valid(struct ifobject *ifobject)
{
	u32 xsk_stat = 0, expected_stat = ifobject->pkt_stream->nb_pkts;
	struct xsk_socket *xsk = ifobject->xsk->xsk;
	int fd = xsk_socket__fd(xsk);
	struct xdp_statistics stats;
	socklen_t optlen;
	int err;

	optlen = sizeof(stats);
	err = getsockopt(fd, SOL_XDP, XDP_STATISTICS, &stats, &optlen);
	if (err) {
		ksft_test_result_fail("ERROR: [%s] getsockopt(XDP_STATISTICS) error %u %s\n",
				      __func__, -err, strerror(-err));
		return true;
	}
=======
		tx_only(ifobject->xsk, &frame_nb, batch_size);
		pkt_cnt += batch_size;
	}

	if (opt_pkt_count)
		complete_tx_only_all(ifobject);
}

static void worker_pkt_dump(void)
{
	struct ethhdr *ethhdr;
	struct iphdr *iphdr;
	struct udphdr *udphdr;
	char s[128];
	int payload;
	void *ptr;

	fprintf(stdout, "---------------------------------------\n");
	for (int iter = 0; iter < num_frames - 1; iter++) {
		ptr = pkt_buf[iter]->payload;
		ethhdr = ptr;
		iphdr = ptr + sizeof(*ethhdr);
		udphdr = ptr + sizeof(*ethhdr) + sizeof(*iphdr);

		/*extract L2 frame */
		fprintf(stdout, "DEBUG>> L2: dst mac: ");
		for (int i = 0; i < ETH_ALEN; i++)
			fprintf(stdout, "%02X", ethhdr->h_dest[i]);

		fprintf(stdout, "\nDEBUG>> L2: src mac: ");
		for (int i = 0; i < ETH_ALEN; i++)
			fprintf(stdout, "%02X", ethhdr->h_source[i]);

		/*extract L3 frame */
		fprintf(stdout, "\nDEBUG>> L3: ip_hdr->ihl: %02X\n", iphdr->ihl);
		fprintf(stdout, "DEBUG>> L3: ip_hdr->saddr: %s\n",
			inet_ntop(AF_INET, &iphdr->saddr, s, sizeof(s)));
		fprintf(stdout, "DEBUG>> L3: ip_hdr->daddr: %s\n",
			inet_ntop(AF_INET, &iphdr->daddr, s, sizeof(s)));
		/*extract L4 frame */
		fprintf(stdout, "DEBUG>> L4: udp_hdr->src: %d\n", ntohs(udphdr->source));
		fprintf(stdout, "DEBUG>> L4: udp_hdr->dst: %d\n", ntohs(udphdr->dest));
		/*extract L5 frame */
		payload = *((uint32_t *)(ptr + PKT_HDR_SIZE));

		if (payload == EOT) {
			print_verbose("End-of-transmission frame received\n");
			fprintf(stdout, "---------------------------------------\n");
			break;
		}
		fprintf(stdout, "DEBUG>> L5: payload: %d\n", payload);
		fprintf(stdout, "---------------------------------------\n");
	}
}

static void worker_stats_validate(struct ifobject *ifobject)
{
	struct xdp_statistics stats;
	socklen_t optlen;
	int err;
	struct xsk_socket *xsk = stat_test_type == STAT_TEST_TX_INVALID ?
							ifdict[!ifobject->ifdict_index]->xsk->xsk :
							ifobject->xsk->xsk;
	int fd = xsk_socket__fd(xsk);
	unsigned long xsk_stat = 0, expected_stat = opt_pkt_count;

	sigvar = 0;

	optlen = sizeof(stats);
	err = getsockopt(fd, SOL_XDP, XDP_STATISTICS, &stats, &optlen);
	if (err)
		return;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	if (optlen == sizeof(struct xdp_statistics)) {
		switch (stat_test_type) {
		case STAT_TEST_RX_DROPPED:
			xsk_stat = stats.rx_dropped;
			break;
		case STAT_TEST_TX_INVALID:
<<<<<<< HEAD
			return true;
=======
			xsk_stat = stats.tx_invalid_descs;
			break;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		case STAT_TEST_RX_FULL:
			xsk_stat = stats.rx_ring_full;
			expected_stat -= RX_FULL_RXQSIZE;
			break;
		case STAT_TEST_RX_FILL_EMPTY:
			xsk_stat = stats.rx_fill_ring_empty_descs;
			break;
		default:
			break;
		}

		if (xsk_stat == expected_stat)
<<<<<<< HEAD
			return true;
	}

	return false;
}

static void tx_stats_validate(struct ifobject *ifobject)
{
	struct xsk_socket *xsk = ifobject->xsk->xsk;
	int fd = xsk_socket__fd(xsk);
	struct xdp_statistics stats;
	socklen_t optlen;
	int err;

	optlen = sizeof(stats);
	err = getsockopt(fd, SOL_XDP, XDP_STATISTICS, &stats, &optlen);
	if (err) {
		ksft_test_result_fail("ERROR: [%s] getsockopt(XDP_STATISTICS) error %u %s\n",
				      __func__, -err, strerror(-err));
		return;
	}

	if (stats.tx_invalid_descs == ifobject->pkt_stream->nb_pkts)
		return;

	ksft_test_result_fail("ERROR: [%s] tx_invalid_descs incorrect. Got [%u] expected [%u]\n",
			      __func__, stats.tx_invalid_descs, ifobject->pkt_stream->nb_pkts);
=======
			sigvar = 1;
	}
}

static void worker_pkt_validate(void)
{
	u32 payloadseqnum = -2;
	struct iphdr *iphdr;

	while (1) {
		pkt_node_rx_q = TAILQ_LAST(&head, head_s);
		if (!pkt_node_rx_q)
			break;

		iphdr = (struct iphdr *)(pkt_node_rx_q->pkt_frame + sizeof(struct ethhdr));

		/*do not increment pktcounter if !(tos=0x9 and ipv4) */
		if (iphdr->version == IP_PKT_VER && iphdr->tos == IP_PKT_TOS) {
			payloadseqnum = *((uint32_t *)(pkt_node_rx_q->pkt_frame + PKT_HDR_SIZE));
			if (debug_pkt_dump && payloadseqnum != EOT) {
				pkt_obj = malloc(sizeof(*pkt_obj));
				pkt_obj->payload = malloc(PKT_SIZE);
				memcpy(pkt_obj->payload, pkt_node_rx_q->pkt_frame, PKT_SIZE);
				pkt_buf[payloadseqnum] = pkt_obj;
			}

			if (payloadseqnum == EOT) {
				print_verbose("End-of-transmission frame received: PASS\n");
				sigvar = 1;
				break;
			}

			if (prev_pkt + 1 != payloadseqnum) {
				ksft_test_result_fail
				    ("ERROR: [%s] prev_pkt [%d], payloadseqnum [%d]\n",
				     __func__, prev_pkt, payloadseqnum);
				ksft_exit_xfail();
			}

			prev_pkt = payloadseqnum;
			pkt_counter++;
		} else {
			ksft_print_msg("Invalid frame received: ");
			ksft_print_msg("[IP_PKT_VER: %02X], [IP_PKT_TOS: %02X]\n", iphdr->version,
				       iphdr->tos);
		}

		TAILQ_REMOVE(&head, pkt_node_rx_q, pkt_nodes);
		free(pkt_node_rx_q->pkt_frame);
		free(pkt_node_rx_q);
		pkt_node_rx_q = NULL;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}

static void thread_common_ops(struct ifobject *ifobject, void *bufs)
{
<<<<<<< HEAD
	u64 umem_sz = num_frames * XSK_UMEM__DEFAULT_FRAME_SIZE;
	int mmap_flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE;
	size_t mmap_sz = umem_sz;
=======
	int umem_sz = num_frames * XSK_UMEM__DEFAULT_FRAME_SIZE;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	int ctr = 0;
	int ret;

	ifobject->ns_fd = switch_namespace(ifobject->nsname);

	if (test_type == TEST_TYPE_BPF_RES)
<<<<<<< HEAD
		mmap_sz *= 2;

	bufs = mmap(NULL, mmap_sz, PROT_READ | PROT_WRITE, mmap_flags, -1, 0);
	if (bufs == MAP_FAILED)
		exit_with_error(errno);

	while (ctr++ < SOCK_RECONF_CTR) {
		xsk_configure_umem(ifobject, bufs, umem_sz, 0);
		ifobject->umem = ifobject->umem_arr[0];
		ret = xsk_configure_socket(ifobject, 0);
		if (!ret)
			break;

		/* Retry Create Socket if it fails as xsk_socket__create() is asynchronous */
		usleep(USLEEP_MAX);
		if (ctr >= SOCK_RECONF_CTR)
			exit_with_error(-ret);
	}

=======
		umem_sz *= 2;

	bufs = mmap(NULL, umem_sz,
		    PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (bufs == MAP_FAILED)
		exit_with_error(errno);

	xsk_configure_umem(ifobject, bufs, 0);
	ifobject->umem = ifobject->umem_arr[0];
	ret = xsk_configure_socket(ifobject, 0);

	/* Retry Create Socket if it fails as xsk_socket__create()
	 * is asynchronous
	 */
	while (ret && ctr < SOCK_RECONF_CTR) {
		xsk_configure_umem(ifobject, bufs, 0);
		ifobject->umem = ifobject->umem_arr[0];
		ret = xsk_configure_socket(ifobject, 0);
		usleep(USLEEP_MAX);
		ctr++;
	}

	if (ctr >= SOCK_RECONF_CTR)
		exit_with_error(ret);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	ifobject->umem = ifobject->umem_arr[0];
	ifobject->xsk = ifobject->xsk_arr[0];

	if (test_type == TEST_TYPE_BPF_RES) {
<<<<<<< HEAD
		xsk_configure_umem(ifobject, (u8 *)bufs + umem_sz, umem_sz, 1);
=======
		xsk_configure_umem(ifobject, (u8 *)bufs + (umem_sz / 2), 1);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		ifobject->umem = ifobject->umem_arr[1];
		ret = xsk_configure_socket(ifobject, 1);
	}

	ifobject->umem = ifobject->umem_arr[0];
	ifobject->xsk = ifobject->xsk_arr[0];
	print_verbose("Interface [%s] vector [%s]\n",
		      ifobject->ifname, ifobject->fv.vector == tx ? "Tx" : "Rx");
}

static bool testapp_is_test_two_stepped(void)
{
	return (test_type != TEST_TYPE_BIDI && test_type != TEST_TYPE_BPF_RES) || second_step;
}

static void testapp_cleanup_xsk_res(struct ifobject *ifobj)
{
	if (testapp_is_test_two_stepped()) {
		xsk_socket__delete(ifobj->xsk->xsk);
		(void)xsk_umem__delete(ifobj->umem->umem);
	}
}

static void *worker_testapp_validate_tx(void *arg)
{
<<<<<<< HEAD
	struct ifobject *ifobject = (struct ifobject *)arg;
=======
	struct udphdr *udp_hdr =
	    (struct udphdr *)(pkt_data + sizeof(struct ethhdr) + sizeof(struct iphdr));
	struct iphdr *ip_hdr = (struct iphdr *)(pkt_data + sizeof(struct ethhdr));
	struct ethhdr *eth_hdr = (struct ethhdr *)pkt_data;
	struct ifobject *ifobject = (struct ifobject *)arg;
	struct generic_data data;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	void *bufs = NULL;

	if (!second_step)
		thread_common_ops(ifobject, bufs);

<<<<<<< HEAD
	print_verbose("Sending %d packets on interface %s\n", ifobject->pkt_stream->nb_pkts,
		      ifobject->ifname);
	send_pkts(ifobject);

	if (stat_test_type == STAT_TEST_TX_INVALID)
		tx_stats_validate(ifobject);
=======
	for (int i = 0; i < num_frames; i++) {
		/*send EOT frame */
		if (i == (num_frames - 1))
			data.seqnum = -1;
		else
			data.seqnum = i;
		gen_udp_hdr(&data, ifobject, udp_hdr);
		gen_ip_hdr(ifobject, ip_hdr);
		gen_udp_csum(udp_hdr, ip_hdr);
		gen_eth_hdr(ifobject, eth_hdr);
		gen_eth_frame(ifobject->umem, i * XSK_UMEM__DEFAULT_FRAME_SIZE);
	}

	print_verbose("Sending %d packets on interface %s\n",
		      (opt_pkt_count - 1), ifobject->ifname);
	tx_only_all(ifobject);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	testapp_cleanup_xsk_res(ifobject);
	pthread_exit(NULL);
}

static void *worker_testapp_validate_rx(void *arg)
{
	struct ifobject *ifobject = (struct ifobject *)arg;
	struct pollfd fds[MAX_SOCKS] = { };
	void *bufs = NULL;

	if (!second_step)
		thread_common_ops(ifobject, bufs);

	if (stat_test_type != STAT_TEST_RX_FILL_EMPTY)
		xsk_populate_fill_ring(ifobject->umem);

<<<<<<< HEAD
=======
	TAILQ_INIT(&head);
	if (debug_pkt_dump) {
		pkt_buf = calloc(num_frames, sizeof(*pkt_buf));
		if (!pkt_buf)
			exit_with_error(errno);
	}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	fds[0].fd = xsk_socket__fd(ifobject->xsk->xsk);
	fds[0].events = POLLIN;

	pthread_barrier_wait(&barr);

<<<<<<< HEAD
	if (test_type == TEST_TYPE_STATS)
		while (!rx_stats_are_valid(ifobject))
			continue;
	else
		receive_pkts(ifobject->pkt_stream, ifobject->xsk, fds);
=======
	while (1) {
		if (test_type != TEST_TYPE_STATS) {
			rx_pkt(ifobject->xsk, fds);
			worker_pkt_validate();
		} else {
			worker_stats_validate(ifobject);
		}
		if (sigvar)
			break;
	}

	print_verbose("Received %d packets on interface %s\n",
		      pkt_counter, ifobject->ifname);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	if (test_type == TEST_TYPE_TEARDOWN)
		print_verbose("Destroying socket\n");

	testapp_cleanup_xsk_res(ifobject);
	pthread_exit(NULL);
}

static void testapp_validate(void)
{
	bool bidi = test_type == TEST_TYPE_BIDI;
	bool bpf = test_type == TEST_TYPE_BPF_RES;
<<<<<<< HEAD
	struct pkt_stream *pkt_stream;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	if (pthread_barrier_init(&barr, NULL, 2))
		exit_with_error(errno);

<<<<<<< HEAD
	if (stat_test_type == STAT_TEST_TX_INVALID)
		pkt_stream = pkt_stream_generate(DEFAULT_PKT_CNT, XSK_UMEM__INVALID_FRAME_SIZE);
	else
		pkt_stream = pkt_stream_generate(DEFAULT_PKT_CNT, PKT_SIZE);
	ifdict_tx->pkt_stream = pkt_stream;
	ifdict_rx->pkt_stream = pkt_stream;

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	/*Spawn RX thread */
	pthread_create(&t0, NULL, ifdict_rx->func_ptr, ifdict_rx);

	pthread_barrier_wait(&barr);
	if (pthread_barrier_destroy(&barr))
		exit_with_error(errno);

	/*Spawn TX thread */
	pthread_create(&t1, NULL, ifdict_tx->func_ptr, ifdict_tx);

	pthread_join(t1, NULL);
	pthread_join(t0, NULL);

<<<<<<< HEAD
=======
	if (debug_pkt_dump && test_type != TEST_TYPE_STATS) {
		worker_pkt_dump();
		for (int iter = 0; iter < num_frames - 1; iter++) {
			free(pkt_buf[iter]->payload);
			free(pkt_buf[iter]);
		}
		free(pkt_buf);
	}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	if (!(test_type == TEST_TYPE_TEARDOWN) && !bidi && !bpf && !(test_type == TEST_TYPE_STATS))
		print_ksft_result();
}

static void testapp_teardown(void)
{
	int i;

	for (i = 0; i < MAX_TEARDOWN_ITER; i++) {
<<<<<<< HEAD
=======
		pkt_counter = 0;
		prev_pkt = -1;
		sigvar = 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		print_verbose("Creating socket\n");
		testapp_validate();
	}

	print_ksft_result();
}

static void swap_vectors(struct ifobject *ifobj1, struct ifobject *ifobj2)
{
	void *(*tmp_func_ptr)(void *) = ifobj1->func_ptr;
	enum fvector tmp_vector = ifobj1->fv.vector;

	ifobj1->func_ptr = ifobj2->func_ptr;
	ifobj1->fv.vector = ifobj2->fv.vector;

	ifobj2->func_ptr = tmp_func_ptr;
	ifobj2->fv.vector = tmp_vector;

	ifdict_tx = ifobj1;
	ifdict_rx = ifobj2;
}

static void testapp_bidi(void)
{
	for (int i = 0; i < MAX_BIDI_ITER; i++) {
<<<<<<< HEAD
=======
		pkt_counter = 0;
		prev_pkt = -1;
		sigvar = 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		print_verbose("Creating socket\n");
		testapp_validate();
		if (!second_step) {
			print_verbose("Switching Tx/Rx vectors\n");
			swap_vectors(ifdict[1], ifdict[0]);
		}
		second_step = true;
	}

	swap_vectors(ifdict[0], ifdict[1]);

	print_ksft_result();
}

static void swap_xsk_res(void)
{
	xsk_socket__delete(ifdict_tx->xsk->xsk);
	xsk_umem__delete(ifdict_tx->umem->umem);
	xsk_socket__delete(ifdict_rx->xsk->xsk);
	xsk_umem__delete(ifdict_rx->umem->umem);
	ifdict_tx->umem = ifdict_tx->umem_arr[1];
	ifdict_tx->xsk = ifdict_tx->xsk_arr[1];
	ifdict_rx->umem = ifdict_rx->umem_arr[1];
	ifdict_rx->xsk = ifdict_rx->xsk_arr[1];
}

static void testapp_bpf_res(void)
{
	int i;

	for (i = 0; i < MAX_BPF_ITER; i++) {
<<<<<<< HEAD
=======
		pkt_counter = 0;
		prev_pkt = -1;
		sigvar = 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		print_verbose("Creating socket\n");
		testapp_validate();
		if (!second_step)
			swap_xsk_res();
		second_step = true;
	}

	print_ksft_result();
}

static void testapp_stats(void)
{
	for (int i = 0; i < STAT_TEST_TYPE_MAX; i++) {
		stat_test_type = i;

		/* reset defaults */
		rxqsize = XSK_RING_CONS__DEFAULT_NUM_DESCS;
		frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM;

		switch (stat_test_type) {
		case STAT_TEST_RX_DROPPED:
			frame_headroom = XSK_UMEM__DEFAULT_FRAME_SIZE -
						XDP_PACKET_HEADROOM - 1;
			break;
		case STAT_TEST_RX_FULL:
			rxqsize = RX_FULL_RXQSIZE;
			break;
<<<<<<< HEAD
		case STAT_TEST_TX_INVALID:
			continue;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		default:
			break;
		}
		testapp_validate();
	}

	print_ksft_result();
}

static void init_iface(struct ifobject *ifobj, const char *dst_mac,
		       const char *src_mac, const char *dst_ip,
		       const char *src_ip, const u16 dst_port,
		       const u16 src_port, enum fvector vector)
{
	struct in_addr ip;

	memcpy(ifobj->dst_mac, dst_mac, ETH_ALEN);
	memcpy(ifobj->src_mac, src_mac, ETH_ALEN);

	inet_aton(dst_ip, &ip);
	ifobj->dst_ip = ip.s_addr;

	inet_aton(src_ip, &ip);
	ifobj->src_ip = ip.s_addr;

	ifobj->dst_port = dst_port;
	ifobj->src_port = src_port;

	if (vector == tx) {
		ifobj->fv.vector = tx;
		ifobj->func_ptr = worker_testapp_validate_tx;
		ifdict_tx = ifobj;
	} else {
		ifobj->fv.vector = rx;
		ifobj->func_ptr = worker_testapp_validate_rx;
		ifdict_rx = ifobj;
	}
}

static void run_pkt_test(int mode, int type)
{
	test_type = type;

	/* reset defaults after potential previous test */
	xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
<<<<<<< HEAD
	second_step = 0;
=======
	pkt_counter = 0;
	second_step = 0;
	prev_pkt = -1;
	sigvar = 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	stat_test_type = -1;
	rxqsize = XSK_RING_CONS__DEFAULT_NUM_DESCS;
	frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM;

	configured_mode = mode;

	switch (mode) {
	case (TEST_MODE_SKB):
		xdp_flags |= XDP_FLAGS_SKB_MODE;
		break;
	case (TEST_MODE_DRV):
		xdp_flags |= XDP_FLAGS_DRV_MODE;
		break;
	default:
		break;
	}

	switch (test_type) {
	case TEST_TYPE_STATS:
		testapp_stats();
		break;
	case TEST_TYPE_TEARDOWN:
		testapp_teardown();
		break;
	case TEST_TYPE_BIDI:
		testapp_bidi();
		break;
	case TEST_TYPE_BPF_RES:
		testapp_bpf_res();
		break;
	default:
		testapp_validate();
		break;
	}
}

<<<<<<< HEAD
static struct ifobject *ifobject_create(void)
{
	struct ifobject *ifobj;

	ifobj = calloc(1, sizeof(struct ifobject));
	if (!ifobj)
		return NULL;

	ifobj->xsk_arr = calloc(2, sizeof(struct xsk_socket_info *));
	if (!ifobj->xsk_arr)
		goto out_xsk_arr;

	ifobj->umem_arr = calloc(2, sizeof(struct xsk_umem_info *));
	if (!ifobj->umem_arr)
		goto out_umem_arr;

	return ifobj;

out_umem_arr:
	free(ifobj->xsk_arr);
out_xsk_arr:
	free(ifobj);
	return NULL;
}

static void ifobject_delete(struct ifobject *ifobj)
{
	free(ifobj->umem_arr);
	free(ifobj->xsk_arr);
	free(ifobj);
}

int main(int argc, char **argv)
{
	struct rlimit _rlim = { RLIM_INFINITY, RLIM_INFINITY };
=======
int main(int argc, char **argv)
{
	struct rlimit _rlim = { RLIM_INFINITY, RLIM_INFINITY };
	bool failure = false;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	int i, j;

	if (setrlimit(RLIMIT_MEMLOCK, &_rlim))
		exit_with_error(errno);

<<<<<<< HEAD
	for (i = 0; i < MAX_INTERFACES; i++) {
		ifdict[i] = ifobject_create();
		if (!ifdict[i])
			exit_with_error(ENOMEM);
=======
	for (int i = 0; i < MAX_INTERFACES; i++) {
		ifdict[i] = malloc(sizeof(struct ifobject));
		if (!ifdict[i])
			exit_with_error(errno);

		ifdict[i]->ifdict_index = i;
		ifdict[i]->xsk_arr = calloc(2, sizeof(struct xsk_socket_info *));
		if (!ifdict[i]->xsk_arr) {
			failure = true;
			goto cleanup;
		}
		ifdict[i]->umem_arr = calloc(2, sizeof(struct xsk_umem_info *));
		if (!ifdict[i]->umem_arr) {
			failure = true;
			goto cleanup;
		}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	}

	setlocale(LC_ALL, "");

	parse_command_line(argc, argv);

<<<<<<< HEAD
	init_iface(ifdict[tx], MAC1, MAC2, IP1, IP2, UDP_PORT1, UDP_PORT2, tx);
	init_iface(ifdict[rx], MAC2, MAC1, IP2, IP1, UDP_PORT2, UDP_PORT1, rx);

	ksft_set_plan(TEST_MODE_MAX * TEST_TYPE_MAX);

	for (i = 0; i < TEST_MODE_MAX; i++)
		for (j = 0; j < TEST_TYPE_MAX; j++) {
			run_pkt_test(i, j);
			usleep(USLEEP_MAX);
		}

	for (i = 0; i < MAX_INTERFACES; i++)
		ifobject_delete(ifdict[i]);

	ksft_exit_pass();
=======
	num_frames = ++opt_pkt_count;

	init_iface(ifdict[0], MAC1, MAC2, IP1, IP2, UDP_PORT1, UDP_PORT2, tx);
	init_iface(ifdict[1], MAC2, MAC1, IP2, IP1, UDP_PORT2, UDP_PORT1, rx);

	ksft_set_plan(TEST_MODE_MAX * TEST_TYPE_MAX);

	for (i = 0; i < TEST_MODE_MAX; i++) {
		for (j = 0; j < TEST_TYPE_MAX; j++)
			run_pkt_test(i, j);
	}

cleanup:
	for (int i = 0; i < MAX_INTERFACES; i++) {
		if (ifdict[i]->ns_fd != -1)
			close(ifdict[i]->ns_fd);
		free(ifdict[i]->xsk_arr);
		free(ifdict[i]->umem_arr);
		free(ifdict[i]);
	}

	if (failure)
		exit_with_error(errno);

	ksft_exit_pass();

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	return 0;
}
