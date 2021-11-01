/* SPDX-License-Identifier: GPL-2.0 */
<<<<<<< HEAD
<<<<<<< HEAD
#include <basic_asm.h>
=======
#include <ppc-asm.h>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <basic_asm.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <asm/unistd.h>

	.text
FUNC_START(getppid_tm_active)
	tbegin.
	beq 1f
	li	r0, __NR_getppid
	sc
	tend.
	blr
1:
	li	r3, -1
	blr

FUNC_START(getppid_tm_suspended)
	tbegin.
	beq 1f
	li	r0, __NR_getppid
	tsuspend.
	sc
	tresume.
	tend.
	blr
1:
	li	r3, -1
	blr
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b


.macro scv level
	.long (0x44000001 | (\level) << 5)
.endm

FUNC_START(getppid_scv_tm_active)
	PUSH_BASIC_STACK(0)
	tbegin.
	beq 1f
	li	r0, __NR_getppid
	scv	0
	tend.
	POP_BASIC_STACK(0)
	blr
1:
	li	r3, -1
	POP_BASIC_STACK(0)
	blr

FUNC_START(getppid_scv_tm_suspended)
	PUSH_BASIC_STACK(0)
	tbegin.
	beq 1f
	li	r0, __NR_getppid
	tsuspend.
	scv	0
	tresume.
	tend.
	POP_BASIC_STACK(0)
	blr
1:
	li	r3, -1
	POP_BASIC_STACK(0)
	blr
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
