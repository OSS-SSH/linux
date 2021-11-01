/* SPDX-License-Identifier: (GPL-2.0+ OR BSD-3-Clause) */
<<<<<<< HEAD
<<<<<<< HEAD
/* Copyright 2021 NXP */
=======
/* Copyright 2021 NXP Semiconductors */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
/* Copyright 2021 NXP */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#include <linux/pci.h>
#include <linux/platform_device.h>

#if IS_ENABLED(CONFIG_FSL_ENETC_IERB)

int enetc_ierb_register_pf(struct platform_device *pdev,
			   struct pci_dev *pf_pdev);

#else

static inline int enetc_ierb_register_pf(struct platform_device *pdev,
					 struct pci_dev *pf_pdev)
{
	return -EOPNOTSUPP;
}

#endif
