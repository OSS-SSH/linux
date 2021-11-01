/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2016 Intel Corporation
 */

#include "mock_context.h"
#include "selftests/mock_drm.h"
#include "selftests/mock_gtt.h"

struct i915_gem_context *
mock_context(struct drm_i915_private *i915,
	     const char *name)
{
	struct i915_gem_context *ctx;
	struct i915_gem_engines *e;
<<<<<<< HEAD
	struct intel_sseu null_sseu = {};
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	kref_init(&ctx->ref);
	INIT_LIST_HEAD(&ctx->link);
	ctx->i915 = i915;

	mutex_init(&ctx->mutex);

	spin_lock_init(&ctx->stale.lock);
	INIT_LIST_HEAD(&ctx->stale.engines);

	i915_gem_context_set_persistence(ctx);

<<<<<<< HEAD
=======
	mutex_init(&ctx->engines_mutex);
	e = default_engines(ctx);
	if (IS_ERR(e))
		goto err_free;
	RCU_INIT_POINTER(ctx->engines, e);

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	mutex_init(&ctx->lut_mutex);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	if (name) {
		struct i915_ppgtt *ppgtt;

		strncpy(ctx->name, name, sizeof(ctx->name) - 1);

		ppgtt = mock_ppgtt(i915, name);
		if (!ppgtt)
<<<<<<< HEAD
			goto err_free;

		ctx->vm = i915_vm_open(&ppgtt->vm);
		i915_vm_put(&ppgtt->vm);
	}

	mutex_init(&ctx->engines_mutex);
	e = default_engines(ctx, null_sseu);
	if (IS_ERR(e))
		goto err_vm;
	RCU_INIT_POINTER(ctx->engines, e);

	INIT_RADIX_TREE(&ctx->handles_vma, GFP_KERNEL);
	mutex_init(&ctx->lut_mutex);

	return ctx;

err_vm:
	if (ctx->vm)
		i915_vm_close(ctx->vm);
err_free:
	kfree(ctx);
	return NULL;
=======
			goto err_put;

		mutex_lock(&ctx->mutex);
		__set_ppgtt(ctx, &ppgtt->vm);
		mutex_unlock(&ctx->mutex);

		i915_vm_put(&ppgtt->vm);
	}

	return ctx;

err_free:
	kfree(ctx);
	return NULL;

err_put:
	i915_gem_context_set_closed(ctx);
	i915_gem_context_put(ctx);
	return NULL;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}

void mock_context_close(struct i915_gem_context *ctx)
{
	context_close(ctx);
}

void mock_init_contexts(struct drm_i915_private *i915)
{
	init_contexts(&i915->gem.contexts);
}

struct i915_gem_context *
live_context(struct drm_i915_private *i915, struct file *file)
{
<<<<<<< HEAD
	struct drm_i915_file_private *fpriv = to_drm_file(file)->driver_priv;
	struct i915_gem_proto_context *pc;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	struct i915_gem_context *ctx;
	int err;
	u32 id;

<<<<<<< HEAD
	pc = proto_context_create(i915, 0);
	if (IS_ERR(pc))
		return ERR_CAST(pc);

	ctx = i915_gem_create_context(i915, pc);
	proto_context_close(pc);
=======
	ctx = i915_gem_create_context(i915, 0);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	if (IS_ERR(ctx))
		return ctx;

	i915_gem_context_set_no_error_capture(ctx);

<<<<<<< HEAD
	err = xa_alloc(&fpriv->context_xa, &id, NULL, xa_limit_32b, GFP_KERNEL);
	if (err < 0)
		goto err_ctx;

	gem_context_register(ctx, fpriv, id);

=======
	err = gem_context_register(ctx, to_drm_file(file)->driver_priv, &id);
	if (err < 0)
		goto err_ctx;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	return ctx;

err_ctx:
	context_close(ctx);
	return ERR_PTR(err);
}

struct i915_gem_context *
live_context_for_engine(struct intel_engine_cs *engine, struct file *file)
{
	struct i915_gem_engines *engines;
	struct i915_gem_context *ctx;
<<<<<<< HEAD
	struct intel_sseu null_sseu = {};
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	struct intel_context *ce;

	engines = alloc_engines(1);
	if (!engines)
		return ERR_PTR(-ENOMEM);

	ctx = live_context(engine->i915, file);
	if (IS_ERR(ctx)) {
		__free_engines(engines, 0);
		return ctx;
	}

	ce = intel_context_create(engine);
	if (IS_ERR(ce)) {
		__free_engines(engines, 0);
		return ERR_CAST(ce);
	}

<<<<<<< HEAD
	intel_context_set_gem(ce, ctx, null_sseu);
=======
	intel_context_set_gem(ce, ctx);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	engines->engines[0] = ce;
	engines->num_engines = 1;

	mutex_lock(&ctx->engines_mutex);
	i915_gem_context_set_user_engines(ctx);
	engines = rcu_replace_pointer(ctx->engines, engines, 1);
	mutex_unlock(&ctx->engines_mutex);

	engines_idle_release(ctx, engines);

	return ctx;
}

struct i915_gem_context *
<<<<<<< HEAD
kernel_context(struct drm_i915_private *i915,
	       struct i915_address_space *vm)
{
	struct i915_gem_context *ctx;
	struct i915_gem_proto_context *pc;

	pc = proto_context_create(i915, 0);
	if (IS_ERR(pc))
		return ERR_CAST(pc);

	if (vm) {
		if (pc->vm)
			i915_vm_put(pc->vm);
		pc->vm = i915_vm_get(vm);
	}

	ctx = i915_gem_create_context(i915, pc);
	proto_context_close(pc);
=======
kernel_context(struct drm_i915_private *i915)
{
	struct i915_gem_context *ctx;

	ctx = i915_gem_create_context(i915, 0);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	if (IS_ERR(ctx))
		return ctx;

	i915_gem_context_clear_bannable(ctx);
	i915_gem_context_set_persistence(ctx);
	i915_gem_context_set_no_error_capture(ctx);

	return ctx;
}

void kernel_context_close(struct i915_gem_context *ctx)
{
	context_close(ctx);
}
