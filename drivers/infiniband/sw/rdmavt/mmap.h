<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2016 Intel Corporation.
 */

#ifndef DEF_RDMAVTMMAP_H
#define DEF_RDMAVTMMAP_H

=======
#ifndef DEF_RDMAVTMMAP_H
#define DEF_RDMAVTMMAP_H

=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2016 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef DEF_RDMAVTMMAP_H
#define DEF_RDMAVTMMAP_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <rdma/rdma_vt.h>

void rvt_mmap_init(struct rvt_dev_info *rdi);
void rvt_release_mmap_info(struct kref *ref);
int rvt_mmap(struct ib_ucontext *context, struct vm_area_struct *vma);
struct rvt_mmap_info *rvt_create_mmap_info(struct rvt_dev_info *rdi, u32 size,
					   struct ib_udata *udata, void *obj);
void rvt_update_mmap_info(struct rvt_dev_info *rdi, struct rvt_mmap_info *ip,
			  u32 size, void *obj);

#endif          /* DEF_RDMAVTMMAP_H */
