# SPDX-License-Identifier: GPL-2.0-only
# Copied from arch/tile/kernel/vdso/Makefile

# Absolute relocation type $(ARCH_REL_TYPE_ABS) needs to be defined before
# the inclusion of generic Makefile.
ARCH_REL_TYPE_ABS := R_RISCV_32|R_RISCV_64|R_RISCV_JUMP_SLOT
include $(srctree)/lib/vdso/Makefile
# Symbols present in the vdso
vdso-syms  = rt_sigreturn
ifdef CONFIG_64BIT
vdso-syms += vgettimeofday
endif
vdso-syms += getcpu
vdso-syms += flush_icache

# Files to link into the vdso
obj-vdso = $(patsubst %, %.o, $(vdso-syms)) note.o

ccflags-y := -fno-stack-protector

ifneq ($(c-gettimeofday-y),)
  CFLAGS_vgettimeofday.o += -fPIC -include $(c-gettimeofday-y)
endif

# Build rules
<<<<<<< HEAD
<<<<<<< HEAD
targets := $(obj-vdso) vdso.so vdso.so.dbg vdso.lds
obj-vdso := $(addprefix $(obj)/, $(obj-vdso))

obj-y += vdso.o
=======
targets := $(obj-vdso) vdso.so vdso.so.dbg vdso.lds vdso-syms.S
obj-vdso := $(addprefix $(obj)/, $(obj-vdso))

obj-y += vdso.o vdso-syms.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
targets := $(obj-vdso) vdso.so vdso.so.dbg vdso.lds
obj-vdso := $(addprefix $(obj)/, $(obj-vdso))

obj-y += vdso.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
CPPFLAGS_vdso.lds += -P -C -U$(ARCH)

# Disable -pg to prevent insert call site
CFLAGS_REMOVE_vgettimeofday.o = $(CC_FLAGS_FTRACE) -Os

# Disable profiling and instrumentation for VDSO code
GCOV_PROFILE := n
KCOV_INSTRUMENT := n
KASAN_SANITIZE := n
<<<<<<< HEAD
<<<<<<< HEAD
UBSAN_SANITIZE := n
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
UBSAN_SANITIZE := n
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

# Force dependency
$(obj)/vdso.o: $(obj)/vdso.so

# link rule for the .so file, .lds has to be first
$(obj)/vdso.so.dbg: $(obj)/vdso.lds $(obj-vdso) FORCE
	$(call if_changed,vdsold)
<<<<<<< HEAD
<<<<<<< HEAD
LDFLAGS_vdso.so.dbg = -shared -S -soname=linux-vdso.so.1 \
	--build-id=sha1 --hash-style=both --eh-frame-hdr

=======
LDFLAGS_vdso.so.dbg = -shared -s -soname=linux-vdso.so.1 \
	--build-id=sha1 --hash-style=both --eh-frame-hdr

# We also create a special relocatable object that should mirror the symbol
# table and layout of the linked DSO. With ld --just-symbols we can then
# refer to these symbols in the kernel code rather than hand-coded addresses.
$(obj)/vdso-syms.S: $(obj)/vdso.so FORCE
	$(call if_changed,so2s)

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
LDFLAGS_vdso.so.dbg = -shared -S -soname=linux-vdso.so.1 \
	--build-id=sha1 --hash-style=both --eh-frame-hdr

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# strip rule for the .so file
$(obj)/%.so: OBJCOPYFLAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FORCE
	$(call if_changed,objcopy)

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# Generate VDSO offsets using helper script
gen-vdsosym := $(srctree)/$(src)/gen_vdso_offsets.sh
quiet_cmd_vdsosym = VDSOSYM $@
	cmd_vdsosym = $(NM) $< | $(gen-vdsosym) | LC_ALL=C sort > $@

include/generated/vdso-offsets.h: $(obj)/vdso.so.dbg FORCE
	$(call if_changed,vdsosym)

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# actual build commands
# The DSO images are built using a special linker script
# Make sure only to export the intended __vdso_xxx symbol offsets.
quiet_cmd_vdsold = VDSOLD  $@
      cmd_vdsold = $(LD) $(ld_flags) -T $(filter-out FORCE,$^) -o $@.tmp && \
                   $(OBJCOPY) $(patsubst %, -G __vdso_%, $(vdso-syms)) $@.tmp $@ && \
                   rm $@.tmp

<<<<<<< HEAD
<<<<<<< HEAD
=======
# Extracts symbol offsets from the VDSO, converting them into an assembly file
# that contains the same symbols at the same offsets.
quiet_cmd_so2s = SO2S    $@
      cmd_so2s = $(NM) -D $< | $(srctree)/$(src)/so2s.sh > $@

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# install commands for the unstripped file
quiet_cmd_vdso_install = INSTALL $@
      cmd_vdso_install = cp $(obj)/$@.dbg $(MODLIB)/vdso/$@

vdso.so: $(obj)/vdso.so.dbg
	@mkdir -p $(MODLIB)/vdso
	$(call cmd,vdso_install)

vdso_install: vdso.so
