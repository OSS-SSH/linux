/* SPDX-License-Identifier: GPL-2.0 */
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/* Marvell RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell.
 *
 */
<<<<<<< HEAD
=======
/* Marvell OcteonTx2 PTP support for ethernet driver */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#ifndef OTX2_PTP_H
#define OTX2_PTP_H

int otx2_ptp_init(struct otx2_nic *pfvf);
void otx2_ptp_destroy(struct otx2_nic *pfvf);

int otx2_ptp_clock_index(struct otx2_nic *pfvf);
int otx2_ptp_tstamp2time(struct otx2_nic *pfvf, u64 tstamp, u64 *tsns);

#endif
