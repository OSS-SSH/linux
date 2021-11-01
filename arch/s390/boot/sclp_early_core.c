// SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include "boot.h"
#include "../../../drivers/s390/char/sclp_early_core.c"

/* SCLP early buffer must stay page-aligned and below 2GB */
static char __sclp_early_sccb[EXT_SCCB_READ_SCP] __aligned(PAGE_SIZE);

void sclp_early_setup_buffer(void)
{
	sclp_early_set_buffer(&__sclp_early_sccb);
}
<<<<<<< HEAD
=======
#include "../../../drivers/s390/char/sclp_early_core.c"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
