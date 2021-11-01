/* SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved. */

#ifndef _PRESTERA_SWITCHDEV_H_
#define _PRESTERA_SWITCHDEV_H_

int prestera_switchdev_init(struct prestera_switch *sw);
void prestera_switchdev_fini(struct prestera_switch *sw);

int prestera_bridge_port_join(struct net_device *br_dev,
<<<<<<< HEAD
			      struct prestera_port *port,
			      struct netlink_ext_ack *extack);
=======
			      struct prestera_port *port);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

void prestera_bridge_port_leave(struct net_device *br_dev,
				struct prestera_port *port);

#endif /* _PRESTERA_SWITCHDEV_H_ */
