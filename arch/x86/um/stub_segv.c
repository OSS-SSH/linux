/*
 * Copyright (C) 2004 - 2007 Jeff Dike (jdike@{addtoit,linux.intel}.com)
 * Licensed under the GPL
 */

#include <sysdep/stub.h>
#include <sysdep/faultinfo.h>
#include <sysdep/mcontext.h>
#include <sys/ucontext.h>

void __attribute__ ((__section__ (".__syscall_stub")))
stub_segv_handler(int sig, siginfo_t *info, void *p)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct faultinfo *f = get_stub_page();
	ucontext_t *uc = p;
=======
	int stack;
	ucontext_t *uc = p;
	struct faultinfo *f = (void *)(((unsigned long)&stack) & ~(UM_KERN_PAGE_SIZE - 1));
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct faultinfo *f = get_stub_page();
	ucontext_t *uc = p;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	GET_FAULTINFO_FROM_MC(*f, &uc->uc_mcontext);
	trap_myself();
}

