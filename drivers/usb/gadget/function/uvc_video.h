/* SPDX-License-Identifier: GPL-2.0 */
/*
 *	uvc_video.h  --  USB Video Class Gadget driver
 *
 * Copyright (C) 2009-2010
 *		Laurent Pinchart (laurent.pinchart@ideasonboard.com)
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *		Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */
#ifndef __UVC_VIDEO_H__
#define __UVC_VIDEO_H__

<<<<<<< HEAD
<<<<<<< HEAD
#define UVCG_REQUEST_HEADER_LEN			2

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define UVCG_REQUEST_HEADER_LEN			2

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
struct uvc_video;

int uvcg_video_enable(struct uvc_video *video, int enable);

int uvcg_video_init(struct uvc_video *video, struct uvc_device *uvc);

#endif /* __UVC_VIDEO_H__ */
