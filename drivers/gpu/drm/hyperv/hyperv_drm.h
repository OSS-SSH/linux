/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright 2021 Microsoft
 */

#ifndef _HYPERV_DRM_H_
#define _HYPERV_DRM_H_

#define VMBUS_MAX_PACKET_SIZE 0x4000

struct hyperv_drm_device {
	/* drm */
	struct drm_device dev;
	struct drm_simple_display_pipe pipe;
	struct drm_connector connector;

	/* mode */
	u32 screen_width_max;
	u32 screen_height_max;
	u32 preferred_width;
	u32 preferred_height;
	u32 screen_depth;

	/* hw */
	struct resource *mem;
	void __iomem *vram;
	unsigned long fb_base;
	unsigned long fb_size;
	struct completion wait;
	u32 synthvid_version;
	u32 mmio_megabytes;
	bool dirt_needed;

	u8 init_buf[VMBUS_MAX_PACKET_SIZE];
	u8 recv_buf[VMBUS_MAX_PACKET_SIZE];

	struct hv_device *hdev;
};

#define to_hv(_dev) container_of(_dev, struct hyperv_drm_device, dev)

/* hyperv_drm_modeset */
int hyperv_mode_config_init(struct hyperv_drm_device *hv);

/* hyperv_drm_proto */
int hyperv_update_vram_location(struct hv_device *hdev, phys_addr_t vram_pp);
int hyperv_update_situation(struct hv_device *hdev, u8 active, u32 bpp,
			    u32 w, u32 h, u32 pitch);
<<<<<<< HEAD
<<<<<<< HEAD
int hyperv_hide_hw_ptr(struct hv_device *hdev);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
int hyperv_hide_hw_ptr(struct hv_device *hdev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int hyperv_update_dirt(struct hv_device *hdev, struct drm_rect *rect);
int hyperv_connect_vsp(struct hv_device *hdev);

#endif
