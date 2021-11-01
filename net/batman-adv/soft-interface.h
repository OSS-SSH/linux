/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#ifndef _NET_BATMAN_ADV_SOFT_INTERFACE_H_
#define _NET_BATMAN_ADV_SOFT_INTERFACE_H_

#include "main.h"

<<<<<<< HEAD
#include <linux/kref.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <net/rtnetlink.h>

int batadv_skb_head_push(struct sk_buff *skb, unsigned int len);
void batadv_interface_rx(struct net_device *soft_iface,
			 struct sk_buff *skb, int hdr_size,
			 struct batadv_orig_node *orig_node);
bool batadv_softif_is_valid(const struct net_device *net_dev);
extern struct rtnl_link_ops batadv_link_ops;
int batadv_softif_create_vlan(struct batadv_priv *bat_priv, unsigned short vid);
<<<<<<< HEAD
void batadv_softif_vlan_release(struct kref *ref);
struct batadv_softif_vlan *batadv_softif_vlan_get(struct batadv_priv *bat_priv,
						  unsigned short vid);

/**
 * batadv_softif_vlan_put() - decrease the vlan object refcounter and
 *  possibly release it
 * @vlan: the vlan object to release
 */
static inline void batadv_softif_vlan_put(struct batadv_softif_vlan *vlan)
{
	if (!vlan)
		return;

	kref_put(&vlan->refcount, batadv_softif_vlan_release);
}

=======
void batadv_softif_vlan_put(struct batadv_softif_vlan *softif_vlan);
struct batadv_softif_vlan *batadv_softif_vlan_get(struct batadv_priv *bat_priv,
						  unsigned short vid);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif /* _NET_BATMAN_ADV_SOFT_INTERFACE_H_ */
