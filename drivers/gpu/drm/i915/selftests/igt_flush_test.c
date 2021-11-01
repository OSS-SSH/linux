/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2018 Intel Corporation
 */

#include "gt/intel_gt.h"
#include "gt/intel_gt_requests.h"

#include "i915_drv.h"
#include "i915_selftest.h"

#include "igt_flush_test.h"

int igt_flush_test(struct drm_i915_private *i915)
{
	struct intel_gt *gt = &i915->gt;
	int ret = intel_gt_is_wedged(gt) ? -EIO : 0;

	cond_resched();

<<<<<<< HEAD
<<<<<<< HEAD
	if (intel_gt_wait_for_idle(gt, HZ) == -ETIME) {
=======
	if (intel_gt_wait_for_idle(gt, HZ / 5) == -ETIME) {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (intel_gt_wait_for_idle(gt, HZ) == -ETIME) {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		pr_err("%pS timed out, cancelling all further testing.\n",
		       __builtin_return_address(0));

		GEM_TRACE("%pS timed out.\n",
			  __builtin_return_address(0));
		GEM_TRACE_DUMP();

		intel_gt_set_wedged(gt);
		ret = -EIO;
	}

	return ret;
}
