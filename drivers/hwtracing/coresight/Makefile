# SPDX-License-Identifier: GPL-2.0
#
# Makefile for CoreSight drivers.
#
obj-$(CONFIG_CORESIGHT) += coresight.o
coresight-y := coresight-core.o  coresight-etm-perf.o coresight-platform.o \
<<<<<<< HEAD
<<<<<<< HEAD
		coresight-sysfs.o coresight-syscfg.o coresight-config.o \
		coresight-cfg-preload.o coresight-cfg-afdo.o \
		coresight-syscfg-configfs.o
=======
		coresight-sysfs.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		coresight-sysfs.o coresight-syscfg.o coresight-config.o \
		coresight-cfg-preload.o coresight-cfg-afdo.o \
		coresight-syscfg-configfs.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
obj-$(CONFIG_CORESIGHT_LINK_AND_SINK_TMC) += coresight-tmc.o
coresight-tmc-y := coresight-tmc-core.o coresight-tmc-etf.o \
		      coresight-tmc-etr.o
obj-$(CONFIG_CORESIGHT_SINK_TPIU) += coresight-tpiu.o
obj-$(CONFIG_CORESIGHT_SINK_ETBV10) += coresight-etb10.o
obj-$(CONFIG_CORESIGHT_LINKS_AND_SINKS) += coresight-funnel.o \
					   coresight-replicator.o
obj-$(CONFIG_CORESIGHT_SOURCE_ETM3X) += coresight-etm3x.o
coresight-etm3x-y := coresight-etm3x-core.o coresight-etm-cp14.o \
		     coresight-etm3x-sysfs.o
obj-$(CONFIG_CORESIGHT_SOURCE_ETM4X) += coresight-etm4x.o
<<<<<<< HEAD
<<<<<<< HEAD
coresight-etm4x-y := coresight-etm4x-core.o coresight-etm4x-sysfs.o \
			coresight-etm4x-cfg.o
=======
coresight-etm4x-y := coresight-etm4x-core.o coresight-etm4x-sysfs.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
coresight-etm4x-y := coresight-etm4x-core.o coresight-etm4x-sysfs.o \
			coresight-etm4x-cfg.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
obj-$(CONFIG_CORESIGHT_STM) += coresight-stm.o
obj-$(CONFIG_CORESIGHT_CPU_DEBUG) += coresight-cpu-debug.o
obj-$(CONFIG_CORESIGHT_CATU) += coresight-catu.o
obj-$(CONFIG_CORESIGHT_CTI) += coresight-cti.o
obj-$(CONFIG_CORESIGHT_TRBE) += coresight-trbe.o
coresight-cti-y := coresight-cti-core.o	coresight-cti-platform.o \
		   coresight-cti-sysfs.o
