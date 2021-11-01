/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * CQHCI crypto engine (inline encryption) support
 *
 * Copyright 2020 Google LLC
 */

#ifndef LINUX_MMC_CQHCI_CRYPTO_H
#define LINUX_MMC_CQHCI_CRYPTO_H

#include <linux/mmc/host.h>

#include "cqhci.h"

#ifdef CONFIG_MMC_CRYPTO

int cqhci_crypto_init(struct cqhci_host *host);

/*
 * Returns the crypto bits that should be set in bits 64-127 of the
 * task descriptor.
 */
static inline u64 cqhci_crypto_prep_task_desc(struct mmc_request *mrq)
{
<<<<<<< HEAD
<<<<<<< HEAD
	if (!mrq->crypto_ctx)
		return 0;

	/* We set max_dun_bytes_supported=4, so all DUNs should be 32-bit. */
	WARN_ON_ONCE(mrq->crypto_ctx->bc_dun[0] > U32_MAX);

	return CQHCI_CRYPTO_ENABLE_BIT |
	       CQHCI_CRYPTO_KEYSLOT(mrq->crypto_key_slot) |
	       mrq->crypto_ctx->bc_dun[0];
=======
	if (!mrq->crypto_enabled)
=======
	if (!mrq->crypto_ctx)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return 0;

	/* We set max_dun_bytes_supported=4, so all DUNs should be 32-bit. */
	WARN_ON_ONCE(mrq->crypto_ctx->bc_dun[0] > U32_MAX);

	return CQHCI_CRYPTO_ENABLE_BIT |
	       CQHCI_CRYPTO_KEYSLOT(mrq->crypto_key_slot) |
<<<<<<< HEAD
	       mrq->data_unit_num;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	       mrq->crypto_ctx->bc_dun[0];
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

#else /* CONFIG_MMC_CRYPTO */

static inline int cqhci_crypto_init(struct cqhci_host *host)
{
	return 0;
}

static inline u64 cqhci_crypto_prep_task_desc(struct mmc_request *mrq)
{
	return 0;
}

#endif /* !CONFIG_MMC_CRYPTO */

#endif /* LINUX_MMC_CQHCI_CRYPTO_H */
