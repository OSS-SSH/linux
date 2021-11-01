// SPDX-License-Identifier: GPL-2.0-only
/******************************************************************************
 * features.c
 *
 * Xen feature flags.
 *
 * Copyright (c) 2006, Ian Campbell, XenSource Inc.
 */
#include <linux/types.h>
#include <linux/cache.h>
#include <linux/export.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/printk.h>

#include <asm/xen/hypercall.h>

#include <xen/xen.h>
<<<<<<< HEAD
=======

#include <asm/xen/hypercall.h>

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <xen/interface/xen.h>
#include <xen/interface/version.h>
#include <xen/features.h>

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Linux kernel expects at least Xen 4.0.
 *
 * Assume some features to be available for that reason (depending on guest
 * mode, of course).
 */
#define chk_required_feature(f) {					\
		if (!xen_feature(f))					\
			panic("Xen: feature %s not available!\n", #f);	\
	}

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
u8 xen_features[XENFEAT_NR_SUBMAPS * 32] __read_mostly;
EXPORT_SYMBOL_GPL(xen_features);

void xen_setup_features(void)
{
	struct xen_feature_info fi;
	int i, j;

	for (i = 0; i < XENFEAT_NR_SUBMAPS; i++) {
		fi.submap_idx = i;
		if (HYPERVISOR_xen_version(XENVER_get_features, &fi) < 0)
			break;
		for (j = 0; j < 32; j++)
			xen_features[i * 32 + j] = !!(fi.submap & 1<<j);
	}
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	if (xen_pv_domain()) {
		chk_required_feature(XENFEAT_mmu_pt_update_preserve_ad);
		chk_required_feature(XENFEAT_gnttab_map_avail_bits);
	}
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}
