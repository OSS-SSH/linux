/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ALPHA_SYSCALL_H
#define _ASM_ALPHA_SYSCALL_H

#include <uapi/linux/audit.h>

static inline int syscall_get_arch(struct task_struct *task)
{
	return AUDIT_ARCH_ALPHA;
}

<<<<<<< HEAD
static inline long syscall_get_return_value(struct task_struct *task,
					    struct pt_regs *regs)
{
	return regs->r0;
}

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif	/* _ASM_ALPHA_SYSCALL_H */
