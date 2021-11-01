/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _INTEL_THERMAL_INTERRUPT_H
#define _INTEL_THERMAL_INTERRUPT_H

/* Interrupt Handler for package thermal thresholds */
extern int (*platform_thermal_package_notify)(__u64 msr_val);

/* Interrupt Handler for core thermal thresholds */
extern int (*platform_thermal_notify)(__u64 msr_val);

/* Callback support of rate control, return true, if
 * callback has rate control */
extern bool (*platform_thermal_package_rate_control)(void);

<<<<<<< HEAD
<<<<<<< HEAD
/* Handle HWP interrupt */
extern void notify_hwp_interrupt(void);

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
/* Handle HWP interrupt */
extern void notify_hwp_interrupt(void);

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif /* _INTEL_THERMAL_INTERRUPT_H */
