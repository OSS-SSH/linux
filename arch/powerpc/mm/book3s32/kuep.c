// SPDX-License-Identifier: GPL-2.0-or-later

#include <asm/kup.h>
<<<<<<< HEAD
#include <asm/reg.h>
#include <asm/task_size_32.h>
#include <asm/mmu.h>

#define KUEP_UPDATE_TWO_USER_SEGMENTS(n) do {		\
	if (TASK_SIZE > ((n) << 28))			\
		mtsr(val1, (n) << 28);			\
	if (TASK_SIZE > (((n) + 1) << 28))		\
		mtsr(val2, ((n) + 1) << 28);		\
	val1 = (val1 + 0x222) & 0xf0ffffff;		\
	val2 = (val2 + 0x222) & 0xf0ffffff;		\
} while (0)

static __always_inline void kuep_update(u32 val)
{
	int val1 = val;
	int val2 = (val + 0x111) & 0xf0ffffff;

	KUEP_UPDATE_TWO_USER_SEGMENTS(0);
	KUEP_UPDATE_TWO_USER_SEGMENTS(2);
	KUEP_UPDATE_TWO_USER_SEGMENTS(4);
	KUEP_UPDATE_TWO_USER_SEGMENTS(6);
	KUEP_UPDATE_TWO_USER_SEGMENTS(8);
	KUEP_UPDATE_TWO_USER_SEGMENTS(10);
	KUEP_UPDATE_TWO_USER_SEGMENTS(12);
	KUEP_UPDATE_TWO_USER_SEGMENTS(14);
}

void kuep_lock(void)
{
	kuep_update(mfsr(0) | SR_NX);
}

void kuep_unlock(void)
{
	kuep_update(mfsr(0) & ~SR_NX);
=======
#include <asm/smp.h>

struct static_key_false disable_kuep_key;

void setup_kuep(bool disabled)
{
	if (!disabled)
		kuep_lock();

	if (smp_processor_id() != boot_cpuid)
		return;

	if (disabled)
		static_branch_enable(&disable_kuep_key);
	else
		pr_info("Activating Kernel Userspace Execution Prevention\n");
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a
}
