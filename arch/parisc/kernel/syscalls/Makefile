# SPDX-License-Identifier: GPL-2.0
kapi := arch/$(SRCARCH)/include/generated/asm
uapi := arch/$(SRCARCH)/include/generated/uapi/asm

_dummy := $(shell [ -d '$(uapi)' ] || mkdir -p '$(uapi)')	\
	  $(shell [ -d '$(kapi)' ] || mkdir -p '$(kapi)')

syscall := $(src)/syscall.tbl
syshdr := $(srctree)/scripts/syscallhdr.sh
systbl := $(srctree)/scripts/syscalltbl.sh

quiet_cmd_syshdr = SYSHDR  $@
<<<<<<< HEAD
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --emit-nr --abis $(abis) $< $@

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis $(abis) $< $@

$(uapi)/unistd_32.h: abis := common,32
$(uapi)/unistd_32.h: $(syscall) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(uapi)/unistd_64.h: abis := common,64
$(uapi)/unistd_64.h: $(syscall) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/syscall_table_32.h: abis := common,32
$(kapi)/syscall_table_32.h: $(syscall) $(systbl) FORCE
	$(call if_changed,systbl)

$(kapi)/syscall_table_64.h: abis := common,64
$(kapi)/syscall_table_64.h: $(syscall) $(systbl) FORCE
=======
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --emit-nr --abis common,$* $< $@

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis common,$* $< $@

$(uapi)/unistd_%.h: $(syscall) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/syscall_table_%.h: $(syscall) $(systbl) FORCE
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a
	$(call if_changed,systbl)

uapisyshdr-y		+= unistd_32.h unistd_64.h
kapisyshdr-y		+= syscall_table_32.h		\
			   syscall_table_64.h

uapisyshdr-y	:= $(addprefix $(uapi)/, $(uapisyshdr-y))
kapisyshdr-y	:= $(addprefix $(kapi)/, $(kapisyshdr-y))
targets		+= $(addprefix ../../../../, $(uapisyshdr-y) $(kapisyshdr-y))

PHONY += all
all: $(uapisyshdr-y) $(kapisyshdr-y)
	@:
