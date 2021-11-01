/* SPDX-License-Identifier: GPL-2.0-only */
/*
 *  Copyright 2007 Red Hat, Inc.
 *  by Peter Jones <pjones@redhat.com>
 *  Copyright 2007 IBM, Inc.
 *  by Konrad Rzeszutek <konradr@linux.vnet.ibm.com>
 *  Copyright 2008
 *  by Konrad Rzeszutek <ketuzsezr@darnok.org>
 *
 * This code exposes the iSCSI Boot Format Table to userland via sysfs.
 */

#ifndef ISCSI_IBFT_H
#define ISCSI_IBFT_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/types.h>

/*
 * Physical location of iSCSI Boot Format Table.
 * If the value is 0 there is no iBFT on the machine.
 */
extern phys_addr_t ibft_phys_addr;

/*
 * Routine used to find and reserve the iSCSI Boot Format Table. The
 * physical address is set in the ibft_phys_addr variable.
 */
#ifdef CONFIG_ISCSI_IBFT_FIND
void reserve_ibft_region(void);
#else
static inline void reserve_ibft_region(void) {}
=======
#include <linux/acpi.h>
=======
#include <linux/types.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

/*
 * Physical location of iSCSI Boot Format Table.
 * If the value is 0 there is no iBFT on the machine.
 */
extern phys_addr_t ibft_phys_addr;

/*
 * Routine used to find and reserve the iSCSI Boot Format Table. The
 * physical address is set in the ibft_phys_addr variable.
 */
#ifdef CONFIG_ISCSI_IBFT_FIND
void reserve_ibft_region(void);
#else
<<<<<<< HEAD
static inline unsigned long find_ibft_region(unsigned long *sizep)
{
	*sizep = 0;
	return 0;
}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static inline void reserve_ibft_region(void) {}
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif

#endif /* ISCSI_IBFT_H */
