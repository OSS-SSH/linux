/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * linux/arch/arm/mach-at91/generic.h
 *
 *  Copyright (C) 2005 David Brownell
 */

#ifndef _AT91_GENERIC_H
#define _AT91_GENERIC_H

#ifdef CONFIG_PM
extern void __init at91rm9200_pm_init(void);
extern void __init at91sam9_pm_init(void);
extern void __init sam9x60_pm_init(void);
extern void __init sama5_pm_init(void);
extern void __init sama5d2_pm_init(void);
<<<<<<< HEAD
extern void __init sama7_pm_init(void);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#else
static inline void __init at91rm9200_pm_init(void) { }
static inline void __init at91sam9_pm_init(void) { }
static inline void __init sam9x60_pm_init(void) { }
static inline void __init sama5_pm_init(void) { }
static inline void __init sama5d2_pm_init(void) { }
<<<<<<< HEAD
static inline void __init sama7_pm_init(void) { }
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif

#endif /* _AT91_GENERIC_H */
