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
 *
 * Authors: AMD
 *
 */

#ifndef _DC_STAT_H_
#define _DC_STAT_H_

/**
 * DOC: DC STAT Interface
 *
 * These interfaces are called without acquiring DAL and DC locks.
 * Hence, there is limitations on whese interfaces can access. Only
 * variables exclusively defined for these interfaces can be modified.
 */

#include "dc.h"
#include "dmub/dmub_srv.h"

void dc_stat_get_dmub_notification(const struct dc *dc, struct dmub_notification *notify);
<<<<<<< HEAD
<<<<<<< HEAD
void dc_stat_get_dmub_dataout(const struct dc *dc, uint32_t *dataout);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void dc_stat_get_dmub_dataout(const struct dc *dc, uint32_t *dataout);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* _DC_STAT_H_ */
