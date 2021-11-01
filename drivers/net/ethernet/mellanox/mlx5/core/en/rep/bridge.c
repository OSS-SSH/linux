// SPDX-License-Identifier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021 Mellanox Technologies. */

#include <linux/netdevice.h>
#include <linux/if_bridge.h>
#include <net/netevent.h>
#include <net/switchdev.h>
#include "bridge.h"
#include "esw/bridge.h"
#include "en_rep.h"

#define MLX5_ESW_BRIDGE_UPDATE_INTERVAL 1000

struct mlx5_bridge_switchdev_fdb_work {
	struct work_struct work;
	struct switchdev_notifier_fdb_info fdb_info;
	struct net_device *dev;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mlx5_esw_bridge_offloads *br_offloads;
	bool add;
};

static bool mlx5_esw_bridge_dev_same_esw(struct net_device *dev, struct mlx5_eswitch *esw)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	return esw == priv->mdev->priv.eswitch;
}

static bool mlx5_esw_bridge_dev_same_hw(struct net_device *dev, struct mlx5_eswitch *esw)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5_core_dev *mdev, *esw_mdev;
	u64 system_guid, esw_system_guid;

	mdev = priv->mdev;
	esw_mdev = esw->dev;

	system_guid = mlx5_query_nic_system_image_guid(mdev);
	esw_system_guid = mlx5_query_nic_system_image_guid(esw_mdev);

	return system_guid == esw_system_guid;
}

static struct net_device *
mlx5_esw_bridge_lag_rep_get(struct net_device *dev, struct mlx5_eswitch *esw)
{
	struct net_device *lower;
	struct list_head *iter;

	netdev_for_each_lower_dev(dev, lower, iter) {
		struct mlx5_core_dev *mdev;
		struct mlx5e_priv *priv;

		if (!mlx5e_eswitch_rep(lower))
			continue;

		priv = netdev_priv(lower);
		mdev = priv->mdev;
		if (mlx5_lag_is_shared_fdb(mdev) && mlx5_esw_bridge_dev_same_esw(lower, esw))
			return lower;
	}

	return NULL;
}

static struct net_device *
mlx5_esw_bridge_rep_vport_num_vhca_id_get(struct net_device *dev, struct mlx5_eswitch *esw,
					  u16 *vport_num, u16 *esw_owner_vhca_id)
{
	struct mlx5e_rep_priv *rpriv;
	struct mlx5e_priv *priv;

	if (netif_is_lag_master(dev))
		dev = mlx5_esw_bridge_lag_rep_get(dev, esw);

	if (!dev || !mlx5e_eswitch_rep(dev) || !mlx5_esw_bridge_dev_same_hw(dev, esw))
		return NULL;

	priv = netdev_priv(dev);
	rpriv = priv->ppriv;
	*vport_num = rpriv->rep->vport;
	*esw_owner_vhca_id = MLX5_CAP_GEN(priv->mdev, vhca_id);
	return dev;
}

static struct net_device *
mlx5_esw_bridge_lower_rep_vport_num_vhca_id_get(struct net_device *dev, struct mlx5_eswitch *esw,
						u16 *vport_num, u16 *esw_owner_vhca_id)
{
	struct net_device *lower_dev;
	struct list_head *iter;

	if (netif_is_lag_master(dev) || mlx5e_eswitch_rep(dev))
		return mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, esw, vport_num,
								 esw_owner_vhca_id);

	netdev_for_each_lower_dev(dev, lower_dev, iter) {
		struct net_device *rep;

		if (netif_is_bridge_master(lower_dev))
			continue;

		rep = mlx5_esw_bridge_lower_rep_vport_num_vhca_id_get(lower_dev, esw, vport_num,
								      esw_owner_vhca_id);
		if (rep)
			return rep;
	}

	return NULL;
}

static bool mlx5_esw_bridge_is_local(struct net_device *dev, struct net_device *rep,
				     struct mlx5_eswitch *esw)
{
	struct mlx5_core_dev *mdev;
	struct mlx5e_priv *priv;

	if (!mlx5_esw_bridge_dev_same_esw(rep, esw))
		return false;

	priv = netdev_priv(rep);
	mdev = priv->mdev;
	if (netif_is_lag_master(dev))
		return mlx5_lag_is_shared_fdb(mdev) && mlx5_lag_is_master(mdev);
	return true;
}

=======
	bool add;
};

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct mlx5_esw_bridge_offloads *br_offloads;
	bool add;
};

static bool mlx5_esw_bridge_dev_same_esw(struct net_device *dev, struct mlx5_eswitch *esw)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	return esw == priv->mdev->priv.eswitch;
}

static bool mlx5_esw_bridge_dev_same_hw(struct net_device *dev, struct mlx5_eswitch *esw)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5_core_dev *mdev, *esw_mdev;
	u64 system_guid, esw_system_guid;

	mdev = priv->mdev;
	esw_mdev = esw->dev;

	system_guid = mlx5_query_nic_system_image_guid(mdev);
	esw_system_guid = mlx5_query_nic_system_image_guid(esw_mdev);

	return system_guid == esw_system_guid;
}

static struct net_device *
mlx5_esw_bridge_lag_rep_get(struct net_device *dev, struct mlx5_eswitch *esw)
{
	struct net_device *lower;
	struct list_head *iter;

	netdev_for_each_lower_dev(dev, lower, iter) {
		struct mlx5_core_dev *mdev;
		struct mlx5e_priv *priv;

		if (!mlx5e_eswitch_rep(lower))
			continue;

		priv = netdev_priv(lower);
		mdev = priv->mdev;
		if (mlx5_lag_is_shared_fdb(mdev) && mlx5_esw_bridge_dev_same_esw(lower, esw))
			return lower;
	}

	return NULL;
}

static struct net_device *
mlx5_esw_bridge_rep_vport_num_vhca_id_get(struct net_device *dev, struct mlx5_eswitch *esw,
					  u16 *vport_num, u16 *esw_owner_vhca_id)
{
	struct mlx5e_rep_priv *rpriv;
	struct mlx5e_priv *priv;

	if (netif_is_lag_master(dev))
		dev = mlx5_esw_bridge_lag_rep_get(dev, esw);

	if (!dev || !mlx5e_eswitch_rep(dev) || !mlx5_esw_bridge_dev_same_hw(dev, esw))
		return NULL;

	priv = netdev_priv(dev);
	rpriv = priv->ppriv;
	*vport_num = rpriv->rep->vport;
	*esw_owner_vhca_id = MLX5_CAP_GEN(priv->mdev, vhca_id);
	return dev;
}

static struct net_device *
mlx5_esw_bridge_lower_rep_vport_num_vhca_id_get(struct net_device *dev, struct mlx5_eswitch *esw,
						u16 *vport_num, u16 *esw_owner_vhca_id)
{
	struct net_device *lower_dev;
	struct list_head *iter;

	if (netif_is_lag_master(dev) || mlx5e_eswitch_rep(dev))
		return mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, esw, vport_num,
								 esw_owner_vhca_id);

	netdev_for_each_lower_dev(dev, lower_dev, iter) {
		struct net_device *rep;

		if (netif_is_bridge_master(lower_dev))
			continue;

		rep = mlx5_esw_bridge_lower_rep_vport_num_vhca_id_get(lower_dev, esw, vport_num,
								      esw_owner_vhca_id);
		if (rep)
			return rep;
	}

	return NULL;
}

static bool mlx5_esw_bridge_is_local(struct net_device *dev, struct net_device *rep,
				     struct mlx5_eswitch *esw)
{
	struct mlx5_core_dev *mdev;
	struct mlx5e_priv *priv;

	if (!mlx5_esw_bridge_dev_same_esw(rep, esw))
		return false;

	priv = netdev_priv(rep);
	mdev = priv->mdev;
	if (netif_is_lag_master(dev))
		return mlx5_lag_is_shared_fdb(mdev) && mlx5_lag_is_master(mdev);
	return true;
}

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int mlx5_esw_bridge_port_changeupper(struct notifier_block *nb, void *ptr)
{
	struct mlx5_esw_bridge_offloads *br_offloads = container_of(nb,
								    struct mlx5_esw_bridge_offloads,
								    netdev_nb);
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct netdev_notifier_changeupper_info *info = ptr;
<<<<<<< HEAD
<<<<<<< HEAD
	struct net_device *upper = info->upper_dev, *rep;
	struct mlx5_eswitch *esw = br_offloads->esw;
	u16 vport_num, esw_owner_vhca_id;
	struct netlink_ext_ack *extack;
	int ifindex = upper->ifindex;
	int err = 0;

	if (!netif_is_bridge_master(upper))
		return 0;

	rep = mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, esw, &vport_num, &esw_owner_vhca_id);
	if (!rep)
		return 0;

	extack = netdev_notifier_info_to_extack(&info->info);

	if (mlx5_esw_bridge_is_local(dev, rep, esw))
		err = info->linking ?
			mlx5_esw_bridge_vport_link(ifindex, vport_num, esw_owner_vhca_id,
						   br_offloads, extack) :
			mlx5_esw_bridge_vport_unlink(ifindex, vport_num, esw_owner_vhca_id,
						     br_offloads, extack);
	else if (mlx5_esw_bridge_dev_same_hw(rep, esw))
		err = info->linking ?
			mlx5_esw_bridge_vport_peer_link(ifindex, vport_num, esw_owner_vhca_id,
							br_offloads, extack) :
			mlx5_esw_bridge_vport_peer_unlink(ifindex, vport_num, esw_owner_vhca_id,
							  br_offloads, extack);

	return err;
=======
=======
	struct net_device *upper = info->upper_dev, *rep;
	struct mlx5_eswitch *esw = br_offloads->esw;
	u16 vport_num, esw_owner_vhca_id;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct netlink_ext_ack *extack;
	int ifindex = upper->ifindex;
	int err = 0;

	if (!netif_is_bridge_master(upper))
		return 0;

	rep = mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, esw, &vport_num, &esw_owner_vhca_id);
	if (!rep)
		return 0;

	extack = netdev_notifier_info_to_extack(&info->info);

<<<<<<< HEAD
	return info->linking ?
		mlx5_esw_bridge_vport_link(upper->ifindex, br_offloads, vport, extack) :
		mlx5_esw_bridge_vport_unlink(upper->ifindex, br_offloads, vport, extack);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (mlx5_esw_bridge_is_local(dev, rep, esw))
		err = info->linking ?
			mlx5_esw_bridge_vport_link(ifindex, vport_num, esw_owner_vhca_id,
						   br_offloads, extack) :
			mlx5_esw_bridge_vport_unlink(ifindex, vport_num, esw_owner_vhca_id,
						     br_offloads, extack);
	else if (mlx5_esw_bridge_dev_same_hw(rep, esw))
		err = info->linking ?
			mlx5_esw_bridge_vport_peer_link(ifindex, vport_num, esw_owner_vhca_id,
							br_offloads, extack) :
			mlx5_esw_bridge_vport_peer_unlink(ifindex, vport_num, esw_owner_vhca_id,
							  br_offloads, extack);

	return err;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static int mlx5_esw_bridge_switchdev_port_event(struct notifier_block *nb,
						unsigned long event, void *ptr)
{
	int err = 0;

	switch (event) {
	case NETDEV_PRECHANGEUPPER:
		break;

	case NETDEV_CHANGEUPPER:
		err = mlx5_esw_bridge_port_changeupper(nb, ptr);
		break;
	}

	return notifier_from_errno(err);
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int
mlx5_esw_bridge_port_obj_add(struct net_device *dev,
			     struct switchdev_notifier_port_obj_info *port_obj_info,
			     struct mlx5_esw_bridge_offloads *br_offloads)
<<<<<<< HEAD
{
	struct netlink_ext_ack *extack = switchdev_notifier_info_to_extack(&port_obj_info->info);
	const struct switchdev_obj *obj = port_obj_info->obj;
	const struct switchdev_obj_port_vlan *vlan;
	u16 vport_num, esw_owner_vhca_id;
	int err;

	if (!mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
						       &esw_owner_vhca_id))
		return 0;

	port_obj_info->handled = true;
=======
static int mlx5_esw_bridge_port_obj_add(struct net_device *dev,
					const void *ctx,
					const struct switchdev_obj *obj,
					struct netlink_ext_ack *extack)
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct netlink_ext_ack *extack = switchdev_notifier_info_to_extack(&port_obj_info->info);
	const struct switchdev_obj *obj = port_obj_info->obj;
	const struct switchdev_obj_port_vlan *vlan;
	u16 vport_num, esw_owner_vhca_id;
	int err;

<<<<<<< HEAD
	priv = netdev_priv(dev);
	rpriv = priv->ppriv;
	vport_num = rpriv->rep->vport;
	esw = priv->mdev->priv.eswitch;
	vport = mlx5_eswitch_get_vport(esw, vport_num);
	if (IS_ERR(vport))
		return PTR_ERR(vport);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
						       &esw_owner_vhca_id))
		return 0;

	port_obj_info->handled = true;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
<<<<<<< HEAD
<<<<<<< HEAD
		err = mlx5_esw_bridge_port_vlan_add(vport_num, esw_owner_vhca_id, vlan->vid,
						    vlan->flags, br_offloads, extack);
=======
		err = mlx5_esw_bridge_port_vlan_add(vlan->vid, vlan->flags, esw, vport, extack);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		err = mlx5_esw_bridge_port_vlan_add(vport_num, esw_owner_vhca_id, vlan->vid,
						    vlan->flags, br_offloads, extack);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	default:
		return -EOPNOTSUPP;
	}
	return err;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int
mlx5_esw_bridge_port_obj_del(struct net_device *dev,
			     struct switchdev_notifier_port_obj_info *port_obj_info,
			     struct mlx5_esw_bridge_offloads *br_offloads)
<<<<<<< HEAD
{
	const struct switchdev_obj *obj = port_obj_info->obj;
	const struct switchdev_obj_port_vlan *vlan;
	u16 vport_num, esw_owner_vhca_id;

	if (!mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
						       &esw_owner_vhca_id))
		return 0;

	port_obj_info->handled = true;
=======
static int mlx5_esw_bridge_port_obj_del(struct net_device *dev,
					const void *ctx,
					const struct switchdev_obj *obj)
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	const struct switchdev_obj *obj = port_obj_info->obj;
	const struct switchdev_obj_port_vlan *vlan;
	u16 vport_num, esw_owner_vhca_id;

<<<<<<< HEAD
	priv = netdev_priv(dev);
	rpriv = priv->ppriv;
	vport_num = rpriv->rep->vport;
	esw = priv->mdev->priv.eswitch;
	vport = mlx5_eswitch_get_vport(esw, vport_num);
	if (IS_ERR(vport))
		return PTR_ERR(vport);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
						       &esw_owner_vhca_id))
		return 0;

	port_obj_info->handled = true;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
<<<<<<< HEAD
<<<<<<< HEAD
		mlx5_esw_bridge_port_vlan_del(vport_num, esw_owner_vhca_id, vlan->vid, br_offloads);
=======
		mlx5_esw_bridge_port_vlan_del(vlan->vid, esw, vport);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		mlx5_esw_bridge_port_vlan_del(vport_num, esw_owner_vhca_id, vlan->vid, br_offloads);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int
mlx5_esw_bridge_port_obj_attr_set(struct net_device *dev,
				  struct switchdev_notifier_port_attr_info *port_attr_info,
				  struct mlx5_esw_bridge_offloads *br_offloads)
<<<<<<< HEAD
{
	struct netlink_ext_ack *extack = switchdev_notifier_info_to_extack(&port_attr_info->info);
	const struct switchdev_attr *attr = port_attr_info->attr;
	u16 vport_num, esw_owner_vhca_id;
	int err = 0;

	if (!mlx5_esw_bridge_lower_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
							     &esw_owner_vhca_id))
		return 0;

	port_attr_info->handled = true;
=======
static int mlx5_esw_bridge_port_obj_attr_set(struct net_device *dev,
					     const void *ctx,
					     const struct switchdev_attr *attr,
					     struct netlink_ext_ack *extack)
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct netlink_ext_ack *extack = switchdev_notifier_info_to_extack(&port_attr_info->info);
	const struct switchdev_attr *attr = port_attr_info->attr;
	u16 vport_num, esw_owner_vhca_id;
	int err = 0;

<<<<<<< HEAD
	priv = netdev_priv(dev);
	rpriv = priv->ppriv;
	vport_num = rpriv->rep->vport;
	esw = priv->mdev->priv.eswitch;
	vport = mlx5_eswitch_get_vport(esw, vport_num);
	if (IS_ERR(vport))
		return PTR_ERR(vport);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (!mlx5_esw_bridge_lower_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
							     &esw_owner_vhca_id))
		return 0;

	port_attr_info->handled = true;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		if (attr->u.brport_flags.mask & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD)) {
			NL_SET_ERR_MSG_MOD(extack, "Flag is not supported");
			err = -EINVAL;
		}
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
<<<<<<< HEAD
<<<<<<< HEAD
		err = mlx5_esw_bridge_ageing_time_set(vport_num, esw_owner_vhca_id,
						      attr->u.ageing_time, br_offloads);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		err = mlx5_esw_bridge_vlan_filtering_set(vport_num, esw_owner_vhca_id,
							 attr->u.vlan_filtering, br_offloads);
=======
		err = mlx5_esw_bridge_ageing_time_set(attr->u.ageing_time, esw, vport);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		err = mlx5_esw_bridge_vlan_filtering_set(attr->u.vlan_filtering, esw, vport);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		err = mlx5_esw_bridge_ageing_time_set(vport_num, esw_owner_vhca_id,
						      attr->u.ageing_time, br_offloads);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		err = mlx5_esw_bridge_vlan_filtering_set(vport_num, esw_owner_vhca_id,
							 attr->u.vlan_filtering, br_offloads);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	default:
		err = -EOPNOTSUPP;
	}

	return err;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int mlx5_esw_bridge_event_blocking(struct notifier_block *nb,
					  unsigned long event, void *ptr)
{
	struct mlx5_esw_bridge_offloads *br_offloads = container_of(nb,
								    struct mlx5_esw_bridge_offloads,
								    nb_blk);
=======
static int mlx5_esw_bridge_event_blocking(struct notifier_block *unused,
					  unsigned long event, void *ptr)
{
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int mlx5_esw_bridge_event_blocking(struct notifier_block *nb,
					  unsigned long event, void *ptr)
{
	struct mlx5_esw_bridge_offloads *br_offloads = container_of(nb,
								    struct mlx5_esw_bridge_offloads,
								    nb_blk);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
	int err;

	switch (event) {
	case SWITCHDEV_PORT_OBJ_ADD:
<<<<<<< HEAD
<<<<<<< HEAD
		err = mlx5_esw_bridge_port_obj_add(dev, ptr, br_offloads);
		break;
	case SWITCHDEV_PORT_OBJ_DEL:
		err = mlx5_esw_bridge_port_obj_del(dev, ptr, br_offloads);
		break;
	case SWITCHDEV_PORT_ATTR_SET:
		err = mlx5_esw_bridge_port_obj_attr_set(dev, ptr, br_offloads);
=======
		err = switchdev_handle_port_obj_add(dev, ptr,
						    mlx5e_eswitch_rep,
						    mlx5_esw_bridge_port_obj_add);
=======
		err = mlx5_esw_bridge_port_obj_add(dev, ptr, br_offloads);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	case SWITCHDEV_PORT_OBJ_DEL:
		err = mlx5_esw_bridge_port_obj_del(dev, ptr, br_offloads);
		break;
	case SWITCHDEV_PORT_ATTR_SET:
<<<<<<< HEAD
		err = switchdev_handle_port_attr_set(dev, ptr,
						     mlx5e_eswitch_rep,
						     mlx5_esw_bridge_port_obj_attr_set);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		err = mlx5_esw_bridge_port_obj_attr_set(dev, ptr, br_offloads);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	default:
		err = 0;
	}

	return notifier_from_errno(err);
}

static void
mlx5_esw_bridge_cleanup_switchdev_fdb_work(struct mlx5_bridge_switchdev_fdb_work *fdb_work)
{
	dev_put(fdb_work->dev);
	kfree(fdb_work->fdb_info.addr);
	kfree(fdb_work);
}

static void mlx5_esw_bridge_switchdev_fdb_event_work(struct work_struct *work)
{
	struct mlx5_bridge_switchdev_fdb_work *fdb_work =
		container_of(work, struct mlx5_bridge_switchdev_fdb_work, work);
	struct switchdev_notifier_fdb_info *fdb_info =
		&fdb_work->fdb_info;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mlx5_esw_bridge_offloads *br_offloads =
		fdb_work->br_offloads;
	struct net_device *dev = fdb_work->dev;
	u16 vport_num, esw_owner_vhca_id;

	rtnl_lock();

	if (!mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
						       &esw_owner_vhca_id))
		goto out;

	if (fdb_work->add)
		mlx5_esw_bridge_fdb_create(dev, vport_num, esw_owner_vhca_id, br_offloads,
					   fdb_info);
	else
		mlx5_esw_bridge_fdb_remove(dev, vport_num, esw_owner_vhca_id, br_offloads,
					   fdb_info);
=======
=======
	struct mlx5_esw_bridge_offloads *br_offloads =
		fdb_work->br_offloads;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct net_device *dev = fdb_work->dev;
	u16 vport_num, esw_owner_vhca_id;

	rtnl_lock();

	if (!mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, br_offloads->esw, &vport_num,
						       &esw_owner_vhca_id))
		goto out;

	if (fdb_work->add)
		mlx5_esw_bridge_fdb_create(dev, vport_num, esw_owner_vhca_id, br_offloads,
					   fdb_info);
	else
<<<<<<< HEAD
		mlx5_esw_bridge_fdb_remove(dev, esw, vport, fdb_info);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		mlx5_esw_bridge_fdb_remove(dev, vport_num, esw_owner_vhca_id, br_offloads,
					   fdb_info);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

out:
	rtnl_unlock();
	mlx5_esw_bridge_cleanup_switchdev_fdb_work(fdb_work);
}

static struct mlx5_bridge_switchdev_fdb_work *
mlx5_esw_bridge_init_switchdev_fdb_work(struct net_device *dev, bool add,
<<<<<<< HEAD
<<<<<<< HEAD
					struct switchdev_notifier_fdb_info *fdb_info,
					struct mlx5_esw_bridge_offloads *br_offloads)
=======
					struct switchdev_notifier_fdb_info *fdb_info)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
					struct switchdev_notifier_fdb_info *fdb_info,
					struct mlx5_esw_bridge_offloads *br_offloads)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct mlx5_bridge_switchdev_fdb_work *work;
	u8 *addr;

	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work)
		return ERR_PTR(-ENOMEM);

	INIT_WORK(&work->work, mlx5_esw_bridge_switchdev_fdb_event_work);
	memcpy(&work->fdb_info, fdb_info, sizeof(work->fdb_info));

	addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
	if (!addr) {
		kfree(work);
		return ERR_PTR(-ENOMEM);
	}
	ether_addr_copy(addr, fdb_info->addr);
	work->fdb_info.addr = addr;

	dev_hold(dev);
	work->dev = dev;
<<<<<<< HEAD
<<<<<<< HEAD
	work->br_offloads = br_offloads;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	work->br_offloads = br_offloads;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	work->add = add;
	return work;
}

static int mlx5_esw_bridge_switchdev_event(struct notifier_block *nb,
					   unsigned long event, void *ptr)
{
	struct mlx5_esw_bridge_offloads *br_offloads = container_of(nb,
								    struct mlx5_esw_bridge_offloads,
								    nb);
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
	struct switchdev_notifier_fdb_info *fdb_info;
	struct mlx5_bridge_switchdev_fdb_work *work;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mlx5_eswitch *esw = br_offloads->esw;
	struct switchdev_notifier_info *info = ptr;
	u16 vport_num, esw_owner_vhca_id;
	struct net_device *upper, *rep;

	if (event == SWITCHDEV_PORT_ATTR_SET) {
		int err = mlx5_esw_bridge_port_obj_attr_set(dev, ptr, br_offloads);

=======
=======
	struct mlx5_eswitch *esw = br_offloads->esw;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct switchdev_notifier_info *info = ptr;
	u16 vport_num, esw_owner_vhca_id;
	struct net_device *upper, *rep;

	if (event == SWITCHDEV_PORT_ATTR_SET) {
<<<<<<< HEAD
		int err = switchdev_handle_port_attr_set(dev, ptr,
							 mlx5e_eswitch_rep,
							 mlx5_esw_bridge_port_obj_attr_set);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		int err = mlx5_esw_bridge_port_obj_attr_set(dev, ptr, br_offloads);

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return notifier_from_errno(err);
	}

	upper = netdev_master_upper_dev_get_rcu(dev);
	if (!upper)
		return NOTIFY_DONE;
	if (!netif_is_bridge_master(upper))
		return NOTIFY_DONE;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	rep = mlx5_esw_bridge_rep_vport_num_vhca_id_get(dev, esw, &vport_num, &esw_owner_vhca_id);
	if (!rep)
		return NOTIFY_DONE;

<<<<<<< HEAD
	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_BRIDGE:
		/* only handle the event on native eswtich of representor */
		if (!mlx5_esw_bridge_is_local(dev, rep, esw))
			break;

		fdb_info = container_of(info,
					struct switchdev_notifier_fdb_info,
					info);
		mlx5_esw_bridge_fdb_update_used(dev, vport_num, esw_owner_vhca_id, br_offloads,
						fdb_info);
		break;
	case SWITCHDEV_FDB_DEL_TO_BRIDGE:
		/* only handle the event on peers */
		if (mlx5_esw_bridge_is_local(dev, rep, esw))
			break;
		fallthrough;
=======
	switch (event) {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_BRIDGE:
		/* only handle the event on native eswtich of representor */
		if (!mlx5_esw_bridge_is_local(dev, rep, esw))
			break;

		fdb_info = container_of(info,
					struct switchdev_notifier_fdb_info,
					info);
		mlx5_esw_bridge_fdb_update_used(dev, vport_num, esw_owner_vhca_id, br_offloads,
						fdb_info);
		break;
	case SWITCHDEV_FDB_DEL_TO_BRIDGE:
		/* only handle the event on peers */
		if (mlx5_esw_bridge_is_local(dev, rep, esw))
			break;
		fallthrough;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	case SWITCHDEV_FDB_ADD_TO_DEVICE:
	case SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb_info = container_of(info,
					struct switchdev_notifier_fdb_info,
					info);

		work = mlx5_esw_bridge_init_switchdev_fdb_work(dev,
							       event == SWITCHDEV_FDB_ADD_TO_DEVICE,
<<<<<<< HEAD
<<<<<<< HEAD
							       fdb_info,
							       br_offloads);
=======
							       fdb_info);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
							       fdb_info,
							       br_offloads);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (IS_ERR(work)) {
			WARN_ONCE(1, "Failed to init switchdev work, err=%ld",
				  PTR_ERR(work));
			return notifier_from_errno(PTR_ERR(work));
		}

		queue_work(br_offloads->wq, &work->work);
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}

static void mlx5_esw_bridge_update_work(struct work_struct *work)
{
	struct mlx5_esw_bridge_offloads *br_offloads = container_of(work,
								    struct mlx5_esw_bridge_offloads,
								    update_work.work);

	rtnl_lock();
	mlx5_esw_bridge_update(br_offloads);
	rtnl_unlock();

	queue_delayed_work(br_offloads->wq, &br_offloads->update_work,
			   msecs_to_jiffies(MLX5_ESW_BRIDGE_UPDATE_INTERVAL));
}

void mlx5e_rep_bridge_init(struct mlx5e_priv *priv)
{
	struct mlx5_esw_bridge_offloads *br_offloads;
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5_eswitch *esw =
		mdev->priv.eswitch;
	int err;

	rtnl_lock();
	br_offloads = mlx5_esw_bridge_init(esw);
	rtnl_unlock();
	if (IS_ERR(br_offloads)) {
		esw_warn(mdev, "Failed to init esw bridge (err=%ld)\n", PTR_ERR(br_offloads));
		return;
	}

	br_offloads->wq = alloc_ordered_workqueue("mlx5_bridge_wq", 0);
	if (!br_offloads->wq) {
		esw_warn(mdev, "Failed to allocate bridge offloads workqueue\n");
		goto err_alloc_wq;
	}
<<<<<<< HEAD
<<<<<<< HEAD
=======
	INIT_DELAYED_WORK(&br_offloads->update_work, mlx5_esw_bridge_update_work);
	queue_delayed_work(br_offloads->wq, &br_offloads->update_work,
			   msecs_to_jiffies(MLX5_ESW_BRIDGE_UPDATE_INTERVAL));
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	br_offloads->nb.notifier_call = mlx5_esw_bridge_switchdev_event;
	err = register_switchdev_notifier(&br_offloads->nb);
	if (err) {
		esw_warn(mdev, "Failed to register switchdev notifier (err=%d)\n", err);
		goto err_register_swdev;
	}

	br_offloads->nb_blk.notifier_call = mlx5_esw_bridge_event_blocking;
	err = register_switchdev_blocking_notifier(&br_offloads->nb_blk);
	if (err) {
		esw_warn(mdev, "Failed to register blocking switchdev notifier (err=%d)\n", err);
		goto err_register_swdev_blk;
	}

	br_offloads->netdev_nb.notifier_call = mlx5_esw_bridge_switchdev_port_event;
	err = register_netdevice_notifier(&br_offloads->netdev_nb);
	if (err) {
		esw_warn(mdev, "Failed to register bridge offloads netdevice notifier (err=%d)\n",
			 err);
		goto err_register_netdev;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	INIT_DELAYED_WORK(&br_offloads->update_work, mlx5_esw_bridge_update_work);
	queue_delayed_work(br_offloads->wq, &br_offloads->update_work,
			   msecs_to_jiffies(MLX5_ESW_BRIDGE_UPDATE_INTERVAL));
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	INIT_DELAYED_WORK(&br_offloads->update_work, mlx5_esw_bridge_update_work);
	queue_delayed_work(br_offloads->wq, &br_offloads->update_work,
			   msecs_to_jiffies(MLX5_ESW_BRIDGE_UPDATE_INTERVAL));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	return;

err_register_netdev:
	unregister_switchdev_blocking_notifier(&br_offloads->nb_blk);
err_register_swdev_blk:
	unregister_switchdev_notifier(&br_offloads->nb);
err_register_swdev:
	destroy_workqueue(br_offloads->wq);
err_alloc_wq:
	mlx5_esw_bridge_cleanup(esw);
}

void mlx5e_rep_bridge_cleanup(struct mlx5e_priv *priv)
{
	struct mlx5_esw_bridge_offloads *br_offloads;
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5_eswitch *esw =
		mdev->priv.eswitch;

	br_offloads = esw->br_offloads;
	if (!br_offloads)
		return;

<<<<<<< HEAD
<<<<<<< HEAD
	cancel_delayed_work_sync(&br_offloads->update_work);
	unregister_netdevice_notifier(&br_offloads->netdev_nb);
	unregister_switchdev_blocking_notifier(&br_offloads->nb_blk);
	unregister_switchdev_notifier(&br_offloads->nb);
=======
	unregister_netdevice_notifier(&br_offloads->netdev_nb);
	unregister_switchdev_blocking_notifier(&br_offloads->nb_blk);
	unregister_switchdev_notifier(&br_offloads->nb);
	cancel_delayed_work(&br_offloads->update_work);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	cancel_delayed_work_sync(&br_offloads->update_work);
	unregister_netdevice_notifier(&br_offloads->netdev_nb);
	unregister_switchdev_blocking_notifier(&br_offloads->nb_blk);
	unregister_switchdev_notifier(&br_offloads->nb);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	destroy_workqueue(br_offloads->wq);
	rtnl_lock();
	mlx5_esw_bridge_cleanup(esw);
	rtnl_unlock();
}
