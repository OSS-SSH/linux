<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2016 Intel Corporation.
 */

#ifndef DEF_RVTMCAST_H
#define DEF_RVTMCAST_H

=======
#ifndef DEF_RVTMCAST_H
#define DEF_RVTMCAST_H

=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2016 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef DEF_RVTMCAST_H
#define DEF_RVTMCAST_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <rdma/rdma_vt.h>

void rvt_driver_mcast_init(struct rvt_dev_info *rdi);
int rvt_attach_mcast(struct ib_qp *ibqp, union ib_gid *gid, u16 lid);
int rvt_detach_mcast(struct ib_qp *ibqp, union ib_gid *gid, u16 lid);
int rvt_mcast_tree_empty(struct rvt_dev_info *rdi);

#endif          /* DEF_RVTMCAST_H */
