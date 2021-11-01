<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2016 Intel Corporation.
 */

#ifndef DEF_RDMAVTPD_H
#define DEF_RDMAVTPD_H

=======
#ifndef DEF_RDMAVTPD_H
#define DEF_RDMAVTPD_H

=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2016 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef DEF_RDMAVTPD_H
#define DEF_RDMAVTPD_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <rdma/rdma_vt.h>

int rvt_alloc_pd(struct ib_pd *pd, struct ib_udata *udata);
int rvt_dealloc_pd(struct ib_pd *ibpd, struct ib_udata *udata);

#endif          /* DEF_RDMAVTPD_H */
