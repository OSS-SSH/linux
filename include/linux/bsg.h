/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_BSG_H
#define _LINUX_BSG_H

#include <uapi/linux/bsg.h>

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

#ifdef CONFIG_BLK_DEV_BSG
struct bsg_ops {
	int	(*check_proto)(struct sg_io_v4 *hdr);
	int	(*fill_hdr)(struct request *rq, struct sg_io_v4 *hdr,
				fmode_t mode);
	int	(*complete_rq)(struct request *rq, struct sg_io_v4 *hdr);
	void	(*free_rq)(struct request *rq);
};

struct bsg_class_device {
	struct device *class_dev;
	int minor;
	struct request_queue *queue;
	const struct bsg_ops *ops;
};

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
#endif /* _LINUX_BSG_H */
