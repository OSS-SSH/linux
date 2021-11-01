/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2014-2021 Intel Corporation
 */

#ifndef _ABI_GUC_COMMUNICATION_MMIO_ABI_H
#define _ABI_GUC_COMMUNICATION_MMIO_ABI_H

/**
<<<<<<< HEAD
 * DOC: GuC MMIO based communication
 *
 * The MMIO based communication between Host and GuC relies on special
 * hardware registers which format could be defined by the software
 * (so called scratch registers).
 *
 * Each MMIO based message, both Host to GuC (H2G) and GuC to Host (G2H)
 * messages, which maximum length depends on number of available scratch
 * registers, is directly written into those scratch registers.
 *
 * For Gen9+, there are 16 software scratch registers 0xC180-0xC1B8,
 * but no H2G command takes more than 4 parameters and the GuC firmware
 * itself uses an 4-element array to store the H2G message.
 *
 * For Gen11+, there are additional 4 registers 0x190240-0x19024C, which
 * are, regardless on lower count, preferred over legacy ones.
 *
 * The MMIO based communication is mainly used during driver initialization
 * phase to setup the `CTB based communication`_ that will be used afterwards.
 */

#define GUC_MAX_MMIO_MSG_LEN		4

/**
 * DOC: MMIO HXG Message
 *
 * Format of the MMIO messages follows definitions of `HXG Message`_.
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Description                                                  |
 *  +===+=======+==============================================================+
 *  | 0 |  31:0 |                                                              |
 *  +---+-------+                                                              |
 *  |...|       | [Embedded `HXG Message`_]                                    |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */
=======
 * DOC: MMIO based communication
 *
 * The MMIO based communication between Host and GuC uses software scratch
 * registers, where first register holds data treated as message header,
 * and other registers are used to hold message payload.
 *
 * For Gen9+, GuC uses software scratch registers 0xC180-0xC1B8,
 * but no H2G command takes more than 8 parameters and the GuC FW
 * itself uses an 8-element array to store the H2G message.
 *
 *      +-----------+---------+---------+---------+
 *      |  MMIO[0]  | MMIO[1] |   ...   | MMIO[n] |
 *      +-----------+---------+---------+---------+
 *      | header    |      optional payload       |
 *      +======+====+=========+=========+=========+
 *      | 31:28|type|         |         |         |
 *      +------+----+         |         |         |
 *      | 27:16|data|         |         |         |
 *      +------+----+         |         |         |
 *      |  15:0|code|         |         |         |
 *      +------+----+---------+---------+---------+
 *
 * The message header consists of:
 *
 * - **type**, indicates message type
 * - **code**, indicates message code, is specific for **type**
 * - **data**, indicates message data, optional, depends on **code**
 *
 * The following message **types** are supported:
 *
 * - **REQUEST**, indicates Host-to-GuC request, requested GuC action code
 *   must be priovided in **code** field. Optional action specific parameters
 *   can be provided in remaining payload registers or **data** field.
 *
 * - **RESPONSE**, indicates GuC-to-Host response from earlier GuC request,
 *   action response status will be provided in **code** field. Optional
 *   response data can be returned in remaining payload registers or **data**
 *   field.
 */

#define GUC_MAX_MMIO_MSG_LEN		8
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#endif /* _ABI_GUC_COMMUNICATION_MMIO_ABI_H */
