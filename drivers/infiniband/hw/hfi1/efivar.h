<<<<<<< HEAD
<<<<<<< HEAD
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 */

=======
=======
/* SPDX-License-Identifier: GPL-2.0 or BSD-3-Clause */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 */
<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#ifndef _HFI1_EFIVAR_H
#define _HFI1_EFIVAR_H

#include <linux/efi.h>

#include "hfi.h"

int read_hfi1_efi_var(struct hfi1_devdata *dd, const char *kind,
		      unsigned long *size, void **return_data);

#endif /* _HFI1_EFIVAR_H */
