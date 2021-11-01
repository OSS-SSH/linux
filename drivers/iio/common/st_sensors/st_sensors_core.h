/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Local functions in the ST Sensors core
 */
#ifndef __ST_SENSORS_CORE_H
#define __ST_SENSORS_CORE_H
<<<<<<< HEAD
struct iio_dev;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
int st_sensors_write_data_with_mask(struct iio_dev *indio_dev,
				    u8 reg_addr, u8 mask, u8 data);
#endif
