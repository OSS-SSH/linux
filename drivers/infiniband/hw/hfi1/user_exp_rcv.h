<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2020 - Cornelis Networks, Inc.
 * Copyright(c) 2015 - 2017 Intel Corporation.
 */

#ifndef _HFI1_USER_EXP_RCV_H
#define _HFI1_USER_EXP_RCV_H

=======
#ifndef _HFI1_USER_EXP_RCV_H
#define _HFI1_USER_EXP_RCV_H
=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2020 - Cornelis Networks, Inc.
 * Copyright(c) 2015 - 2017 Intel Corporation.
 */

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef _HFI1_USER_EXP_RCV_H
#define _HFI1_USER_EXP_RCV_H

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include "hfi.h"
#include "exp_rcv.h"

struct tid_pageset {
	u16 idx;
	u16 count;
};

struct tid_user_buf {
	unsigned long vaddr;
	unsigned long length;
	unsigned int npages;
	struct page **pages;
	struct tid_pageset *psets;
	unsigned int n_psets;
};

struct tid_rb_node {
	struct mmu_interval_notifier notifier;
	struct hfi1_filedata *fdata;
	unsigned long phys;
	struct tid_group *grp;
	u32 rcventry;
	dma_addr_t dma_addr;
	bool freed;
	unsigned int npages;
	struct page *pages[];
};

static inline int num_user_pages(unsigned long addr,
				 unsigned long len)
{
	const unsigned long spage = addr & PAGE_MASK;
	const unsigned long epage = (addr + len - 1) & PAGE_MASK;

	return 1 + ((epage - spage) >> PAGE_SHIFT);
}

int hfi1_user_exp_rcv_init(struct hfi1_filedata *fd,
			   struct hfi1_ctxtdata *uctxt);
void hfi1_user_exp_rcv_free(struct hfi1_filedata *fd);
int hfi1_user_exp_rcv_setup(struct hfi1_filedata *fd,
			    struct hfi1_tid_info *tinfo);
int hfi1_user_exp_rcv_clear(struct hfi1_filedata *fd,
			    struct hfi1_tid_info *tinfo);
int hfi1_user_exp_rcv_invalid(struct hfi1_filedata *fd,
			      struct hfi1_tid_info *tinfo);

static inline struct mm_struct *mm_from_tid_node(struct tid_rb_node *node)
{
	return node->notifier.mm;
}

#endif /* _HFI1_USER_EXP_RCV_H */
