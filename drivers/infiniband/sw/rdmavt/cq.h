<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 */

#ifndef DEF_RVTCQ_H
#define DEF_RVTCQ_H

=======
#ifndef DEF_RVTCQ_H
#define DEF_RVTCQ_H

=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef DEF_RVTCQ_H
#define DEF_RVTCQ_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <rdma/rdma_vt.h>
#include <rdma/rdmavt_cq.h>

int rvt_create_cq(struct ib_cq *ibcq, const struct ib_cq_init_attr *attr,
		  struct ib_udata *udata);
int rvt_destroy_cq(struct ib_cq *ibcq, struct ib_udata *udata);
int rvt_req_notify_cq(struct ib_cq *ibcq, enum ib_cq_notify_flags notify_flags);
int rvt_resize_cq(struct ib_cq *ibcq, int cqe, struct ib_udata *udata);
int rvt_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *entry);
int rvt_driver_cq_init(void);
void rvt_cq_exit(void);
#endif          /* DEF_RVTCQ_H */
