/* SPDX-License-Identifier: GPL-2.0 */
/* Marvell PTP driver
 *
<<<<<<< HEAD
 * Copyright (C) 2020 Marvell.
 *
=======
 * Copyright (C) 2020 Marvell International Ltd.
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
 */

#ifndef PTP_H
#define PTP_H

#include <linux/timecounter.h>
#include <linux/time64.h>
#include <linux/spinlock.h>

struct ptp {
	struct pci_dev *pdev;
	void __iomem *reg_base;
	u32 clock_rate;
};

struct ptp *ptp_get(void);
void ptp_put(struct ptp *ptp);

extern struct pci_driver ptp_driver;

#endif
