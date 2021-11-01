/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _ASM_POWERPC_VDSO_PROCESSOR_H
#define _ASM_POWERPC_VDSO_PROCESSOR_H

#ifndef __ASSEMBLY__

/* Macros for adjusting thread priority (hardware multi-threading) */
<<<<<<< HEAD
#ifdef CONFIG_PPC64
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#define HMT_very_low()		asm volatile("or 31, 31, 31	# very low priority")
#define HMT_low()		asm volatile("or 1, 1, 1	# low priority")
#define HMT_medium_low()	asm volatile("or 6, 6, 6	# medium low priority")
#define HMT_medium()		asm volatile("or 2, 2, 2	# medium priority")
#define HMT_medium_high()	asm volatile("or 5, 5, 5	# medium high priority")
#define HMT_high()		asm volatile("or 3, 3, 3	# high priority")
<<<<<<< HEAD
#else
#define HMT_very_low()
#define HMT_low()
#define HMT_medium_low()
#define HMT_medium()
#define HMT_medium_high()
#define HMT_high()
#endif
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#ifdef CONFIG_PPC64
#define cpu_relax()	do { HMT_low(); HMT_medium(); barrier(); } while (0)
#else
#define cpu_relax()	barrier()
#endif

#endif /* __ASSEMBLY__ */

#endif /* _ASM_POWERPC_VDSO_PROCESSOR_H */
