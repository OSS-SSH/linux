/* SPDX-License-Identifier: GPL-2.0
 * Copyright(c) 2020 Intel Corporation.
 */

#ifndef XDPXCEIVER_H_
#define XDPXCEIVER_H_

#ifndef SOL_XDP
#define SOL_XDP 283
#endif

#ifndef AF_XDP
#define AF_XDP 44
#endif

#ifndef PF_XDP
#define PF_XDP AF_XDP
#endif

#define MAX_INTERFACES 2
#define MAX_INTERFACE_NAME_CHARS 7
#define MAX_INTERFACES_NAMESPACE_CHARS 10
#define MAX_SOCKS 1
#define MAX_TEARDOWN_ITER 10
#define MAX_BIDI_ITER 2
#define MAX_BPF_ITER 2
#define PKT_HDR_SIZE (sizeof(struct ethhdr) + sizeof(struct iphdr) + \
			sizeof(struct udphdr))
#define MIN_PKT_SIZE 64
#define ETH_FCS_SIZE 4
#define PKT_SIZE (MIN_PKT_SIZE - ETH_FCS_SIZE)
#define IP_PKT_SIZE (PKT_SIZE - sizeof(struct ethhdr))
#define IP_PKT_VER 0x4
#define IP_PKT_TOS 0x9
#define UDP_PKT_SIZE (IP_PKT_SIZE - sizeof(struct iphdr))
#define UDP_PKT_DATA_SIZE (UDP_PKT_SIZE - sizeof(struct udphdr))
<<<<<<< HEAD
#define USLEEP_MAX 10000
#define SOCK_RECONF_CTR 10
#define BATCH_SIZE 8
#define POLL_TMOUT 1000
#define DEFAULT_PKT_CNT (4 * 1024)
#define RX_FULL_RXQSIZE 32
#define XSK_UMEM__INVALID_FRAME_SIZE (XSK_UMEM__DEFAULT_FRAME_SIZE + 1)

#define print_verbose(x...) do { if (opt_verbose) ksft_print_msg(x); } while (0)

enum test_mode {
=======
#define EOT (-1)
#define USLEEP_MAX 200000
#define SOCK_RECONF_CTR 10
#define BATCH_SIZE 64
#define POLL_TMOUT 1000
#define DEFAULT_PKT_CNT 10000
#define RX_FULL_RXQSIZE 32

#define print_verbose(x...) do { if (opt_verbose) ksft_print_msg(x); } while (0)

typedef __u32 u32;
typedef __u16 u16;
typedef __u8 u8;

enum TEST_MODES {
	TEST_MODE_UNCONFIGURED = -1,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	TEST_MODE_SKB,
	TEST_MODE_DRV,
	TEST_MODE_MAX
};

<<<<<<< HEAD
enum test_type {
=======
enum TEST_TYPES {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	TEST_TYPE_NOPOLL,
	TEST_TYPE_POLL,
	TEST_TYPE_TEARDOWN,
	TEST_TYPE_BIDI,
	TEST_TYPE_STATS,
	TEST_TYPE_BPF_RES,
	TEST_TYPE_MAX
};

<<<<<<< HEAD
enum stat_test_type {
=======
enum STAT_TEST_TYPES {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	STAT_TEST_RX_DROPPED,
	STAT_TEST_TX_INVALID,
	STAT_TEST_RX_FULL,
	STAT_TEST_RX_FILL_EMPTY,
	STAT_TEST_TYPE_MAX
};

<<<<<<< HEAD
static int configured_mode;
static bool opt_pkt_dump;
static u32 num_frames = DEFAULT_PKT_CNT / 4;
static bool second_step;
static int test_type;

static bool opt_verbose;

static u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
static u32 xdp_bind_flags = XDP_USE_NEED_WAKEUP | XDP_COPY;
=======
static int configured_mode = TEST_MODE_UNCONFIGURED;
static u8 debug_pkt_dump;
static u32 num_frames;
static bool second_step;
static int test_type;

static int opt_pkt_count;
static u8 opt_verbose;

static u32 xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
static u32 xdp_bind_flags = XDP_USE_NEED_WAKEUP | XDP_COPY;
static u8 pkt_data[XSK_UMEM__DEFAULT_FRAME_SIZE];
static u32 pkt_counter;
static long prev_pkt = -1;
static int sigvar;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
static int stat_test_type;
static u32 rxqsize;
static u32 frame_headroom;

struct xsk_umem_info {
	struct xsk_ring_prod fq;
	struct xsk_ring_cons cq;
	struct xsk_umem *umem;
	void *buffer;
};

struct xsk_socket_info {
	struct xsk_ring_cons rx;
	struct xsk_ring_prod tx;
	struct xsk_umem_info *umem;
	struct xsk_socket *xsk;
<<<<<<< HEAD
=======
	unsigned long rx_npkts;
	unsigned long tx_npkts;
	unsigned long prev_rx_npkts;
	unsigned long prev_tx_npkts;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	u32 outstanding_tx;
};

struct flow_vector {
	enum fvector {
		tx,
		rx,
	} vector;
};

<<<<<<< HEAD
struct pkt {
	u64 addr;
	u32 len;
	u32 payload;
};

struct pkt_stream {
	u32 nb_pkts;
	struct pkt *pkts;
=======
struct generic_data {
	u32 seqnum;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
};

struct ifobject {
	char ifname[MAX_INTERFACE_NAME_CHARS];
	char nsname[MAX_INTERFACES_NAMESPACE_CHARS];
	struct xsk_socket_info *xsk;
	struct xsk_socket_info **xsk_arr;
	struct xsk_umem_info **umem_arr;
	struct xsk_umem_info *umem;
	void *(*func_ptr)(void *arg);
	struct flow_vector fv;
<<<<<<< HEAD
	struct pkt_stream *pkt_stream;
	int ns_fd;
=======
	int ns_fd;
	int ifdict_index;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	u32 dst_ip;
	u32 src_ip;
	u16 src_port;
	u16 dst_port;
	u8 dst_mac[ETH_ALEN];
	u8 src_mac[ETH_ALEN];
};

static struct ifobject *ifdict[MAX_INTERFACES];
static struct ifobject *ifdict_rx;
static struct ifobject *ifdict_tx;

/*threads*/
pthread_barrier_t barr;
pthread_t t0, t1;

<<<<<<< HEAD
=======
TAILQ_HEAD(head_s, pkt) head = TAILQ_HEAD_INITIALIZER(head);
struct head_s *head_p;
struct pkt {
	char *pkt_frame;

	TAILQ_ENTRY(pkt) pkt_nodes;
} *pkt_node_rx, *pkt_node_rx_q;

struct pkt_frame {
	char *payload;
} *pkt_obj;

struct pkt_frame **pkt_buf;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif				/* XDPXCEIVER_H */
