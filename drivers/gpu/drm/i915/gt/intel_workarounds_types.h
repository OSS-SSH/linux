/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2014-2018 Intel Corporation
 */

#ifndef __INTEL_WORKAROUNDS_TYPES_H__
#define __INTEL_WORKAROUNDS_TYPES_H__

#include <linux/types.h>

#include "i915_reg.h"

struct i915_wa {
	i915_reg_t	reg;
	u32		clr;
	u32		set;
	u32		read;
<<<<<<< HEAD
<<<<<<< HEAD
	bool		masked_reg;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	bool		masked_reg;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

struct i915_wa_list {
	const char	*name;
	const char	*engine_name;
	struct i915_wa	*list;
	unsigned int	count;
	unsigned int	wa_count;
};

#endif /* __INTEL_WORKAROUNDS_TYPES_H__ */
