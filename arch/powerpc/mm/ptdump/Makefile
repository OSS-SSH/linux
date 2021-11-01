# SPDX-License-Identifier: GPL-2.0

obj-y	+= ptdump.o

obj-$(CONFIG_4xx)		+= shared.o
obj-$(CONFIG_PPC_8xx)		+= 8xx.o
obj-$(CONFIG_PPC_BOOK3E_MMU)	+= shared.o
<<<<<<< HEAD
obj-$(CONFIG_PPC_BOOK3S_32)	+= shared.o
obj-$(CONFIG_PPC_BOOK3S_64)	+= book3s64.o

ifdef CONFIG_PTDUMP_DEBUGFS
obj-$(CONFIG_PPC_BOOK3S_32)	+= bats.o segment_regs.o
obj-$(CONFIG_PPC_BOOK3S_64)	+= hashpagetable.o
endif
=======
obj-$(CONFIG_PPC_BOOK3S_32)	+= shared.o bats.o segment_regs.o
obj-$(CONFIG_PPC_BOOK3S_64)	+= book3s64.o hashpagetable.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
