// SPDX-License-Identifier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#include "log.h"
#include "main.h"

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/stdarg.h>
=======
#include <stdarg.h>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <linux/stdarg.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#include "trace.h"

/**
 * batadv_debug_log() - Add debug log entry
 * @bat_priv: the bat priv with all the soft interface information
 * @fmt: format string
 *
 * Return: 0 on success or negative error number in case of failure
 */
int batadv_debug_log(struct batadv_priv *bat_priv, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	trace_batadv_dbg(bat_priv, &vaf);

	va_end(args);

	return 0;
}
