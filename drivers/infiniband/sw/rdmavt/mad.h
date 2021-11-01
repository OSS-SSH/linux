<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2016 Intel Corporation.
 */

#ifndef DEF_RVTMAD_H
#define DEF_RVTMAD_H

=======
#ifndef DEF_RVTMAD_H
#define DEF_RVTMAD_H

=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2016 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef DEF_RVTMAD_H
#define DEF_RVTMAD_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <rdma/rdma_vt.h>

int rvt_process_mad(struct ib_device *ibdev, int mad_flags, u32 port_num,
		    const struct ib_wc *in_wc, const struct ib_grh *in_grh,
		    const struct ib_mad_hdr *in, size_t in_mad_size,
		    struct ib_mad_hdr *out, size_t *out_mad_size,
		    u16 *out_mad_pkey_index);
int rvt_create_mad_agents(struct rvt_dev_info *rdi);
void rvt_free_mad_agents(struct rvt_dev_info *rdi);
#endif          /* DEF_RVTMAD_H */
