/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2016 Intel Corporation
 */

#ifndef __MOCK_CONTEXT_H
#define __MOCK_CONTEXT_H

struct file;
struct drm_i915_private;
struct intel_engine_cs;
<<<<<<< HEAD
<<<<<<< HEAD
struct i915_address_space;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
struct i915_address_space;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

void mock_init_contexts(struct drm_i915_private *i915);

struct i915_gem_context *
mock_context(struct drm_i915_private *i915,
	     const char *name);

void mock_context_close(struct i915_gem_context *ctx);

struct i915_gem_context *
live_context(struct drm_i915_private *i915, struct file *file);

struct i915_gem_context *
live_context_for_engine(struct intel_engine_cs *engine, struct file *file);

<<<<<<< HEAD
<<<<<<< HEAD
struct i915_gem_context *kernel_context(struct drm_i915_private *i915,
					struct i915_address_space *vm);
=======
struct i915_gem_context *kernel_context(struct drm_i915_private *i915);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
struct i915_gem_context *kernel_context(struct drm_i915_private *i915,
					struct i915_address_space *vm);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void kernel_context_close(struct i915_gem_context *ctx);

#endif /* !__MOCK_CONTEXT_H */
