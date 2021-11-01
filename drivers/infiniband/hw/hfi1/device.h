<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 */

#ifndef _HFI1_DEVICE_H
#define _HFI1_DEVICE_H

=======
#ifndef _HFI1_DEVICE_H
#define _HFI1_DEVICE_H
=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef _HFI1_DEVICE_H
#define _HFI1_DEVICE_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int hfi1_cdev_init(int minor, const char *name,
		   const struct file_operations *fops,
		   struct cdev *cdev, struct device **devp,
		   bool user_accessible,
		   struct kobject *parent);
void hfi1_cdev_cleanup(struct cdev *cdev, struct device **devp);
const char *class_name(void);
int __init dev_init(void);
void dev_cleanup(void);

#endif                          /* _HFI1_DEVICE_H */
