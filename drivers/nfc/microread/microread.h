/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 - 2012  Intel Corporation. All rights reserved.
 */

#ifndef __LOCAL_MICROREAD_H_
#define __LOCAL_MICROREAD_H_

#include <net/nfc/hci.h>

#define DRIVER_DESC "NFC driver for microread"

<<<<<<< HEAD
<<<<<<< HEAD
int microread_probe(void *phy_id, const struct nfc_phy_ops *phy_ops,
		    const char *llc_name, int phy_headroom, int phy_tailroom,
		    int phy_payload, struct nfc_hci_dev **hdev);
=======
int microread_probe(void *phy_id, struct nfc_phy_ops *phy_ops, char *llc_name,
		    int phy_headroom, int phy_tailroom, int phy_payload,
		    struct nfc_hci_dev **hdev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
int microread_probe(void *phy_id, const struct nfc_phy_ops *phy_ops,
		    const char *llc_name, int phy_headroom, int phy_tailroom,
		    int phy_payload, struct nfc_hci_dev **hdev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

void microread_remove(struct nfc_hci_dev *hdev);

#endif /* __LOCAL_MICROREAD_H_ */
