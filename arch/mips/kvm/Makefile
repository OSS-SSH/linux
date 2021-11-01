# SPDX-License-Identifier: GPL-2.0
# Makefile for KVM support for MIPS
#

<<<<<<< HEAD
ccflags-y += -Ivirt/kvm -Iarch/mips/kvm

kvm-y := $(addprefix ../../../virt/kvm/, kvm_main.o coalesced_mmio.o eventfd.o binary_stats.o)
kvm-$(CONFIG_CPU_HAS_MSA) += msa.o

kvm-y +=    mips.o emulate.o entry.o \
	    interrupt.o stats.o \
	    fpu.o
kvm-y += hypcall.o
kvm-y += mmu.o
kvm-$(CONFIG_CPU_LOONGSON64) += loongson_ipi.o

kvm-y		+= vz.o
=======
common-objs-y = $(addprefix ../../../virt/kvm/, kvm_main.o coalesced_mmio.o eventfd.o binary_stats.o)

EXTRA_CFLAGS += -Ivirt/kvm -Iarch/mips/kvm

common-objs-$(CONFIG_CPU_HAS_MSA) += msa.o

kvm-objs := $(common-objs-y) mips.o emulate.o entry.o \
	    interrupt.o stats.o \
	    fpu.o
kvm-objs += hypcall.o
kvm-objs += mmu.o
ifdef CONFIG_CPU_LOONGSON64
kvm-objs += loongson_ipi.o
endif

kvm-objs		+= vz.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
obj-$(CONFIG_KVM)	+= kvm.o
obj-y			+= callback.o tlb.o
