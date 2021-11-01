/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_BREADCRUMBS__
#define __INTEL_BREADCRUMBS__

#include <linux/atomic.h>
#include <linux/irq_work.h>

<<<<<<< HEAD
#include "intel_breadcrumbs_types.h"
=======
#include "intel_engine_types.h"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

struct drm_printer;
struct i915_request;
struct intel_breadcrumbs;

struct intel_breadcrumbs *
intel_breadcrumbs_create(struct intel_engine_cs *irq_engine);
<<<<<<< HEAD
void intel_breadcrumbs_free(struct kref *kref);
=======
void intel_breadcrumbs_free(struct intel_breadcrumbs *b);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

void intel_breadcrumbs_reset(struct intel_breadcrumbs *b);
void __intel_breadcrumbs_park(struct intel_breadcrumbs *b);

static inline void intel_breadcrumbs_unpark(struct intel_breadcrumbs *b)
{
	atomic_inc(&b->active);
}

static inline void intel_breadcrumbs_park(struct intel_breadcrumbs *b)
{
	if (atomic_dec_and_test(&b->active))
		__intel_breadcrumbs_park(b);
}

static inline void
intel_engine_signal_breadcrumbs(struct intel_engine_cs *engine)
{
	irq_work_queue(&engine->breadcrumbs->irq_work);
}

void intel_engine_print_breadcrumbs(struct intel_engine_cs *engine,
				    struct drm_printer *p);

bool i915_request_enable_breadcrumb(struct i915_request *request);
void i915_request_cancel_breadcrumb(struct i915_request *request);

void intel_context_remove_breadcrumbs(struct intel_context *ce,
				      struct intel_breadcrumbs *b);

<<<<<<< HEAD
static inline struct intel_breadcrumbs *
intel_breadcrumbs_get(struct intel_breadcrumbs *b)
{
	kref_get(&b->ref);
	return b;
}

static inline void intel_breadcrumbs_put(struct intel_breadcrumbs *b)
{
	kref_put(&b->ref, intel_breadcrumbs_free);
}

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif /* __INTEL_BREADCRUMBS__ */
