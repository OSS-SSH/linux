/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_KVM_CLOCK_H
#define _ASM_X86_KVM_CLOCK_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/percpu.h>

extern struct clocksource kvm_clock;

DECLARE_PER_CPU(struct pvclock_vsyscall_time_info *, hv_clock_per_cpu);

static inline struct pvclock_vcpu_time_info *this_cpu_pvti(void)
{
	return &this_cpu_read(hv_clock_per_cpu)->pvti;
}

static inline struct pvclock_vsyscall_time_info *this_cpu_hvclock(void)
{
	return this_cpu_read(hv_clock_per_cpu);
}

=======
extern struct clocksource kvm_clock;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <linux/percpu.h>

extern struct clocksource kvm_clock;

DECLARE_PER_CPU(struct pvclock_vsyscall_time_info *, hv_clock_per_cpu);

static inline struct pvclock_vcpu_time_info *this_cpu_pvti(void)
{
	return &this_cpu_read(hv_clock_per_cpu)->pvti;
}

static inline struct pvclock_vsyscall_time_info *this_cpu_hvclock(void)
{
	return this_cpu_read(hv_clock_per_cpu);
}

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif /* _ASM_X86_KVM_CLOCK_H */
