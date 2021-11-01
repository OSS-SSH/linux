# SPDX-License-Identifier: GPL-2.0
ccflags-$(CONFIG_DRM_TEGRA_DEBUG) += -DDEBUG

tegra-drm-y := \
	drm.o \
<<<<<<< HEAD
	uapi.o \
	submit.o \
	firewall.o \
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	gem.o \
	fb.o \
	dp.o \
	hub.o \
	plane.o \
	dc.o \
	output.o \
	rgb.o \
	hda.o \
	hdmi.o \
	mipi-phy.o \
	dsi.o \
	sor.o \
	dpaux.o \
	gr2d.o \
	gr3d.o \
	falcon.o \
	vic.o

tegra-drm-y += trace.o

obj-$(CONFIG_DRM_TEGRA) += tegra-drm.o
