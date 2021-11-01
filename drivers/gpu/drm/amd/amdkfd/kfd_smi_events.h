/*
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef KFD_SMI_EVENTS_H_INCLUDED
#define KFD_SMI_EVENTS_H_INCLUDED

int kfd_smi_event_open(struct kfd_dev *dev, uint32_t *fd);
void kfd_smi_event_update_vmfault(struct kfd_dev *dev, uint16_t pasid);
void kfd_smi_event_update_thermal_throttling(struct kfd_dev *dev,
<<<<<<< HEAD
<<<<<<< HEAD
					     uint64_t throttle_bitmask);
=======
					     uint32_t throttle_bitmask);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
					     uint64_t throttle_bitmask);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void kfd_smi_event_update_gpu_reset(struct kfd_dev *dev, bool post_reset);

#endif
