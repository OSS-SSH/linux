/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef INTEL_CONTEXT_PARAM_H
#define INTEL_CONTEXT_PARAM_H

#include <linux/types.h>

#include "intel_context.h"

<<<<<<< HEAD
<<<<<<< HEAD
static inline void
intel_context_set_watchdog_us(struct intel_context *ce, u64 timeout_us)
{
	ce->watchdog.timeout_us = timeout_us;
=======
int intel_context_set_ring_size(struct intel_context *ce, long sz);
long intel_context_get_ring_size(struct intel_context *ce);

static inline int
intel_context_set_watchdog_us(struct intel_context *ce, u64 timeout_us)
{
	ce->watchdog.timeout_us = timeout_us;
	return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static inline void
intel_context_set_watchdog_us(struct intel_context *ce, u64 timeout_us)
{
	ce->watchdog.timeout_us = timeout_us;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

#endif /* INTEL_CONTEXT_PARAM_H */
