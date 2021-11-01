/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __SAMPLE_RAW_H
#define __SAMPLE_RAW_H 1

struct evlist;
union perf_event;
struct perf_sample;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void evlist__s390_sample_raw(struct evlist *evlist, union perf_event *event,
			     struct perf_sample *sample);
bool evlist__has_amd_ibs(struct evlist *evlist);
void evlist__amd_sample_raw(struct evlist *evlist, union perf_event *event,
			    struct perf_sample *sample);
<<<<<<< HEAD
=======
void evlist__s390_sample_raw(struct evlist *evlist, union perf_event *event, struct perf_sample *sample);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void evlist__init_trace_event_sample_raw(struct evlist *evlist);
#endif /* __PERF_EVLIST_H */
