# SPDX-License-Identifier: GPL-2.0

CFLAGS += -I../../../../../usr/include/
<<<<<<< HEAD
TEST_GEN_PROGS := sve-ptrace sve-probe-vls vec-syscfg
TEST_PROGS_EXTENDED := fpsimd-test fpsimd-stress \
	rdvl-sve \
	sve-test sve-stress \
	vlset
=======
TEST_GEN_PROGS := sve-ptrace sve-probe-vls
TEST_PROGS_EXTENDED := fpsimd-test fpsimd-stress sve-test sve-stress vlset
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

all: $(TEST_GEN_PROGS) $(TEST_PROGS_EXTENDED)

fpsimd-test: fpsimd-test.o
	$(CC) -nostdlib $^ -o $@
<<<<<<< HEAD
rdvl-sve: rdvl-sve.o rdvl.o
sve-ptrace: sve-ptrace.o sve-ptrace-asm.o
sve-probe-vls: sve-probe-vls.o rdvl.o
sve-test: sve-test.o
	$(CC) -nostdlib $^ -o $@
vec-syscfg: vec-syscfg.o rdvl.o
=======
sve-ptrace: sve-ptrace.o sve-ptrace-asm.o
sve-probe-vls: sve-probe-vls.o
sve-test: sve-test.o
	$(CC) -nostdlib $^ -o $@
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
vlset: vlset.o

include ../../lib.mk
