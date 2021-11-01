# SPDX-License-Identifier: GPL-2.0
#
<<<<<<< HEAD
<<<<<<< HEAD
# Makefile for Marvell's RVU Ethernet device drivers
=======
# Makefile for Marvell's OcteonTX2 ethernet device drivers
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
# Makefile for Marvell's RVU Ethernet device drivers
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#

obj-$(CONFIG_OCTEONTX2_PF) += rvu_nicpf.o
obj-$(CONFIG_OCTEONTX2_VF) += rvu_nicvf.o

rvu_nicpf-y := otx2_pf.o otx2_common.o otx2_txrx.o otx2_ethtool.o \
<<<<<<< HEAD
<<<<<<< HEAD
               otx2_ptp.o otx2_flows.o otx2_tc.o cn10k.o otx2_dmac_flt.o \
               otx2_devlink.o
rvu_nicvf-y := otx2_vf.o otx2_devlink.o
=======
		     otx2_ptp.o otx2_flows.o otx2_tc.o cn10k.o
rvu_nicvf-y := otx2_vf.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
               otx2_ptp.o otx2_flows.o otx2_tc.o cn10k.o otx2_dmac_flt.o \
               otx2_devlink.o
rvu_nicvf-y := otx2_vf.o otx2_devlink.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

ccflags-y += -I$(srctree)/drivers/net/ethernet/marvell/octeontx2/af
