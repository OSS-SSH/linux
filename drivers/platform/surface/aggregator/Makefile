# SPDX-License-Identifier: GPL-2.0+
# Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>

# For include/trace/define_trace.h to include trace.h
CFLAGS_core.o = -I$(src)

obj-$(CONFIG_SURFACE_AGGREGATOR) += surface_aggregator.o

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
surface_aggregator-y := core.o
surface_aggregator-y += ssh_parser.o
surface_aggregator-y += ssh_packet_layer.o
surface_aggregator-y += ssh_request_layer.o
surface_aggregator-$(CONFIG_SURFACE_AGGREGATOR_BUS) += bus.o
surface_aggregator-y += controller.o
<<<<<<< HEAD
=======
surface_aggregator-objs := core.o
surface_aggregator-objs += ssh_parser.o
surface_aggregator-objs += ssh_packet_layer.o
surface_aggregator-objs += ssh_request_layer.o
surface_aggregator-objs += controller.o

ifeq ($(CONFIG_SURFACE_AGGREGATOR_BUS),y)
surface_aggregator-objs += bus.o
endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
