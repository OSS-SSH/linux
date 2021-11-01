/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef INTEL_GT_REQUESTS_H
#define INTEL_GT_REQUESTS_H

<<<<<<< HEAD
#include <linux/stddef.h>

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
struct intel_engine_cs;
struct intel_gt;
struct intel_timeline;

<<<<<<< HEAD
long intel_gt_retire_requests_timeout(struct intel_gt *gt, long timeout,
				      long *remaining_timeout);
static inline void intel_gt_retire_requests(struct intel_gt *gt)
{
	intel_gt_retire_requests_timeout(gt, 0, NULL);
=======
long intel_gt_retire_requests_timeout(struct intel_gt *gt, long timeout);
static inline void intel_gt_retire_requests(struct intel_gt *gt)
{
	intel_gt_retire_requests_timeout(gt, 0);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}

void intel_engine_init_retire(struct intel_engine_cs *engine);
void intel_engine_add_retire(struct intel_engine_cs *engine,
			     struct intel_timeline *tl);
void intel_engine_fini_retire(struct intel_engine_cs *engine);

<<<<<<< HEAD
=======
int intel_gt_wait_for_idle(struct intel_gt *gt, long timeout);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
void intel_gt_init_requests(struct intel_gt *gt);
void intel_gt_park_requests(struct intel_gt *gt);
void intel_gt_unpark_requests(struct intel_gt *gt);
void intel_gt_fini_requests(struct intel_gt *gt);

#endif /* INTEL_GT_REQUESTS_H */
