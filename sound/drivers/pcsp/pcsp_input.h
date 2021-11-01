/* SPDX-License-Identifier: GPL-2.0 */
/*
 * PC-Speaker driver for Linux
 *
 * Copyright (C) 2001-2008  Stas Sergeev
 */

#ifndef __PCSP_INPUT_H__
#define __PCSP_INPUT_H__

int pcspkr_input_init(struct input_dev **rdev, struct device *dev);
<<<<<<< HEAD
=======
int pcspkr_input_remove(struct input_dev *dev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
void pcspkr_stop_sound(void);

#endif
