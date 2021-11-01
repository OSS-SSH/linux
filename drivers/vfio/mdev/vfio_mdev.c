// SPDX-License-Identifier: GPL-2.0-only
/*
 * VFIO based driver for Mediated device
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/vfio.h>
#include <linux/mdev.h>

#include "mdev_private.h"

<<<<<<< HEAD
<<<<<<< HEAD
static int vfio_mdev_open_device(struct vfio_device *core_vdev)
=======
static int vfio_mdev_open(struct vfio_device *core_vdev)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int vfio_mdev_open_device(struct vfio_device *core_vdev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

<<<<<<< HEAD
<<<<<<< HEAD
	if (unlikely(!parent->ops->open_device))
		return 0;

	return parent->ops->open_device(mdev);
}

static void vfio_mdev_close_device(struct vfio_device *core_vdev)
=======
	if (unlikely(!parent->ops->open))
		return -EINVAL;
=======
	if (unlikely(!parent->ops->open_device))
		return 0;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return parent->ops->open_device(mdev);
}

<<<<<<< HEAD
static void vfio_mdev_release(struct vfio_device *core_vdev)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static void vfio_mdev_close_device(struct vfio_device *core_vdev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

<<<<<<< HEAD
<<<<<<< HEAD
	if (likely(parent->ops->close_device))
		parent->ops->close_device(mdev);
=======
	if (likely(parent->ops->release))
		parent->ops->release(mdev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (likely(parent->ops->close_device))
		parent->ops->close_device(mdev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static long vfio_mdev_unlocked_ioctl(struct vfio_device *core_vdev,
				     unsigned int cmd, unsigned long arg)
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

	if (unlikely(!parent->ops->ioctl))
<<<<<<< HEAD
<<<<<<< HEAD
		return 0;
=======
		return -EINVAL;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		return 0;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return parent->ops->ioctl(mdev, cmd, arg);
}

static ssize_t vfio_mdev_read(struct vfio_device *core_vdev, char __user *buf,
			      size_t count, loff_t *ppos)
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

	if (unlikely(!parent->ops->read))
		return -EINVAL;

	return parent->ops->read(mdev, buf, count, ppos);
}

static ssize_t vfio_mdev_write(struct vfio_device *core_vdev,
			       const char __user *buf, size_t count,
			       loff_t *ppos)
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

	if (unlikely(!parent->ops->write))
		return -EINVAL;

	return parent->ops->write(mdev, buf, count, ppos);
}

static int vfio_mdev_mmap(struct vfio_device *core_vdev,
			  struct vm_area_struct *vma)
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

	if (unlikely(!parent->ops->mmap))
		return -EINVAL;

	return parent->ops->mmap(mdev, vma);
}

static void vfio_mdev_request(struct vfio_device *core_vdev, unsigned int count)
{
	struct mdev_device *mdev = to_mdev_device(core_vdev->dev);
	struct mdev_parent *parent = mdev->type->parent;

	if (parent->ops->request)
		parent->ops->request(mdev, count);
	else if (count == 0)
		dev_notice(mdev_dev(mdev),
			   "No mdev vendor driver request callback support, blocked until released by user\n");
}

static const struct vfio_device_ops vfio_mdev_dev_ops = {
	.name		= "vfio-mdev",
<<<<<<< HEAD
<<<<<<< HEAD
	.open_device	= vfio_mdev_open_device,
	.close_device	= vfio_mdev_close_device,
=======
	.open		= vfio_mdev_open,
	.release	= vfio_mdev_release,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	.open_device	= vfio_mdev_open_device,
	.close_device	= vfio_mdev_close_device,
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	.ioctl		= vfio_mdev_unlocked_ioctl,
	.read		= vfio_mdev_read,
	.write		= vfio_mdev_write,
	.mmap		= vfio_mdev_mmap,
	.request	= vfio_mdev_request,
};

static int vfio_mdev_probe(struct mdev_device *mdev)
{
	struct vfio_device *vdev;
	int ret;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev)
		return -ENOMEM;

	vfio_init_group_dev(vdev, &mdev->dev, &vfio_mdev_dev_ops);
	ret = vfio_register_group_dev(vdev);
<<<<<<< HEAD
<<<<<<< HEAD
	if (ret)
		goto out_uninit;

	dev_set_drvdata(&mdev->dev, vdev);
	return 0;

out_uninit:
	vfio_uninit_group_dev(vdev);
	kfree(vdev);
	return ret;
=======
	if (ret) {
		kfree(vdev);
		return ret;
	}
	dev_set_drvdata(&mdev->dev, vdev);
	return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (ret)
		goto out_uninit;

	dev_set_drvdata(&mdev->dev, vdev);
	return 0;

out_uninit:
	vfio_uninit_group_dev(vdev);
	kfree(vdev);
	return ret;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static void vfio_mdev_remove(struct mdev_device *mdev)
{
	struct vfio_device *vdev = dev_get_drvdata(&mdev->dev);

	vfio_unregister_group_dev(vdev);
<<<<<<< HEAD
<<<<<<< HEAD
	vfio_uninit_group_dev(vdev);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	vfio_uninit_group_dev(vdev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	kfree(vdev);
}

struct mdev_driver vfio_mdev_driver = {
	.driver = {
		.name = "vfio_mdev",
		.owner = THIS_MODULE,
		.mod_name = KBUILD_MODNAME,
	},
	.probe	= vfio_mdev_probe,
	.remove	= vfio_mdev_remove,
};
