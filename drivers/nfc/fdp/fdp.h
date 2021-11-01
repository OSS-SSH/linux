/* SPDX-License-Identifier: GPL-2.0-or-later */
/* -------------------------------------------------------------------------
 * Copyright (C) 2014-2016, Intel Corporation
 *
 * -------------------------------------------------------------------------
 */

#ifndef __LOCAL_FDP_H_
#define __LOCAL_FDP_H_

#include <net/nfc/nci_core.h>
#include <linux/gpio/consumer.h>

struct fdp_i2c_phy {
	struct i2c_client *i2c_dev;
	struct gpio_desc *power_gpio;
	struct nci_dev *ndev;

	/* < 0 if i2c error occurred */
	int hard_fault;
	uint16_t next_read_size;
};

<<<<<<< HEAD
<<<<<<< HEAD
int fdp_nci_probe(struct fdp_i2c_phy *phy, const struct nfc_phy_ops *phy_ops,
		  struct nci_dev **ndev, int tx_headroom, int tx_tailroom,
		  u8 clock_type, u32 clock_freq, const u8 *fw_vsc_cfg);
=======
int fdp_nci_probe(struct fdp_i2c_phy *phy, struct nfc_phy_ops *phy_ops,
		  struct nci_dev **ndev, int tx_headroom, int tx_tailroom,
		  u8 clock_type, u32 clock_freq, u8 *fw_vsc_cfg);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
int fdp_nci_probe(struct fdp_i2c_phy *phy, const struct nfc_phy_ops *phy_ops,
		  struct nci_dev **ndev, int tx_headroom, int tx_tailroom,
		  u8 clock_type, u32 clock_freq, const u8 *fw_vsc_cfg);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void fdp_nci_remove(struct nci_dev *ndev);

#endif /* __LOCAL_FDP_H_ */
