// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright 2015, Sam Bobroff, IBM Corp.
 *
 * Test the kernel's system call code to ensure that a system call
 * made from within an active HTM transaction is aborted with the
 * correct failure code.
 * Conversely, ensure that a system call made from within a
 * suspended transaction can succeed.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <asm/tm.h>
#include <sys/time.h>
#include <stdlib.h>

#include "utils.h"
#include "tm.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#ifndef PPC_FEATURE2_SCV
#define PPC_FEATURE2_SCV               0x00100000 /* scv syscall */
#endif

<<<<<<< HEAD
extern int getppid_tm_active(void);
extern int getppid_tm_suspended(void);
extern int getppid_scv_tm_active(void);
extern int getppid_scv_tm_suspended(void);
=======
extern int getppid_tm_active(void);
extern int getppid_tm_suspended(void);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
extern int getppid_tm_active(void);
extern int getppid_tm_suspended(void);
extern int getppid_scv_tm_active(void);
extern int getppid_scv_tm_suspended(void);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

unsigned retries = 0;

#define TEST_DURATION 10 /* seconds */
<<<<<<< HEAD
<<<<<<< HEAD

pid_t getppid_tm(bool scv, bool suspend)
=======
#define TM_RETRIES 100

pid_t getppid_tm(bool suspend)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

pid_t getppid_tm(bool scv, bool suspend)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int i;
	pid_t pid;

	for (i = 0; i < TM_RETRIES; i++) {
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (suspend) {
			if (scv)
				pid = getppid_scv_tm_suspended();
			else
				pid = getppid_tm_suspended();
		} else {
			if (scv)
				pid = getppid_scv_tm_active();
			else
				pid = getppid_tm_active();
		}
<<<<<<< HEAD
=======
		if (suspend)
			pid = getppid_tm_suspended();
		else
			pid = getppid_tm_active();
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

		if (pid >= 0)
			return pid;

		if (failure_is_persistent()) {
			if (failure_is_syscall())
				return -1;

			printf("Unexpected persistent transaction failure.\n");
			printf("TEXASR 0x%016lx, TFIAR 0x%016lx.\n",
			       __builtin_get_texasr(), __builtin_get_tfiar());
			exit(-1);
		}

		retries++;
	}

	printf("Exceeded limit of %d temporary transaction failures.\n", TM_RETRIES);
	printf("TEXASR 0x%016lx, TFIAR 0x%016lx.\n",
	       __builtin_get_texasr(), __builtin_get_tfiar());

	exit(-1);
}

int tm_syscall(void)
{
	unsigned count = 0;
	struct timeval end, now;

	SKIP_IF(!have_htm_nosc());
<<<<<<< HEAD
<<<<<<< HEAD
	SKIP_IF(htm_is_synthetic());
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	SKIP_IF(htm_is_synthetic());
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	setbuf(stdout, NULL);

	printf("Testing transactional syscalls for %d seconds...\n", TEST_DURATION);

	gettimeofday(&end, NULL);
	now.tv_sec = TEST_DURATION;
	now.tv_usec = 0;
	timeradd(&end, &now, &end);

	for (count = 0; timercmp(&now, &end, <); count++) {
		/*
		 * Test a syscall within a suspended transaction and verify
		 * that it succeeds.
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		FAIL_IF(getppid_tm(false, true) == -1); /* Should succeed. */
=======
		FAIL_IF(getppid_tm(true) == -1); /* Should succeed. */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		FAIL_IF(getppid_tm(false, true) == -1); /* Should succeed. */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

		/*
		 * Test a syscall within an active transaction and verify that
		 * it fails with the correct failure code.
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		FAIL_IF(getppid_tm(false, false) != -1);  /* Should fail... */
		FAIL_IF(!failure_is_persistent()); /* ...persistently... */
		FAIL_IF(!failure_is_syscall());    /* ...with code syscall. */

		/* Now do it all again with scv if it is available. */
		if (have_hwcap2(PPC_FEATURE2_SCV)) {
			FAIL_IF(getppid_tm(true, true) == -1); /* Should succeed. */
			FAIL_IF(getppid_tm(true, false) != -1);  /* Should fail... */
			FAIL_IF(!failure_is_persistent()); /* ...persistently... */
			FAIL_IF(!failure_is_syscall());    /* ...with code syscall. */
		}

=======
		FAIL_IF(getppid_tm(false) != -1);  /* Should fail... */
		FAIL_IF(!failure_is_persistent()); /* ...persistently... */
		FAIL_IF(!failure_is_syscall());    /* ...with code syscall. */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		FAIL_IF(getppid_tm(false, false) != -1);  /* Should fail... */
		FAIL_IF(!failure_is_persistent()); /* ...persistently... */
		FAIL_IF(!failure_is_syscall());    /* ...with code syscall. */

		/* Now do it all again with scv if it is available. */
		if (have_hwcap2(PPC_FEATURE2_SCV)) {
			FAIL_IF(getppid_tm(true, true) == -1); /* Should succeed. */
			FAIL_IF(getppid_tm(true, false) != -1);  /* Should fail... */
			FAIL_IF(!failure_is_persistent()); /* ...persistently... */
			FAIL_IF(!failure_is_syscall());    /* ...with code syscall. */
		}

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		gettimeofday(&now, 0);
	}

	printf("%d active and suspended transactions behaved correctly.\n", count);
	printf("(There were %d transaction retries.)\n", retries);

	return 0;
}

int main(void)
{
	return test_harness(tm_syscall, "tm_syscall");
}
