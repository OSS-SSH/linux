# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the Linux unix domain socket layer.
#

obj-$(CONFIG_UNIX)	+= unix.o

unix-y			:= af_unix.o garbage.o
unix-$(CONFIG_SYSCTL)	+= sysctl_net_unix.o
<<<<<<< HEAD
<<<<<<< HEAD
unix-$(CONFIG_BPF_SYSCALL) += unix_bpf.o
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
unix-$(CONFIG_BPF_SYSCALL) += unix_bpf.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

obj-$(CONFIG_UNIX_DIAG)	+= unix_diag.o
unix_diag-y		:= diag.o

obj-$(CONFIG_UNIX_SCM)	+= scm.o
