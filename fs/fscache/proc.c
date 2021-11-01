// SPDX-License-Identifier: GPL-2.0-or-later
/* FS-Cache statistics viewing interface
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#define FSCACHE_DEBUG_LEVEL OPERATION
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include "internal.h"

/*
 * initialise the /proc/fs/fscache/ directory
 */
int __init fscache_proc_init(void)
{
	_enter("");

	if (!proc_mkdir("fs/fscache", NULL))
		goto error_dir;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (!proc_create_seq("fs/fscache/cookies", S_IFREG | 0444, NULL,
			     &fscache_cookies_seq_ops))
		goto error_cookies;

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#ifdef CONFIG_FSCACHE_STATS
	if (!proc_create_single("fs/fscache/stats", S_IFREG | 0444, NULL,
			fscache_stats_show))
		goto error_stats;
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======
#ifdef CONFIG_FSCACHE_HISTOGRAM
	if (!proc_create_seq("fs/fscache/histogram", S_IFREG | 0444, NULL,
			 &fscache_histogram_ops))
		goto error_histogram;
#endif

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#ifdef CONFIG_FSCACHE_OBJECT_LIST
	if (!proc_create("fs/fscache/objects", S_IFREG | 0444, NULL,
			 &fscache_objlist_proc_ops))
		goto error_objects;
#endif

	_leave(" = 0");
	return 0;

#ifdef CONFIG_FSCACHE_OBJECT_LIST
error_objects:
#endif
<<<<<<< HEAD
<<<<<<< HEAD
=======
#ifdef CONFIG_FSCACHE_HISTOGRAM
	remove_proc_entry("fs/fscache/histogram", NULL);
error_histogram:
#endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#ifdef CONFIG_FSCACHE_STATS
	remove_proc_entry("fs/fscache/stats", NULL);
error_stats:
#endif
<<<<<<< HEAD
<<<<<<< HEAD
	remove_proc_entry("fs/fscache/cookies", NULL);
error_cookies:
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	remove_proc_entry("fs/fscache/cookies", NULL);
error_cookies:
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	remove_proc_entry("fs/fscache", NULL);
error_dir:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}

/*
 * clean up the /proc/fs/fscache/ directory
 */
void fscache_proc_cleanup(void)
{
#ifdef CONFIG_FSCACHE_OBJECT_LIST
	remove_proc_entry("fs/fscache/objects", NULL);
#endif
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_FSCACHE_STATS
	remove_proc_entry("fs/fscache/stats", NULL);
#endif
	remove_proc_entry("fs/fscache/cookies", NULL);
=======
#ifdef CONFIG_FSCACHE_HISTOGRAM
	remove_proc_entry("fs/fscache/histogram", NULL);
#endif
#ifdef CONFIG_FSCACHE_STATS
	remove_proc_entry("fs/fscache/stats", NULL);
#endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifdef CONFIG_FSCACHE_STATS
	remove_proc_entry("fs/fscache/stats", NULL);
#endif
	remove_proc_entry("fs/fscache/cookies", NULL);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	remove_proc_entry("fs/fscache", NULL);
}
