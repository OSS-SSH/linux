# SPDX-License-Identifier: GPL-2.0-only
obj-y := dma-buf.o dma-fence.o dma-fence-array.o dma-fence-chain.o \
	 dma-resv.o seqno-fence.o
obj-$(CONFIG_DMABUF_HEAPS)	+= dma-heap.o
obj-$(CONFIG_DMABUF_HEAPS)	+= heaps/
obj-$(CONFIG_SYNC_FILE)		+= sync_file.o
obj-$(CONFIG_SW_SYNC)		+= sw_sync.o sync_debug.o
obj-$(CONFIG_UDMABUF)		+= udmabuf.o
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_DMABUF_SYSFS_STATS) += dma-buf-sysfs-stats.o
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
obj-$(CONFIG_DMABUF_SYSFS_STATS) += dma-buf-sysfs-stats.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

dmabuf_selftests-y := \
	selftest.o \
	st-dma-fence.o \
	st-dma-fence-chain.o

obj-$(CONFIG_DMABUF_SELFTESTS)	+= dmabuf_selftests.o
