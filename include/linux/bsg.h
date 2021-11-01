/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_BSG_H
#define _LINUX_BSG_H

#include <uapi/linux/bsg.h>

<<<<<<< HEAD
<<<<<<< HEAD
struct bsg_device;
struct device;
struct request_queue;

typedef int (bsg_sg_io_fn)(struct request_queue *, struct sg_io_v4 *hdr,
		fmode_t mode, unsigned int timeout);

struct bsg_device *bsg_register_queue(struct request_queue *q,
		struct device *parent, const char *name,
		bsg_sg_io_fn *sg_io_fn);
void bsg_unregister_queue(struct bsg_device *bcd);

=======
struct request;
=======
struct bsg_device;
struct device;
struct request_queue;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

typedef int (bsg_sg_io_fn)(struct request_queue *, struct sg_io_v4 *hdr,
		fmode_t mode, unsigned int timeout);

struct bsg_device *bsg_register_queue(struct request_queue *q,
		struct device *parent, const char *name,
		bsg_sg_io_fn *sg_io_fn);
void bsg_unregister_queue(struct bsg_device *bcd);

<<<<<<< HEAD
int bsg_register_queue(struct request_queue *q, struct device *parent,
		const char *name, const struct bsg_ops *ops);
int bsg_scsi_register_queue(struct request_queue *q, struct device *parent);
void bsg_unregister_queue(struct request_queue *q);
#else
static inline int bsg_scsi_register_queue(struct request_queue *q,
		struct device *parent)
{
	return 0;
}
static inline void bsg_unregister_queue(struct request_queue *q)
{
}
#endif /* CONFIG_BLK_DEV_BSG */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif /* _LINUX_BSG_H */
