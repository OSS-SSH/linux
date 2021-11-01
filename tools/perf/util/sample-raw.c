/* SPDX-License-Identifier: GPL-2.0 */

#include <string.h>
<<<<<<< HEAD
#include <linux/string.h>
#include "evlist.h"
#include "env.h"
#include "header.h"
=======
#include "evlist.h"
#include "env.h"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#include "sample-raw.h"

/*
 * Check platform the perf data file was created on and perform platform
 * specific interpretation.
 */
void evlist__init_trace_event_sample_raw(struct evlist *evlist)
{
	const char *arch_pf = perf_env__arch(evlist->env);
<<<<<<< HEAD
	const char *cpuid = perf_env__cpuid(evlist->env);

	if (arch_pf && !strcmp("s390", arch_pf))
		evlist->trace_event_sample_raw = evlist__s390_sample_raw;
	else if (arch_pf && !strcmp("x86", arch_pf) &&
		 cpuid && strstarts(cpuid, "AuthenticAMD") &&
		 evlist__has_amd_ibs(evlist)) {
		evlist->trace_event_sample_raw = evlist__amd_sample_raw;
	}
=======

	if (arch_pf && !strcmp("s390", arch_pf))
		evlist->trace_event_sample_raw = evlist__s390_sample_raw;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
