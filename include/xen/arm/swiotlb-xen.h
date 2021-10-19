/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ARM_SWIOTLB_XEN_H
#define _ASM_ARM_SWIOTLB_XEN_H

<<<<<<< HEAD
extern int xen_swiotlb_detect(void);
=======
#include <xen/features.h>
#include <xen/xen.h>

static inline int xen_swiotlb_detect(void)
{
	if (!xen_domain())
		return 0;
	if (xen_feature(XENFEAT_direct_mapped))
		return 1;
	/* legacy case */
	if (!xen_feature(XENFEAT_not_direct_mapped) && xen_initial_domain())
		return 1;
	return 0;
}
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a

#endif /* _ASM_ARM_SWIOTLB_XEN_H */
