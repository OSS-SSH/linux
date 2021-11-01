// SPDX-License-Identifier: GPL-2.0
#include <opencsd/c_api/opencsd_c_api.h>

/*
 * Check OpenCSD library version is sufficient to provide required features
 */
<<<<<<< HEAD
<<<<<<< HEAD
#define OCSD_MIN_VER ((1 << 16) | (1 << 8) | (1))
#if !defined(OCSD_VER_NUM) || (OCSD_VER_NUM < OCSD_MIN_VER)
#error "OpenCSD >= 1.1.1 is required"
=======
#define OCSD_MIN_VER ((1 << 16) | (0 << 8) | (0))
#if !defined(OCSD_VER_NUM) || (OCSD_VER_NUM < OCSD_MIN_VER)
#error "OpenCSD >= 1.0.0 is required"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define OCSD_MIN_VER ((1 << 16) | (1 << 8) | (1))
#if !defined(OCSD_VER_NUM) || (OCSD_VER_NUM < OCSD_MIN_VER)
#error "OpenCSD >= 1.1.1 is required"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif

int main(void)
{
	(void)ocsd_get_version();
	return 0;
}
