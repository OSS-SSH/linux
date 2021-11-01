// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 *
 * This module is not a complete tagger implementation. It only provides
 * primitives for taggers that rely on 802.1Q VLAN tags to use. The
 * dsa_8021q_netdev_ops is registered for API compliance and not used
 * directly by callers.
 */
#include <linux/if_bridge.h>
#include <linux/if_vlan.h>
#include <linux/dsa/8021q.h>

#include "dsa_priv.h"

/* Binary structure of the fake 12-bit VID field (when the TPID is
 * ETH_P_DSA_8021Q):
 *
 * | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +-----------+-----+-----------------+-----------+-----------------------+
<<<<<<< HEAD
<<<<<<< HEAD
 * |    DIR    | VBID|    SWITCH_ID    |   VBID    |          PORT         |
=======
 * |    DIR    | SVL |    SWITCH_ID    |  SUBVLAN  |          PORT         |
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * |    DIR    | VBID|    SWITCH_ID    |   VBID    |          PORT         |
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * +-----------+-----+-----------------+-----------+-----------------------+
 *
 * DIR - VID[11:10]:
 *	Direction flags.
 *	* 1 (0b01) for RX VLAN,
 *	* 2 (0b10) for TX VLAN.
 *	These values make the special VIDs of 0, 1 and 4095 to be left
 *	unused by this coding scheme.
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * SWITCH_ID - VID[8:6]:
 *	Index of switch within DSA tree. Must be between 0 and 7.
 *
 * VBID - { VID[9], VID[5:4] }:
 *	Virtual bridge ID. If between 1 and 7, packet targets the broadcast
 *	domain of a bridge. If transmitted as zero, packet targets a single
 *	port. Field only valid on transmit, must be ignored on receive.
 *
=======
 * SVL/SUBVLAN - { VID[9], VID[5:4] }:
 *	Sub-VLAN encoding. Valid only when DIR indicates an RX VLAN.
 *	* 0 (0b000): Field does not encode a sub-VLAN, either because
 *	received traffic is untagged, PVID-tagged or because a second
 *	VLAN tag is present after this tag and not inside of it.
 *	* 1 (0b001): Received traffic is tagged with a VID value private
 *	to the host. This field encodes the index in the host's lookup
 *	table through which the value of the ingress VLAN ID can be
 *	recovered.
 *	* 2 (0b010): Field encodes a sub-VLAN.
 *	...
 *	* 7 (0b111): Field encodes a sub-VLAN.
 *	When DIR indicates a TX VLAN, SUBVLAN must be transmitted as zero
 *	(by the host) and ignored on receive (by the switch).
 *
 * SWITCH_ID - VID[8:6]:
 *	Index of switch within DSA tree. Must be between 0 and 7.
 *
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * SWITCH_ID - VID[8:6]:
 *	Index of switch within DSA tree. Must be between 0 and 7.
 *
 * VBID - { VID[9], VID[5:4] }:
 *	Virtual bridge ID. If between 1 and 7, packet targets the broadcast
 *	domain of a bridge. If transmitted as zero, packet targets a single
 *	port. Field only valid on transmit, must be ignored on receive.
 *
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * PORT - VID[3:0]:
 *	Index of switch port. Must be between 0 and 15.
 */

#define DSA_8021Q_DIR_SHIFT		10
#define DSA_8021Q_DIR_MASK		GENMASK(11, 10)
#define DSA_8021Q_DIR(x)		(((x) << DSA_8021Q_DIR_SHIFT) & \
						 DSA_8021Q_DIR_MASK)
#define DSA_8021Q_DIR_RX		DSA_8021Q_DIR(1)
#define DSA_8021Q_DIR_TX		DSA_8021Q_DIR(2)

#define DSA_8021Q_SWITCH_ID_SHIFT	6
#define DSA_8021Q_SWITCH_ID_MASK	GENMASK(8, 6)
#define DSA_8021Q_SWITCH_ID(x)		(((x) << DSA_8021Q_SWITCH_ID_SHIFT) & \
						 DSA_8021Q_SWITCH_ID_MASK)

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define DSA_8021Q_VBID_HI_SHIFT		9
#define DSA_8021Q_VBID_HI_MASK		GENMASK(9, 9)
#define DSA_8021Q_VBID_LO_SHIFT		4
#define DSA_8021Q_VBID_LO_MASK		GENMASK(5, 4)
#define DSA_8021Q_VBID_HI(x)		(((x) & GENMASK(2, 2)) >> 2)
#define DSA_8021Q_VBID_LO(x)		((x) & GENMASK(1, 0))
#define DSA_8021Q_VBID(x)		\
		(((DSA_8021Q_VBID_LO(x) << DSA_8021Q_VBID_LO_SHIFT) & \
		  DSA_8021Q_VBID_LO_MASK) | \
		 ((DSA_8021Q_VBID_HI(x) << DSA_8021Q_VBID_HI_SHIFT) & \
		  DSA_8021Q_VBID_HI_MASK))
<<<<<<< HEAD
=======
#define DSA_8021Q_SUBVLAN_HI_SHIFT	9
#define DSA_8021Q_SUBVLAN_HI_MASK	GENMASK(9, 9)
#define DSA_8021Q_SUBVLAN_LO_SHIFT	4
#define DSA_8021Q_SUBVLAN_LO_MASK	GENMASK(5, 4)
#define DSA_8021Q_SUBVLAN_HI(x)		(((x) & GENMASK(2, 2)) >> 2)
#define DSA_8021Q_SUBVLAN_LO(x)		((x) & GENMASK(1, 0))
#define DSA_8021Q_SUBVLAN(x)		\
		(((DSA_8021Q_SUBVLAN_LO(x) << DSA_8021Q_SUBVLAN_LO_SHIFT) & \
		  DSA_8021Q_SUBVLAN_LO_MASK) | \
		 ((DSA_8021Q_SUBVLAN_HI(x) << DSA_8021Q_SUBVLAN_HI_SHIFT) & \
		  DSA_8021Q_SUBVLAN_HI_MASK))
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#define DSA_8021Q_PORT_SHIFT		0
#define DSA_8021Q_PORT_MASK		GENMASK(3, 0)
#define DSA_8021Q_PORT(x)		(((x) << DSA_8021Q_PORT_SHIFT) & \
						 DSA_8021Q_PORT_MASK)

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
u16 dsa_8021q_bridge_tx_fwd_offload_vid(int bridge_num)
{
	/* The VBID value of 0 is reserved for precise TX */
	return DSA_8021Q_DIR_TX | DSA_8021Q_VBID(bridge_num + 1);
}
EXPORT_SYMBOL_GPL(dsa_8021q_bridge_tx_fwd_offload_vid);

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/* Returns the VID to be inserted into the frame from xmit for switch steering
 * instructions on egress. Encodes switch ID and port ID.
 */
u16 dsa_8021q_tx_vid(struct dsa_switch *ds, int port)
{
	return DSA_8021Q_DIR_TX | DSA_8021Q_SWITCH_ID(ds->index) |
	       DSA_8021Q_PORT(port);
}
EXPORT_SYMBOL_GPL(dsa_8021q_tx_vid);

/* Returns the VID that will be installed as pvid for this switch port, sent as
 * tagged egress towards the CPU port and decoded by the rcv function.
 */
u16 dsa_8021q_rx_vid(struct dsa_switch *ds, int port)
{
	return DSA_8021Q_DIR_RX | DSA_8021Q_SWITCH_ID(ds->index) |
	       DSA_8021Q_PORT(port);
}
EXPORT_SYMBOL_GPL(dsa_8021q_rx_vid);

<<<<<<< HEAD
<<<<<<< HEAD
=======
u16 dsa_8021q_rx_vid_subvlan(struct dsa_switch *ds, int port, u16 subvlan)
{
	return DSA_8021Q_DIR_RX | DSA_8021Q_SWITCH_ID(ds->index) |
	       DSA_8021Q_PORT(port) | DSA_8021Q_SUBVLAN(subvlan);
}
EXPORT_SYMBOL_GPL(dsa_8021q_rx_vid_subvlan);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/* Returns the decoded switch ID from the RX VID. */
int dsa_8021q_rx_switch_id(u16 vid)
{
	return (vid & DSA_8021Q_SWITCH_ID_MASK) >> DSA_8021Q_SWITCH_ID_SHIFT;
}
EXPORT_SYMBOL_GPL(dsa_8021q_rx_switch_id);

/* Returns the decoded port ID from the RX VID. */
int dsa_8021q_rx_source_port(u16 vid)
{
	return (vid & DSA_8021Q_PORT_MASK) >> DSA_8021Q_PORT_SHIFT;
}
EXPORT_SYMBOL_GPL(dsa_8021q_rx_source_port);

<<<<<<< HEAD
<<<<<<< HEAD
=======
/* Returns the decoded subvlan from the RX VID. */
u16 dsa_8021q_rx_subvlan(u16 vid)
{
	u16 svl_hi, svl_lo;

	svl_hi = (vid & DSA_8021Q_SUBVLAN_HI_MASK) >>
		 DSA_8021Q_SUBVLAN_HI_SHIFT;
	svl_lo = (vid & DSA_8021Q_SUBVLAN_LO_MASK) >>
		 DSA_8021Q_SUBVLAN_LO_SHIFT;

	return (svl_hi << 2) | svl_lo;
}
EXPORT_SYMBOL_GPL(dsa_8021q_rx_subvlan);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
bool vid_is_dsa_8021q_rxvlan(u16 vid)
{
	return (vid & DSA_8021Q_DIR_MASK) == DSA_8021Q_DIR_RX;
}
EXPORT_SYMBOL_GPL(vid_is_dsa_8021q_rxvlan);

bool vid_is_dsa_8021q_txvlan(u16 vid)
{
	return (vid & DSA_8021Q_DIR_MASK) == DSA_8021Q_DIR_TX;
}
EXPORT_SYMBOL_GPL(vid_is_dsa_8021q_txvlan);

bool vid_is_dsa_8021q(u16 vid)
{
	return vid_is_dsa_8021q_rxvlan(vid) || vid_is_dsa_8021q_txvlan(vid);
}
EXPORT_SYMBOL_GPL(vid_is_dsa_8021q);

<<<<<<< HEAD
<<<<<<< HEAD
static struct dsa_tag_8021q_vlan *
dsa_tag_8021q_vlan_find(struct dsa_8021q_context *ctx, int port, u16 vid)
{
	struct dsa_tag_8021q_vlan *v;

	list_for_each_entry(v, &ctx->vlans, list)
		if (v->vid == vid && v->port == port)
			return v;

	return NULL;
}

static int dsa_switch_do_tag_8021q_vlan_add(struct dsa_switch *ds, int port,
					    u16 vid, u16 flags)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	struct dsa_tag_8021q_vlan *v;
	int err;

	/* No need to bother with refcounting for user ports */
	if (!(dsa_port_is_cpu(dp) || dsa_port_is_dsa(dp)))
		return ds->ops->tag_8021q_vlan_add(ds, port, vid, flags);

	v = dsa_tag_8021q_vlan_find(ctx, port, vid);
	if (v) {
		refcount_inc(&v->refcount);
		return 0;
	}

	v = kzalloc(sizeof(*v), GFP_KERNEL);
	if (!v)
		return -ENOMEM;

	err = ds->ops->tag_8021q_vlan_add(ds, port, vid, flags);
	if (err) {
		kfree(v);
		return err;
	}

	v->vid = vid;
	v->port = port;
	refcount_set(&v->refcount, 1);
	list_add_tail(&v->list, &ctx->vlans);

	return 0;
}

static int dsa_switch_do_tag_8021q_vlan_del(struct dsa_switch *ds, int port,
					    u16 vid)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	struct dsa_tag_8021q_vlan *v;
	int err;

	/* No need to bother with refcounting for user ports */
	if (!(dsa_port_is_cpu(dp) || dsa_port_is_dsa(dp)))
		return ds->ops->tag_8021q_vlan_del(ds, port, vid);

	v = dsa_tag_8021q_vlan_find(ctx, port, vid);
	if (!v)
		return -ENOENT;

	if (!refcount_dec_and_test(&v->refcount))
		return 0;

	err = ds->ops->tag_8021q_vlan_del(ds, port, vid);
	if (err) {
		refcount_inc(&v->refcount);
		return err;
	}

	list_del(&v->list);
	kfree(v);

	return 0;
}

static bool
dsa_switch_tag_8021q_vlan_match(struct dsa_switch *ds, int port,
				struct dsa_notifier_tag_8021q_vlan_info *info)
{
	if (dsa_is_dsa_port(ds, port) || dsa_is_cpu_port(ds, port))
		return true;

	if (ds->dst->index == info->tree_index && ds->index == info->sw_index)
		return port == info->port;

	return false;
}

int dsa_switch_tag_8021q_vlan_add(struct dsa_switch *ds,
				  struct dsa_notifier_tag_8021q_vlan_info *info)
{
	int port, err;

	/* Since we use dsa_broadcast(), there might be other switches in other
	 * trees which don't support tag_8021q, so don't return an error.
	 * Or they might even support tag_8021q but have not registered yet to
	 * use it (maybe they use another tagger currently).
	 */
	if (!ds->ops->tag_8021q_vlan_add || !ds->tag_8021q_ctx)
		return 0;

	for (port = 0; port < ds->num_ports; port++) {
		if (dsa_switch_tag_8021q_vlan_match(ds, port, info)) {
			u16 flags = 0;

			if (dsa_is_user_port(ds, port))
				flags |= BRIDGE_VLAN_INFO_UNTAGGED;

			if (vid_is_dsa_8021q_rxvlan(info->vid) &&
			    dsa_8021q_rx_switch_id(info->vid) == ds->index &&
			    dsa_8021q_rx_source_port(info->vid) == port)
				flags |= BRIDGE_VLAN_INFO_PVID;

			err = dsa_switch_do_tag_8021q_vlan_add(ds, port,
							       info->vid,
							       flags);
			if (err)
				return err;
		}
	}

	return 0;
}

int dsa_switch_tag_8021q_vlan_del(struct dsa_switch *ds,
				  struct dsa_notifier_tag_8021q_vlan_info *info)
{
	int port, err;

	if (!ds->ops->tag_8021q_vlan_del || !ds->tag_8021q_ctx)
		return 0;

	for (port = 0; port < ds->num_ports; port++) {
		if (dsa_switch_tag_8021q_vlan_match(ds, port, info)) {
			err = dsa_switch_do_tag_8021q_vlan_del(ds, port,
							       info->vid);
			if (err)
				return err;
		}
	}

	return 0;
=======
/* If @enabled is true, installs @vid with @flags into the switch port's HW
 * filter.
 * If @enabled is false, deletes @vid (ignores @flags) from the port. Had the
 * user explicitly configured this @vid through the bridge core, then the @vid
 * is installed again, but this time with the flags from the bridge layer.
 */
static int dsa_8021q_vid_apply(struct dsa_8021q_context *ctx, int port, u16 vid,
			       u16 flags, bool enabled)
=======
static struct dsa_tag_8021q_vlan *
dsa_tag_8021q_vlan_find(struct dsa_8021q_context *ctx, int port, u16 vid)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct dsa_tag_8021q_vlan *v;

	list_for_each_entry(v, &ctx->vlans, list)
		if (v->vid == vid && v->port == port)
			return v;

<<<<<<< HEAD
	return ctx->ops->vlan_del(ctx->ds, dp->index, vid);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return NULL;
}

static int dsa_switch_do_tag_8021q_vlan_add(struct dsa_switch *ds, int port,
					    u16 vid, u16 flags)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	struct dsa_tag_8021q_vlan *v;
	int err;

	/* No need to bother with refcounting for user ports */
	if (!(dsa_port_is_cpu(dp) || dsa_port_is_dsa(dp)))
		return ds->ops->tag_8021q_vlan_add(ds, port, vid, flags);

	v = dsa_tag_8021q_vlan_find(ctx, port, vid);
	if (v) {
		refcount_inc(&v->refcount);
		return 0;
	}

	v = kzalloc(sizeof(*v), GFP_KERNEL);
	if (!v)
		return -ENOMEM;

	err = ds->ops->tag_8021q_vlan_add(ds, port, vid, flags);
	if (err) {
		kfree(v);
		return err;
	}

	v->vid = vid;
	v->port = port;
	refcount_set(&v->refcount, 1);
	list_add_tail(&v->list, &ctx->vlans);

	return 0;
}

static int dsa_switch_do_tag_8021q_vlan_del(struct dsa_switch *ds, int port,
					    u16 vid)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	struct dsa_tag_8021q_vlan *v;
	int err;

	/* No need to bother with refcounting for user ports */
	if (!(dsa_port_is_cpu(dp) || dsa_port_is_dsa(dp)))
		return ds->ops->tag_8021q_vlan_del(ds, port, vid);

	v = dsa_tag_8021q_vlan_find(ctx, port, vid);
	if (!v)
		return -ENOENT;

	if (!refcount_dec_and_test(&v->refcount))
		return 0;

	err = ds->ops->tag_8021q_vlan_del(ds, port, vid);
	if (err) {
		refcount_inc(&v->refcount);
		return err;
	}

	list_del(&v->list);
	kfree(v);

	return 0;
}

static bool
dsa_switch_tag_8021q_vlan_match(struct dsa_switch *ds, int port,
				struct dsa_notifier_tag_8021q_vlan_info *info)
{
	if (dsa_is_dsa_port(ds, port) || dsa_is_cpu_port(ds, port))
		return true;

	if (ds->dst->index == info->tree_index && ds->index == info->sw_index)
		return port == info->port;

	return false;
}

int dsa_switch_tag_8021q_vlan_add(struct dsa_switch *ds,
				  struct dsa_notifier_tag_8021q_vlan_info *info)
{
	int port, err;

	/* Since we use dsa_broadcast(), there might be other switches in other
	 * trees which don't support tag_8021q, so don't return an error.
	 * Or they might even support tag_8021q but have not registered yet to
	 * use it (maybe they use another tagger currently).
	 */
	if (!ds->ops->tag_8021q_vlan_add || !ds->tag_8021q_ctx)
		return 0;

	for (port = 0; port < ds->num_ports; port++) {
		if (dsa_switch_tag_8021q_vlan_match(ds, port, info)) {
			u16 flags = 0;

			if (dsa_is_user_port(ds, port))
				flags |= BRIDGE_VLAN_INFO_UNTAGGED;

			if (vid_is_dsa_8021q_rxvlan(info->vid) &&
			    dsa_8021q_rx_switch_id(info->vid) == ds->index &&
			    dsa_8021q_rx_source_port(info->vid) == port)
				flags |= BRIDGE_VLAN_INFO_PVID;

			err = dsa_switch_do_tag_8021q_vlan_add(ds, port,
							       info->vid,
							       flags);
			if (err)
				return err;
		}
	}

	return 0;
}

int dsa_switch_tag_8021q_vlan_del(struct dsa_switch *ds,
				  struct dsa_notifier_tag_8021q_vlan_info *info)
{
	int port, err;

	if (!ds->ops->tag_8021q_vlan_del || !ds->tag_8021q_ctx)
		return 0;

	for (port = 0; port < ds->num_ports; port++) {
		if (dsa_switch_tag_8021q_vlan_match(ds, port, info)) {
			err = dsa_switch_do_tag_8021q_vlan_del(ds, port,
							       info->vid);
			if (err)
				return err;
		}
	}

	return 0;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

/* RX VLAN tagging (left) and TX VLAN tagging (right) setup shown for a single
 * front-panel switch port (here swp0).
 *
 * Port identification through VLAN (802.1Q) tags has different requirements
 * for it to work effectively:
 *  - On RX (ingress from network): each front-panel port must have a pvid
 *    that uniquely identifies it, and the egress of this pvid must be tagged
 *    towards the CPU port, so that software can recover the source port based
 *    on the VID in the frame. But this would only work for standalone ports;
 *    if bridged, this VLAN setup would break autonomous forwarding and would
 *    force all switched traffic to pass through the CPU. So we must also make
 *    the other front-panel ports members of this VID we're adding, albeit
 *    we're not making it their PVID (they'll still have their own).
<<<<<<< HEAD
<<<<<<< HEAD
=======
 *    By the way - just because we're installing the same VID in multiple
 *    switch ports doesn't mean that they'll start to talk to one another, even
 *    while not bridged: the final forwarding decision is still an AND between
 *    the L2 forwarding information (which is limiting forwarding in this case)
 *    and the VLAN-based restrictions (of which there are none in this case,
 *    since all ports are members).
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 *  - On TX (ingress from CPU and towards network) we are faced with a problem.
 *    If we were to tag traffic (from within DSA) with the port's pvid, all
 *    would be well, assuming the switch ports were standalone. Frames would
 *    have no choice but to be directed towards the correct front-panel port.
 *    But because we also want the RX VLAN to not break bridging, then
 *    inevitably that means that we have to give them a choice (of what
 *    front-panel port to go out on), and therefore we cannot steer traffic
 *    based on the RX VID. So what we do is simply install one more VID on the
 *    front-panel and CPU ports, and profit off of the fact that steering will
 *    work just by virtue of the fact that there is only one other port that's
 *    a member of the VID we're tagging the traffic with - the desired one.
 *
 * So at the end, each front-panel port will have one RX VID (also the PVID),
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * the RX VID of all other front-panel ports that are in the same bridge, and
 * one TX VID. Whereas the CPU port will have the RX and TX VIDs of all
 * front-panel ports, and on top of that, is also tagged-input and
 * tagged-output (VLAN trunk).
<<<<<<< HEAD
=======
 * the RX VID of all other front-panel ports, and one TX VID. Whereas the CPU
 * port will have the RX and TX VIDs of all front-panel ports, and on top of
 * that, is also tagged-input and tagged-output (VLAN trunk).
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 *
 *               CPU port                               CPU port
 * +-------------+-----+-------------+    +-------------+-----+-------------+
 * |  RX VID     |     |             |    |  TX VID     |     |             |
 * |  of swp0    |     |             |    |  of swp0    |     |             |
 * |             +-----+             |    |             +-----+             |
 * |                ^ T              |    |                | Tagged         |
 * |                |                |    |                | ingress        |
 * |    +-------+---+---+-------+    |    |    +-----------+                |
 * |    |       |       |       |    |    |    | Untagged                   |
 * |    |     U v     U v     U v    |    |    v egress                     |
 * | +-----+ +-----+ +-----+ +-----+ |    | +-----+ +-----+ +-----+ +-----+ |
 * | |     | |     | |     | |     | |    | |     | |     | |     | |     | |
 * | |PVID | |     | |     | |     | |    | |     | |     | |     | |     | |
 * +-+-----+-+-----+-+-----+-+-----+-+    +-+-----+-+-----+-+-----+-+-----+-+
 *   swp0    swp1    swp2    swp3           swp0    swp1    swp2    swp3
 */
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static bool dsa_tag_8021q_bridge_match(struct dsa_switch *ds, int port,
				       struct dsa_notifier_bridge_info *info)
{
	struct dsa_port *dp = dsa_to_port(ds, port);

	/* Don't match on self */
	if (ds->dst->index == info->tree_index &&
	    ds->index == info->sw_index &&
	    port == info->port)
		return false;

	if (dsa_port_is_user(dp))
		return dp->bridge_dev == info->br;

	return false;
}

int dsa_tag_8021q_bridge_join(struct dsa_switch *ds,
			      struct dsa_notifier_bridge_info *info)
{
	struct dsa_switch *targeted_ds;
	struct dsa_port *targeted_dp;
	u16 targeted_rx_vid;
	int err, port;

	if (!ds->tag_8021q_ctx)
		return 0;

	targeted_ds = dsa_switch_find(info->tree_index, info->sw_index);
	targeted_dp = dsa_to_port(targeted_ds, info->port);
	targeted_rx_vid = dsa_8021q_rx_vid(targeted_ds, info->port);

	for (port = 0; port < ds->num_ports; port++) {
		struct dsa_port *dp = dsa_to_port(ds, port);
		u16 rx_vid = dsa_8021q_rx_vid(ds, port);

		if (!dsa_tag_8021q_bridge_match(ds, port, info))
			continue;

		/* Install the RX VID of the targeted port in our VLAN table */
		err = dsa_port_tag_8021q_vlan_add(dp, targeted_rx_vid, true);
		if (err)
			return err;

		/* Install our RX VID into the targeted port's VLAN table */
		err = dsa_port_tag_8021q_vlan_add(targeted_dp, rx_vid, true);
		if (err)
			return err;
	}

	return 0;
}

int dsa_tag_8021q_bridge_leave(struct dsa_switch *ds,
			       struct dsa_notifier_bridge_info *info)
<<<<<<< HEAD
{
	struct dsa_switch *targeted_ds;
	struct dsa_port *targeted_dp;
	u16 targeted_rx_vid;
	int port;

	if (!ds->tag_8021q_ctx)
		return 0;

	targeted_ds = dsa_switch_find(info->tree_index, info->sw_index);
	targeted_dp = dsa_to_port(targeted_ds, info->port);
	targeted_rx_vid = dsa_8021q_rx_vid(targeted_ds, info->port);

	for (port = 0; port < ds->num_ports; port++) {
		struct dsa_port *dp = dsa_to_port(ds, port);
		u16 rx_vid = dsa_8021q_rx_vid(ds, port);

		if (!dsa_tag_8021q_bridge_match(ds, port, info))
			continue;

		/* Remove the RX VID of the targeted port from our VLAN table */
		dsa_port_tag_8021q_vlan_del(dp, targeted_rx_vid, true);

		/* Remove our RX VID from the targeted port's VLAN table */
		dsa_port_tag_8021q_vlan_del(targeted_dp, rx_vid, true);
	}

	return 0;
}

int dsa_tag_8021q_bridge_tx_fwd_offload(struct dsa_switch *ds, int port,
					struct net_device *br,
					int bridge_num)
{
	u16 tx_vid = dsa_8021q_bridge_tx_fwd_offload_vid(bridge_num);

	return dsa_port_tag_8021q_vlan_add(dsa_to_port(ds, port), tx_vid,
					   true);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_bridge_tx_fwd_offload);

void dsa_tag_8021q_bridge_tx_fwd_unoffload(struct dsa_switch *ds, int port,
					   struct net_device *br,
					   int bridge_num)
{
	u16 tx_vid = dsa_8021q_bridge_tx_fwd_offload_vid(bridge_num);

	dsa_port_tag_8021q_vlan_del(dsa_to_port(ds, port), tx_vid, true);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_bridge_tx_fwd_unoffload);

/* Set up a port's tag_8021q RX and TX VLAN for standalone mode operation */
static int dsa_tag_8021q_port_setup(struct dsa_switch *ds, int port)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	u16 rx_vid = dsa_8021q_rx_vid(ds, port);
	u16 tx_vid = dsa_8021q_tx_vid(ds, port);
	struct net_device *master;
	int err;
=======
static int dsa_8021q_setup_port(struct dsa_8021q_context *ctx, int port,
				bool enabled)
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct dsa_switch *targeted_ds;
	struct dsa_port *targeted_dp;
	u16 targeted_rx_vid;
	int port;

	if (!ds->tag_8021q_ctx)
		return 0;

	targeted_ds = dsa_switch_find(info->tree_index, info->sw_index);
	targeted_dp = dsa_to_port(targeted_ds, info->port);
	targeted_rx_vid = dsa_8021q_rx_vid(targeted_ds, info->port);

	for (port = 0; port < ds->num_ports; port++) {
		struct dsa_port *dp = dsa_to_port(ds, port);
		u16 rx_vid = dsa_8021q_rx_vid(ds, port);

		if (!dsa_tag_8021q_bridge_match(ds, port, info))
			continue;

		/* Remove the RX VID of the targeted port from our VLAN table */
		dsa_port_tag_8021q_vlan_del(dp, targeted_rx_vid, true);

		/* Remove our RX VID from the targeted port's VLAN table */
		dsa_port_tag_8021q_vlan_del(targeted_dp, rx_vid, true);
	}

	return 0;
}

int dsa_tag_8021q_bridge_tx_fwd_offload(struct dsa_switch *ds, int port,
					struct net_device *br,
					int bridge_num)
{
	u16 tx_vid = dsa_8021q_bridge_tx_fwd_offload_vid(bridge_num);

	return dsa_port_tag_8021q_vlan_add(dsa_to_port(ds, port), tx_vid,
					   true);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_bridge_tx_fwd_offload);

void dsa_tag_8021q_bridge_tx_fwd_unoffload(struct dsa_switch *ds, int port,
					   struct net_device *br,
					   int bridge_num)
{
	u16 tx_vid = dsa_8021q_bridge_tx_fwd_offload_vid(bridge_num);

	dsa_port_tag_8021q_vlan_del(dsa_to_port(ds, port), tx_vid, true);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_bridge_tx_fwd_unoffload);

/* Set up a port's tag_8021q RX and TX VLAN for standalone mode operation */
static int dsa_tag_8021q_port_setup(struct dsa_switch *ds, int port)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	u16 rx_vid = dsa_8021q_rx_vid(ds, port);
	u16 tx_vid = dsa_8021q_tx_vid(ds, port);
	struct net_device *master;
<<<<<<< HEAD
	int i, err, subvlan;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	int err;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* The CPU port is implicitly configured by
	 * configuring the front-panel ports
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	if (!dsa_port_is_user(dp))
		return 0;

	master = dp->cpu_dp->master;
=======
	if (!dsa_is_user_port(ctx->ds, port))
		return 0;

	master = dsa_to_port(ctx->ds, port)->cpu_dp->master;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!dsa_port_is_user(dp))
		return 0;

	master = dp->cpu_dp->master;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* Add this user port's RX VID to the membership list of all others
	 * (including itself). This is so that bridging will not be hindered.
	 * L2 forwarding rules still take precedence when there are no VLAN
	 * restrictions, so there are no concerns about leaking traffic.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	err = dsa_port_tag_8021q_vlan_add(dp, rx_vid, false);
	if (err) {
		dev_err(ds->dev,
			"Failed to apply RX VID %d to port %d: %pe\n",
			rx_vid, port, ERR_PTR(err));
		return err;
	}

	/* Add @rx_vid to the master's RX filter. */
	vlan_vid_add(master, ctx->proto, rx_vid);

	/* Finally apply the TX VID on this port and on the CPU port */
	err = dsa_port_tag_8021q_vlan_add(dp, tx_vid, false);
	if (err) {
		dev_err(ds->dev,
			"Failed to apply TX VID %d on port %d: %pe\n",
			tx_vid, port, ERR_PTR(err));
=======
	for (i = 0; i < ctx->ds->num_ports; i++) {
		u16 flags;

		if (i == upstream)
			continue;
		else if (i == port)
			/* The RX VID is pvid on this port */
			flags = BRIDGE_VLAN_INFO_UNTAGGED |
				BRIDGE_VLAN_INFO_PVID;
		else
			/* The RX VID is a regular VLAN on all others */
			flags = BRIDGE_VLAN_INFO_UNTAGGED;

		err = dsa_8021q_vid_apply(ctx, i, rx_vid, flags, enabled);
		if (err) {
			dev_err(ctx->ds->dev,
				"Failed to apply RX VID %d to port %d: %d\n",
				rx_vid, port, err);
			return err;
		}
	}

	/* CPU port needs to see this port's RX VID
	 * as tagged egress.
	 */
	err = dsa_8021q_vid_apply(ctx, upstream, rx_vid, 0, enabled);
=======
	err = dsa_port_tag_8021q_vlan_add(dp, rx_vid, false);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (err) {
		dev_err(ds->dev,
			"Failed to apply RX VID %d to port %d: %pe\n",
			rx_vid, port, ERR_PTR(err));
		return err;
	}

	/* Add @rx_vid to the master's RX filter. */
	vlan_vid_add(master, ctx->proto, rx_vid);

	/* Finally apply the TX VID on this port and on the CPU port */
	err = dsa_port_tag_8021q_vlan_add(dp, tx_vid, false);
	if (err) {
<<<<<<< HEAD
		dev_err(ctx->ds->dev,
			"Failed to apply TX VID %d on port %d: %d\n",
			tx_vid, upstream, err);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_err(ds->dev,
			"Failed to apply TX VID %d on port %d: %pe\n",
			tx_vid, port, ERR_PTR(err));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return err;
	}

	return err;
}

<<<<<<< HEAD
<<<<<<< HEAD
static void dsa_tag_8021q_port_teardown(struct dsa_switch *ds, int port)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	u16 rx_vid = dsa_8021q_rx_vid(ds, port);
	u16 tx_vid = dsa_8021q_tx_vid(ds, port);
	struct net_device *master;

	/* The CPU port is implicitly configured by
	 * configuring the front-panel ports
	 */
	if (!dsa_port_is_user(dp))
		return;

	master = dp->cpu_dp->master;

	dsa_port_tag_8021q_vlan_del(dp, rx_vid, false);

	vlan_vid_del(master, ctx->proto, rx_vid);

	dsa_port_tag_8021q_vlan_del(dp, tx_vid, false);
}

static int dsa_tag_8021q_setup(struct dsa_switch *ds)
{
	int err, port;

	ASSERT_RTNL();

	for (port = 0; port < ds->num_ports; port++) {
		err = dsa_tag_8021q_port_setup(ds, port);
		if (err < 0) {
			dev_err(ds->dev,
				"Failed to setup VLAN tagging for port %d: %pe\n",
				port, ERR_PTR(err));
			return err;
		}
	}

	return 0;
}

static void dsa_tag_8021q_teardown(struct dsa_switch *ds)
{
	int port;

	ASSERT_RTNL();

	for (port = 0; port < ds->num_ports; port++)
		dsa_tag_8021q_port_teardown(ds, port);
}

int dsa_tag_8021q_register(struct dsa_switch *ds, __be16 proto)
{
	struct dsa_8021q_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->proto = proto;
	ctx->ds = ds;

	INIT_LIST_HEAD(&ctx->vlans);

	ds->tag_8021q_ctx = ctx;

	return dsa_tag_8021q_setup(ds);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_register);

void dsa_tag_8021q_unregister(struct dsa_switch *ds)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_tag_8021q_vlan *v, *n;

	dsa_tag_8021q_teardown(ds);

	list_for_each_entry_safe(v, n, &ctx->vlans, list) {
		list_del(&v->list);
		kfree(v);
	}

	ds->tag_8021q_ctx = NULL;

	kfree(ctx);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_unregister);
=======
int dsa_8021q_setup(struct dsa_8021q_context *ctx, bool enabled)
=======
static void dsa_tag_8021q_port_teardown(struct dsa_switch *ds, int port)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_port *dp = dsa_to_port(ds, port);
	u16 rx_vid = dsa_8021q_rx_vid(ds, port);
	u16 tx_vid = dsa_8021q_tx_vid(ds, port);
	struct net_device *master;

	/* The CPU port is implicitly configured by
	 * configuring the front-panel ports
	 */
	if (!dsa_port_is_user(dp))
		return;

	master = dp->cpu_dp->master;

	dsa_port_tag_8021q_vlan_del(dp, rx_vid, false);

	vlan_vid_del(master, ctx->proto, rx_vid);

	dsa_port_tag_8021q_vlan_del(dp, tx_vid, false);
}

static int dsa_tag_8021q_setup(struct dsa_switch *ds)
{
	int err, port;

	ASSERT_RTNL();

	for (port = 0; port < ds->num_ports; port++) {
		err = dsa_tag_8021q_port_setup(ds, port);
		if (err < 0) {
			dev_err(ds->dev,
				"Failed to setup VLAN tagging for port %d: %pe\n",
				port, ERR_PTR(err));
			return err;
		}
	}

	return 0;
}

static void dsa_tag_8021q_teardown(struct dsa_switch *ds)
{
	int port;

	ASSERT_RTNL();

	for (port = 0; port < ds->num_ports; port++)
		dsa_tag_8021q_port_teardown(ds, port);
}

int dsa_tag_8021q_register(struct dsa_switch *ds, __be16 proto)
{
	struct dsa_8021q_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->proto = proto;
	ctx->ds = ds;

	INIT_LIST_HEAD(&ctx->vlans);

	ds->tag_8021q_ctx = ctx;

	return dsa_tag_8021q_setup(ds);
}
EXPORT_SYMBOL_GPL(dsa_tag_8021q_register);

void dsa_tag_8021q_unregister(struct dsa_switch *ds)
{
	struct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	struct dsa_tag_8021q_vlan *v, *n;

	dsa_tag_8021q_teardown(ds);

	list_for_each_entry_safe(v, n, &ctx->vlans, list) {
		list_del(&v->list);
		kfree(v);
	}

	ds->tag_8021q_ctx = NULL;

	kfree(ctx);
}
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(dsa_8021q_crosschip_bridge_leave);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(dsa_tag_8021q_unregister);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

struct sk_buff *dsa_8021q_xmit(struct sk_buff *skb, struct net_device *netdev,
			       u16 tpid, u16 tci)
{
	/* skb->data points at skb_mac_header, which
	 * is fine for vlan_insert_tag.
	 */
	return vlan_insert_tag(skb, htons(tpid), tci);
}
EXPORT_SYMBOL_GPL(dsa_8021q_xmit);

<<<<<<< HEAD
<<<<<<< HEAD
void dsa_8021q_rcv(struct sk_buff *skb, int *source_port, int *switch_id)
=======
void dsa_8021q_rcv(struct sk_buff *skb, int *source_port, int *switch_id,
		   int *subvlan)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void dsa_8021q_rcv(struct sk_buff *skb, int *source_port, int *switch_id)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	u16 vid, tci;

	skb_push_rcsum(skb, ETH_HLEN);
	if (skb_vlan_tag_present(skb)) {
		tci = skb_vlan_tag_get(skb);
		__vlan_hwaccel_clear_tag(skb);
	} else {
		__skb_vlan_pop(skb, &tci);
	}
	skb_pull_rcsum(skb, ETH_HLEN);

	vid = tci & VLAN_VID_MASK;

	*source_port = dsa_8021q_rx_source_port(vid);
	*switch_id = dsa_8021q_rx_switch_id(vid);
<<<<<<< HEAD
<<<<<<< HEAD
	skb->priority = (tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
}
EXPORT_SYMBOL_GPL(dsa_8021q_rcv);
=======
	*subvlan = dsa_8021q_rx_subvlan(vid);
	skb->priority = (tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
}
EXPORT_SYMBOL_GPL(dsa_8021q_rcv);

MODULE_LICENSE("GPL v2");
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	skb->priority = (tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
}
EXPORT_SYMBOL_GPL(dsa_8021q_rcv);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
