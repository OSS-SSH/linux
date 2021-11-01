// SPDX-License-Identifier: GPL-2.0-or-later
/*
 */

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/ptrace.h>

#include <asm/reg.h>

int machine_check_4xx(struct pt_regs *regs)
{
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long reason = regs->esr;
=======
	unsigned long reason = regs->dsisr;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	unsigned long reason = regs->esr;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	if (reason & ESR_IMCP) {
		printk("Instruction");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	} else
		printk("Data");
	printk(" machine check in kernel mode.\n");

	return 0;
}
