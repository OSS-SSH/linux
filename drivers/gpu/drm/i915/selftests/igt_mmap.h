/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2019 Intel Corporation
 */

#ifndef IGT_MMAP_H
#define IGT_MMAP_H

<<<<<<< HEAD
#include <linux/types.h>

struct drm_i915_private;
struct drm_vma_offset_node;

unsigned long igt_mmap_offset(struct drm_i915_private *i915,
			      u64 offset,
			      unsigned long size,
			      unsigned long prot,
			      unsigned long flags);
=======
struct drm_i915_private;
struct drm_vma_offset_node;

unsigned long igt_mmap_node(struct drm_i915_private *i915,
			    struct drm_vma_offset_node *node,
			    unsigned long addr,
			    unsigned long prot,
			    unsigned long flags);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#endif /* IGT_MMAP_H */
