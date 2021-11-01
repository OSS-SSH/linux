/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_IOCTL_H__
#define __NVKM_IOCTL_H__
#include <core/os.h>
struct nvkm_client;

<<<<<<< HEAD
<<<<<<< HEAD
int nvkm_ioctl(struct nvkm_client *, void *, u32, void **);
=======
int nvkm_ioctl(struct nvkm_client *, bool, void *, u32, void **);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
int nvkm_ioctl(struct nvkm_client *, void *, u32, void **);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif
