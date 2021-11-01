/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __PERF_EVLIST_HYBRID_H
#define __PERF_EVLIST_HYBRID_H

#include <linux/compiler.h>
#include <linux/kernel.h>
#include "evlist.h"
#include <unistd.h>

int evlist__add_default_hybrid(struct evlist *evlist, bool precise);
void evlist__warn_hybrid_group(struct evlist *evlist);
bool evlist__has_hybrid(struct evlist *evlist);
<<<<<<< HEAD
int evlist__fix_hybrid_cpus(struct evlist *evlist, const char *cpu_list);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

#endif /* __PERF_EVLIST_HYBRID_H */
