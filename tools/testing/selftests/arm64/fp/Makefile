# SPDX-License-Identifier: GPL-2.0

CFLAGS += -I../../../../../usr/include/
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
TEST_GEN_PROGS := sve-ptrace sve-probe-vls vec-syscfg
TEST_PROGS_EXTENDED := fpsimd-test fpsimd-stress \
	rdvl-sve \
	sve-test sve-stress \
	vlset
<<<<<<< HEAD
=======
TEST_GEN_PROGS := sve-ptrace sve-probe-vls
TEST_PROGS_EXTENDED := fpsimd-test fpsimd-stress sve-test sve-stress vlset
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

all: $(TEST_GEN_PROGS) $(TEST_PROGS_EXTENDED)

fpsimd-test: fpsimd-test.o
	$(CC) -nostdlib $^ -o $@
<<<<<<< HEAD
<<<<<<< HEAD
rdvl-sve: rdvl-sve.o rdvl.o
sve-ptrace: sve-ptrace.o sve-ptrace-asm.o
sve-probe-vls: sve-probe-vls.o rdvl.o
sve-test: sve-test.o
	$(CC) -nostdlib $^ -o $@
vec-syscfg: vec-syscfg.o rdvl.o
=======
=======
rdvl-sve: rdvl-sve.o rdvl.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
sve-ptrace: sve-ptrace.o sve-ptrace-asm.o
sve-probe-vls: sve-probe-vls.o rdvl.o
sve-test: sve-test.o
	$(CC) -nostdlib $^ -o $@
<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
vec-syscfg: vec-syscfg.o rdvl.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
vlset: vlset.o

include ../../lib.mk
