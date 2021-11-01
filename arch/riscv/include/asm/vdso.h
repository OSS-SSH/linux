/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Limited
 * Copyright (C) 2014 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */

#ifndef _ASM_RISCV_VDSO_H
#define _ASM_RISCV_VDSO_H

<<<<<<< HEAD
<<<<<<< HEAD

/*
 * All systems with an MMU have a VDSO, but systems without an MMU don't
 * support shared libraries and therefor don't have one.
 */
#ifdef CONFIG_MMU

#include <linux/types.h>
/*
 * All systems with an MMU have a VDSO, but systems without an MMU don't
 * support shared libraries and therefor don't have one.
 */
#ifdef CONFIG_MMU

#define __VVAR_PAGES    1

#ifndef __ASSEMBLY__
#include <generated/vdso-offsets.h>

#define VDSO_SYMBOL(base, name)							\
	(void __user *)((unsigned long)(base) + __vdso_##name##_offset)

#endif /* CONFIG_MMU */

#endif /* !__ASSEMBLY__ */

#endif /* CONFIG_MMU */
=======
#include <linux/types.h>
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

/*
 * All systems with an MMU have a VDSO, but systems without an MMU don't
 * support shared libraries and therefor don't have one.
 */
#ifdef CONFIG_MMU

#include <linux/types.h>
/*
 * All systems with an MMU have a VDSO, but systems without an MMU don't
 * support shared libraries and therefor don't have one.
 */
#ifdef CONFIG_MMU

#define __VVAR_PAGES    1

#ifndef __ASSEMBLY__
#include <generated/vdso-offsets.h>

#define VDSO_SYMBOL(base, name)							\
	(void __user *)((unsigned long)(base) + __vdso_##name##_offset)

#endif /* CONFIG_MMU */

#endif /* !__ASSEMBLY__ */

<<<<<<< HEAD
asmlinkage long sys_riscv_flush_icache(uintptr_t, uintptr_t, uintptr_t);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#endif /* CONFIG_MMU */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* _ASM_RISCV_VDSO_H */
