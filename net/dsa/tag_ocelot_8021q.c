// SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
<<<<<<< HEAD
/* Copyright 2020-2021 NXP
=======
/* Copyright 2020-2021 NXP Semiconductors
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
/* Copyright 2020-2021 NXP
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 *
 * An implementation of the software-defined tag_8021q.c tagger format, which
 * also preserves full functionality under a vlan_filtering bridge. It does
 * this by using the TCAM engines for:
 * - pushing the RX VLAN as a second, outer tag, on egress towards the CPU port
 * - redirecting towards the correct front port based on TX VLAN and popping
 *   that on egress
 */
#include <linux/dsa/8021q.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/dsa/ocelot.h>
#include "dsa_priv.h"

static struct sk_buff *ocelot_defer_xmit(struct dsa_port *dp,
					 struct sk_buff *skb)
{
	struct felix_deferred_xmit_work *xmit_work;
	struct felix_port *felix_port = dp->priv;

	xmit_work = kzalloc(sizeof(*xmit_work), GFP_ATOMIC);
	if (!xmit_work)
		return NULL;

	/* Calls felix_port_deferred_xmit in felix.c */
	kthread_init_work(&xmit_work->work, felix_port->xmit_work_fn);
	/* Increase refcount so the kfree_skb in dsa_slave_xmit
	 * won't really free the packet.
	 */
	xmit_work->dp = dp;
	xmit_work->skb = skb_get(skb);

	kthread_queue_work(felix_port->xmit_worker, &xmit_work->work);

	return NULL;
}

=======
#include <soc/mscc/ocelot.h>
#include <soc/mscc/ocelot_ptp.h>
#include "dsa_priv.h"

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <linux/dsa/ocelot.h>
#include "dsa_priv.h"

static struct sk_buff *ocelot_defer_xmit(struct dsa_port *dp,
					 struct sk_buff *skb)
{
	struct felix_deferred_xmit_work *xmit_work;
	struct felix_port *felix_port = dp->priv;

	xmit_work = kzalloc(sizeof(*xmit_work), GFP_ATOMIC);
	if (!xmit_work)
		return NULL;

	/* Calls felix_port_deferred_xmit in felix.c */
	kthread_init_work(&xmit_work->work, felix_port->xmit_work_fn);
	/* Increase refcount so the kfree_skb in dsa_slave_xmit
	 * won't really free the packet.
	 */
	xmit_work->dp = dp;
	xmit_work->skb = skb_get(skb);

	kthread_queue_work(felix_port->xmit_worker, &xmit_work->work);

	return NULL;
}

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static struct sk_buff *ocelot_xmit(struct sk_buff *skb,
				   struct net_device *netdev)
{
	struct dsa_port *dp = dsa_slave_to_port(netdev);
	u16 tx_vid = dsa_8021q_tx_vid(dp->ds, dp->index);
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pcp = netdev_txq_to_tc(netdev, queue_mapping);
<<<<<<< HEAD
<<<<<<< HEAD
	struct ethhdr *hdr = eth_hdr(skb);

	if (ocelot_ptp_rew_op(skb) || is_link_local_ether_addr(hdr->h_dest))
		return ocelot_defer_xmit(dp, skb);
=======
	struct ocelot *ocelot = dp->ds->priv;
	int port = dp->index;
	u32 rew_op = 0;

	rew_op = ocelot_ptp_rew_op(skb);
	if (rew_op) {
		if (!ocelot_can_inject(ocelot, 0))
			return NULL;

		ocelot_port_inject_frame(ocelot, port, 0, rew_op, skb);
		return NULL;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct ethhdr *hdr = eth_hdr(skb);

	if (ocelot_ptp_rew_op(skb) || is_link_local_ether_addr(hdr->h_dest))
		return ocelot_defer_xmit(dp, skb);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return dsa_8021q_xmit(skb, netdev, ETH_P_8021Q,
			      ((pcp << VLAN_PRIO_SHIFT) | tx_vid));
}

static struct sk_buff *ocelot_rcv(struct sk_buff *skb,
<<<<<<< HEAD
<<<<<<< HEAD
				  struct net_device *netdev)
{
	int src_port, switch_id;

	dsa_8021q_rcv(skb, &src_port, &switch_id);
=======
				  struct net_device *netdev,
				  struct packet_type *pt)
=======
				  struct net_device *netdev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int src_port, switch_id;

<<<<<<< HEAD
	dsa_8021q_rcv(skb, &src_port, &switch_id, &subvlan);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	dsa_8021q_rcv(skb, &src_port, &switch_id);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	skb->dev = dsa_master_find_slave(netdev, switch_id, src_port);
	if (!skb->dev)
		return NULL;

<<<<<<< HEAD
<<<<<<< HEAD
	dsa_default_offload_fwd_mark(skb);
=======
	skb->offload_fwd_mark = 1;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	dsa_default_offload_fwd_mark(skb);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return skb;
}

static const struct dsa_device_ops ocelot_8021q_netdev_ops = {
	.name			= "ocelot-8021q",
	.proto			= DSA_TAG_PROTO_OCELOT_8021Q,
	.xmit			= ocelot_xmit,
	.rcv			= ocelot_rcv,
	.needed_headroom	= VLAN_HLEN,
	.promisc_on_master	= true,
};

MODULE_LICENSE("GPL v2");
MODULE_ALIAS_DSA_TAG_DRIVER(DSA_TAG_PROTO_OCELOT_8021Q);

module_dsa_tag_driver(ocelot_8021q_netdev_ops);
