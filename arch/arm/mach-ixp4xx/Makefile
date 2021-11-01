# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the linux kernel.
#

obj-pci-y	:=
obj-pci-n	:=

# Device tree platform
obj-pci-$(CONFIG_MACH_IXP4XX_OF)	+= ixp4xx-of.o

<<<<<<< HEAD
<<<<<<< HEAD
obj-pci-$(CONFIG_MACH_GATEWAY7001)	+= gateway7001-pci.o

obj-y	+= common.o

obj-$(CONFIG_MACH_GATEWAY7001)	+= gateway7001-setup.o
obj-$(CONFIG_MACH_GORAMO_MLR)	+= goramo_mlr.o
=======
obj-pci-$(CONFIG_ARCH_IXDP4XX)		+= ixdp425-pci.o
obj-pci-$(CONFIG_MACH_AVILA)		+= avila-pci.o
obj-pci-$(CONFIG_MACH_IXDPG425)		+= ixdpg425-pci.o
obj-pci-$(CONFIG_ARCH_ADI_COYOTE)	+= coyote-pci.o
obj-pci-$(CONFIG_MACH_GTWX5715)		+= gtwx5715-pci.o
obj-pci-$(CONFIG_MACH_MICCPT)		+= miccpt-pci.o
obj-pci-$(CONFIG_MACH_NSLU2)		+= nslu2-pci.o
obj-pci-$(CONFIG_MACH_NAS100D)		+= nas100d-pci.o
obj-pci-$(CONFIG_MACH_DSMG600)		+= dsmg600-pci.o
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
obj-pci-$(CONFIG_MACH_GATEWAY7001)	+= gateway7001-pci.o

obj-y	+= common.o

obj-$(CONFIG_MACH_GATEWAY7001)	+= gateway7001-setup.o
obj-$(CONFIG_MACH_GORAMO_MLR)	+= goramo_mlr.o
<<<<<<< HEAD
obj-$(CONFIG_MACH_ARCOM_VULCAN)	+= vulcan-setup.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

obj-$(CONFIG_PCI)		+= $(obj-pci-$(CONFIG_PCI)) common-pci.o
