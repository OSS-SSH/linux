# SPDX-License-Identifier: GPL-2.0
#
# Makefile for loongson based machines.
#

obj-y += setup.o init.o env.o time.o reset.o irq.o \
<<<<<<< HEAD
<<<<<<< HEAD
    bonito-irq.o mem.o machtype.o platform.o
=======
    bonito-irq.o mem.o machtype.o platform.o serial.o
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
    bonito-irq.o mem.o machtype.o platform.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
obj-$(CONFIG_PCI) += pci.o

#
# Serial port support
#
<<<<<<< HEAD
<<<<<<< HEAD
obj-$(CONFIG_LOONGSON_UART_BASE) += serial.o
obj-$(CONFIG_EARLY_PRINTK) += serial.o
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
obj-$(CONFIG_LOONGSON_UART_BASE) += serial.o
obj-$(CONFIG_EARLY_PRINTK) += serial.o
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
obj-$(CONFIG_LOONGSON_UART_BASE) += uart_base.o
obj-$(CONFIG_LOONGSON_MC146818) += rtc.o

#
# Enable CS5536 Virtual Support Module(VSM) to virtulize the PCI configure
# space
#
obj-$(CONFIG_CS5536) += cs5536/

#
# Suspend Support
#

obj-$(CONFIG_SUSPEND) += pm.o
