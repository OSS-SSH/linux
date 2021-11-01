# SPDX-License-Identifier: GPL-2.0-only
#
# Kernel Makefile for the libsas helpers
#
# Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
# Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
#

obj-$(CONFIG_SCSI_SAS_LIBSAS) += libsas.o
libsas-y +=  sas_init.o     \
		sas_phy.o      \
		sas_port.o     \
		sas_event.o    \
		sas_discover.o \
		sas_expander.o \
		sas_scsi_host.o \
		sas_task.o
libsas-$(CONFIG_SCSI_SAS_ATA) +=	sas_ata.o
libsas-$(CONFIG_SCSI_SAS_HOST_SMP) +=	sas_host_smp.o

<<<<<<< HEAD
<<<<<<< HEAD
ccflags-y := -DDEBUG -I$(srctree)/drivers/scsi
=======
ccflags-y := -DDEBUG
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
ccflags-y := -DDEBUG -I$(srctree)/drivers/scsi
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
