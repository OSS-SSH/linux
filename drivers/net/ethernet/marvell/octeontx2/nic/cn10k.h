<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/* SPDX-License-Identifier: GPL-2.0 */
/* Marvell RVU Ethernet driver
 *
 * Copyright (C) 2021 Marvell.
<<<<<<< HEAD
 *
=======
/* SPDX-License-Identifier: GPL-2.0
 * Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell.
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 *
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 */

#ifndef CN10K_H
#define CN10K_H

#include "otx2_common.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static inline int mtu_to_dwrr_weight(struct otx2_nic *pfvf, int mtu)
{
	u32 weight;

	/* On OTx2, since AF returns DWRR_MTU as '1', this logic
	 * will work on those silicons as well.
	 */
	weight = mtu / pfvf->hw.dwrr_mtu;
	if (mtu % pfvf->hw.dwrr_mtu)
		weight += 1;

	return weight;
}

<<<<<<< HEAD
void cn10k_refill_pool_ptrs(void *dev, struct otx2_cq_queue *cq);
void cn10k_sqe_flush(void *dev, struct otx2_snd_queue *sq, int size, int qidx);
int cn10k_sq_aq_init(void *dev, u16 qidx, u16 sqb_aura);
int cn10k_lmtst_init(struct otx2_nic *pfvf);
=======
void cn10k_refill_pool_ptrs(void *dev, struct otx2_cq_queue *cq);
void cn10k_sqe_flush(void *dev, struct otx2_snd_queue *sq, int size, int qidx);
int cn10k_sq_aq_init(void *dev, u16 qidx, u16 sqb_aura);
int cn10k_pf_lmtst_init(struct otx2_nic *pf);
int cn10k_vf_lmtst_init(struct otx2_nic *vf);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void cn10k_refill_pool_ptrs(void *dev, struct otx2_cq_queue *cq);
void cn10k_sqe_flush(void *dev, struct otx2_snd_queue *sq, int size, int qidx);
int cn10k_sq_aq_init(void *dev, u16 qidx, u16 sqb_aura);
int cn10k_lmtst_init(struct otx2_nic *pfvf);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int cn10k_free_all_ipolicers(struct otx2_nic *pfvf);
int cn10k_alloc_matchall_ipolicer(struct otx2_nic *pfvf);
int cn10k_free_matchall_ipolicer(struct otx2_nic *pfvf);
int cn10k_set_matchall_ipolicer_rate(struct otx2_nic *pfvf,
				     u32 burst, u64 rate);
int cn10k_map_unmap_rq_policer(struct otx2_nic *pfvf, int rq_idx,
			       u16 policer, bool map);
int cn10k_alloc_leaf_profile(struct otx2_nic *pfvf, u16 *leaf);
int cn10k_set_ipolicer_rate(struct otx2_nic *pfvf, u16 profile,
			    u32 burst, u64 rate, bool pps);
int cn10k_free_leaf_profile(struct otx2_nic *pfvf, u16 leaf);
#endif /* CN10K_H */
