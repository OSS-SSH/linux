# SPDX-License-Identifier: GPL-2.0
#
# Makefile for general filesystem caching code
#

fscache-y := \
	cache.o \
	cookie.o \
	fsdef.o \
	io.o \
	main.o \
	netfs.o \
	object.o \
	operation.o \
	page.o

fscache-$(CONFIG_PROC_FS) += proc.o
fscache-$(CONFIG_FSCACHE_STATS) += stats.o
<<<<<<< HEAD
<<<<<<< HEAD
=======
fscache-$(CONFIG_FSCACHE_HISTOGRAM) += histogram.o
fscache-$(CONFIG_FSCACHE_OBJECT_LIST) += object-list.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

obj-$(CONFIG_FSCACHE) := fscache.o
