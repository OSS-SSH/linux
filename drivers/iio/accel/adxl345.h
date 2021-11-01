/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * ADXL345 3-Axis Digital Accelerometer
 *
 * Copyright (c) 2017 Eva Rachel Retuya <eraretuya@gmail.com>
 */

#ifndef _ADXL345_H_
#define _ADXL345_H_

enum adxl345_device_type {
	ADXL345,
	ADXL375,
};

int adxl345_core_probe(struct device *dev, struct regmap *regmap,
		       enum adxl345_device_type type, const char *name);
<<<<<<< HEAD
<<<<<<< HEAD
=======
int adxl345_core_remove(struct device *dev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* _ADXL345_H_ */
