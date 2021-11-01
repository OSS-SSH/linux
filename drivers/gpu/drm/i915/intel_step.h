/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2020,2021 Intel Corporation
 */

#ifndef __INTEL_STEP_H__
#define __INTEL_STEP_H__

#include <linux/types.h>

struct drm_i915_private;

struct intel_step_info {
	u8 gt_step;
	u8 display_step;
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define STEP_ENUM_VAL(name)  STEP_##name,

#define STEP_NAME_LIST(func)		\
	func(A0)			\
	func(A1)			\
	func(A2)			\
	func(B0)			\
	func(B1)			\
	func(B2)			\
	func(C0)			\
	func(C1)			\
	func(D0)			\
	func(D1)			\
	func(E0)			\
	func(F0)			\
	func(G0)			\
	func(H0)			\
	func(I0)			\
	func(I1)			\
	func(J0)

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Symbolic steppings that do not match the hardware. These are valid both as gt
 * and display steppings as symbolic names.
 */
enum intel_step {
	STEP_NONE = 0,
<<<<<<< HEAD
<<<<<<< HEAD
	STEP_NAME_LIST(STEP_ENUM_VAL)
=======
	STEP_A0,
	STEP_A2,
	STEP_B0,
	STEP_B1,
	STEP_C0,
	STEP_D0,
	STEP_D1,
	STEP_E0,
	STEP_F0,
	STEP_G0,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	STEP_NAME_LIST(STEP_ENUM_VAL)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	STEP_FUTURE,
	STEP_FOREVER,
};

void intel_step_init(struct drm_i915_private *i915);
<<<<<<< HEAD
<<<<<<< HEAD
const char *intel_step_name(enum intel_step step);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
const char *intel_step_name(enum intel_step step);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* __INTEL_STEP_H__ */
