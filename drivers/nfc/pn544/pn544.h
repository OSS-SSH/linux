/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 - 2012  Intel Corporation. All rights reserved.
 */

#ifndef __LOCAL_PN544_H_
#define __LOCAL_PN544_H_

#include <net/nfc/hci.h>

#define DRIVER_DESC "HCI NFC driver for PN544"

#define PN544_HCI_MODE 0
#define PN544_FW_MODE 1

typedef int (*fw_download_t)(void *context, const char *firmware_name,
				u8 hw_variant);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int pn544_hci_probe(void *phy_id, const struct nfc_phy_ops *phy_ops,
		    char *llc_name, int phy_headroom, int phy_tailroom,
		    int phy_payload, fw_download_t fw_download,
		    struct nfc_hci_dev **hdev);
<<<<<<< HEAD
=======
int pn544_hci_probe(void *phy_id, struct nfc_phy_ops *phy_ops, char *llc_name,
		    int phy_headroom, int phy_tailroom, int phy_payload,
		    fw_download_t fw_download, struct nfc_hci_dev **hdev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void pn544_hci_remove(struct nfc_hci_dev *hdev);

#endif /* __LOCAL_PN544_H_ */
