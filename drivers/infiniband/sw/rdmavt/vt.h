<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2016 Intel Corporation.
 */

#ifndef DEF_RDMAVT_H
#define DEF_RDMAVT_H

=======
#ifndef DEF_RDMAVT_H
#define DEF_RDMAVT_H

=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2016 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef DEF_RDMAVT_H
#define DEF_RDMAVT_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <rdma/rdma_vt.h>
#include <linux/pci.h>
#include "pd.h"
#include "qp.h"
#include "ah.h"
#include "mr.h"
#include "srq.h"
#include "mcast.h"
#include "mmap.h"
#include "cq.h"
#include "mad.h"

#define rvt_pr_info(rdi, fmt, ...) \
	__rvt_pr_info(rdi->driver_f.get_pci_dev(rdi), \
		      rvt_get_ibdev_name(rdi), \
		      fmt, \
		      ##__VA_ARGS__)

#define rvt_pr_warn(rdi, fmt, ...) \
	__rvt_pr_warn(rdi->driver_f.get_pci_dev(rdi), \
		      rvt_get_ibdev_name(rdi), \
		      fmt, \
		      ##__VA_ARGS__)

#define rvt_pr_err(rdi, fmt, ...) \
	__rvt_pr_err(rdi->driver_f.get_pci_dev(rdi), \
		     rvt_get_ibdev_name(rdi), \
		     fmt, \
		     ##__VA_ARGS__)

#define rvt_pr_err_ratelimited(rdi, fmt, ...) \
	__rvt_pr_err_ratelimited((rdi)->driver_f.get_pci_dev(rdi), \
				 rvt_get_ibdev_name(rdi), \
				 fmt, \
				 ##__VA_ARGS__)

#define __rvt_pr_info(pdev, name, fmt, ...) \
	dev_info(&pdev->dev, "%s: " fmt, name, ##__VA_ARGS__)

#define __rvt_pr_warn(pdev, name, fmt, ...) \
	dev_warn(&pdev->dev, "%s: " fmt, name, ##__VA_ARGS__)

#define __rvt_pr_err(pdev, name, fmt, ...) \
	dev_err(&pdev->dev, "%s: " fmt, name, ##__VA_ARGS__)

#define __rvt_pr_err_ratelimited(pdev, name, fmt, ...) \
	dev_err_ratelimited(&(pdev)->dev, "%s: " fmt, name, ##__VA_ARGS__)

static inline u32 ibport_num_to_idx(struct ib_device *ibdev, u32 port_num)
{
	return port_num - 1; /* IB ports start at 1 our arrays at 0 */
}

#endif          /* DEF_RDMAVT_H */
