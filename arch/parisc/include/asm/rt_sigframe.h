/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_PARISC_RT_SIGFRAME_H
#define _ASM_PARISC_RT_SIGFRAME_H

<<<<<<< HEAD
<<<<<<< HEAD
#define SIGRETURN_TRAMP 3
=======
#define SIGRETURN_TRAMP 4
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define SIGRETURN_TRAMP 3
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define SIGRESTARTBLOCK_TRAMP 5 
#define TRAMP_SIZE (SIGRETURN_TRAMP + SIGRESTARTBLOCK_TRAMP)

struct rt_sigframe {
	/* XXX: Must match trampoline size in arch/parisc/kernel/signal.c 
	        Secondary to that it must protect the ERESTART_RESTARTBLOCK
		trampoline we left on the stack (we were bad and didn't 
		change sp so we could run really fast.) */
	unsigned int tramp[TRAMP_SIZE];
	struct siginfo info;
	struct ucontext uc;
};

#define	SIGFRAME		128
#define FUNCTIONCALLFRAME	96
#define PARISC_RT_SIGFRAME_SIZE					\
	(((sizeof(struct rt_sigframe) + FUNCTIONCALLFRAME) + SIGFRAME) & -SIGFRAME)

#endif
