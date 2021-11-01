/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2019-2020 Linaro Limited */

#ifndef XHCI_PCI_H
#define XHCI_PCI_H

#if IS_ENABLED(CONFIG_USB_XHCI_PCI_RENESAS)
int renesas_xhci_check_request_fw(struct pci_dev *dev,
				  const struct pci_device_id *id);
<<<<<<< HEAD
<<<<<<< HEAD
=======
void renesas_xhci_pci_exit(struct pci_dev *dev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#else
static int renesas_xhci_check_request_fw(struct pci_dev *dev,
					 const struct pci_device_id *id)
{
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
static void renesas_xhci_pci_exit(struct pci_dev *dev) { };

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif

struct xhci_driver_data {
	u64 quirks;
	const char *firmware;
};

#endif
