/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __I915_GEM_LMEM_H
#define __I915_GEM_LMEM_H

#include <linux/types.h>

struct drm_i915_private;
struct drm_i915_gem_object;
struct intel_memory_region;

extern const struct drm_i915_gem_object_ops i915_gem_lmem_obj_ops;

void __iomem *
i915_gem_object_lmem_io_map(struct drm_i915_gem_object *obj,
			    unsigned long n,
			    unsigned long size);

bool i915_gem_object_is_lmem(struct drm_i915_gem_object *obj);

<<<<<<< HEAD
bool __i915_gem_object_is_lmem(struct drm_i915_gem_object *obj);

struct drm_i915_gem_object *
__i915_gem_object_create_lmem_with_ps(struct drm_i915_private *i915,
				      resource_size_t size,
				      resource_size_t page_size,
				      unsigned int flags);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
struct drm_i915_gem_object *
i915_gem_object_create_lmem(struct drm_i915_private *i915,
			    resource_size_t size,
			    unsigned int flags);

<<<<<<< HEAD
=======
int __i915_gem_lmem_object_init(struct intel_memory_region *mem,
				struct drm_i915_gem_object *obj,
				resource_size_t size,
				unsigned int flags);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif /* !__I915_GEM_LMEM_H */
