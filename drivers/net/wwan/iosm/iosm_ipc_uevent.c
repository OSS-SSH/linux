// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2020-21 Intel Corporation.
 */

#include <linux/device.h>
#include <linux/kobject.h>
#include <linux/slab.h>

#include "iosm_ipc_uevent.h"

/* Update the uevent in work queue context */
static void ipc_uevent_work(struct work_struct *data)
{
	struct ipc_uevent_info *info;
	char *envp[2] = { NULL, NULL };

	info = container_of(data, struct ipc_uevent_info, work);

	envp[0] = info->uevent;

	if (kobject_uevent_env(&info->dev->kobj, KOBJ_CHANGE, envp))
		pr_err("uevent %s failed to sent", info->uevent);

	kfree(info);
}

void ipc_uevent_send(struct device *dev, char *uevent)
{
	struct ipc_uevent_info *info = kzalloc(sizeof(*info), GFP_ATOMIC);

	if (!info)
		return;

	/* Initialize the kernel work queue */
	INIT_WORK(&info->work, ipc_uevent_work);

	/* Store the device and event information */
	info->dev = dev;
<<<<<<< HEAD
<<<<<<< HEAD
	snprintf(info->uevent, MAX_UEVENT_LEN, "IOSM_EVENT=%s", uevent);
=======
	snprintf(info->uevent, MAX_UEVENT_LEN, "%s: %s", dev_name(dev), uevent);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	snprintf(info->uevent, MAX_UEVENT_LEN, "IOSM_EVENT=%s", uevent);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* Schedule uevent in process context using work queue */
	schedule_work(&info->work);
}
