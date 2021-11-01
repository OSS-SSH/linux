// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2013  Davidlohr Bueso <davidlohr@hp.com>
 *
 * futex-hash: Stress the hell out of the Linux kernel futex uaddr hashing.
 *
 * This program is particularly useful for measuring the kernel's futex hash
 * table/function implementation. In order for it to make sense, use with as
 * many threads and futexes as possible.
 */

/* For the CLR_() macros */
#include <string.h>
#include <pthread.h>

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <linux/zalloc.h>
#include <sys/time.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <sys/mman.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <sys/mman.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <perf/cpumap.h>

#include "../util/stat.h"
#include <subcmd/parse-options.h>
#include "bench.h"
#include "futex.h"

#include <err.h>

<<<<<<< HEAD
<<<<<<< HEAD
static bool done = false;
=======
static unsigned int nthreads = 0;
static unsigned int nsecs    = 10;
/* amount of futexes per thread */
static unsigned int nfutexes = 1024;
static bool fshared = false, done = false, silent = false;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static bool done = false;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int futex_flag = 0;

struct timeval bench__start, bench__end, bench__runtime;
static pthread_mutex_t thread_lock;
static unsigned int threads_starting;
static struct stats throughput_stats;
static pthread_cond_t thread_parent, thread_worker;

struct worker {
	int tid;
	u_int32_t *futex;
	pthread_t thread;
	unsigned long ops;
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static struct bench_futex_parameters params = {
	.nfutexes = 1024,
	.runtime  = 10,
};

<<<<<<< HEAD
static const struct option options[] = {
	OPT_UINTEGER('t', "threads", &params.nthreads, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &params.runtime, "Specify runtime (in seconds)"),
	OPT_UINTEGER('f', "futexes", &params.nfutexes, "Specify amount of futexes per threads"),
	OPT_BOOLEAN( 's', "silent",  &params.silent, "Silent mode: do not display data/details"),
	OPT_BOOLEAN( 'S', "shared",  &params.fshared, "Use shared futexes instead of private ones"),
	OPT_BOOLEAN( 'm', "mlockall", &params.mlockall, "Lock all current and future memory"),
=======
static const struct option options[] = {
	OPT_UINTEGER('t', "threads", &nthreads, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &nsecs,    "Specify runtime (in seconds)"),
	OPT_UINTEGER('f', "futexes", &nfutexes, "Specify amount of futexes per threads"),
	OPT_BOOLEAN( 's', "silent",  &silent,   "Silent mode: do not display data/details"),
	OPT_BOOLEAN( 'S', "shared",  &fshared,  "Use shared futexes instead of private ones"),
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static const struct option options[] = {
	OPT_UINTEGER('t', "threads", &params.nthreads, "Specify amount of threads"),
	OPT_UINTEGER('r', "runtime", &params.runtime, "Specify runtime (in seconds)"),
	OPT_UINTEGER('f', "futexes", &params.nfutexes, "Specify amount of futexes per threads"),
	OPT_BOOLEAN( 's', "silent",  &params.silent, "Silent mode: do not display data/details"),
	OPT_BOOLEAN( 'S', "shared",  &params.fshared, "Use shared futexes instead of private ones"),
	OPT_BOOLEAN( 'm', "mlockall", &params.mlockall, "Lock all current and future memory"),
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	OPT_END()
};

static const char * const bench_futex_hash_usage[] = {
	"perf bench futex hash <options>",
	NULL
};

static void *workerfn(void *arg)
{
	int ret;
	struct worker *w = (struct worker *) arg;
	unsigned int i;
	unsigned long ops = w->ops; /* avoid cacheline bouncing */

	pthread_mutex_lock(&thread_lock);
	threads_starting--;
	if (!threads_starting)
		pthread_cond_signal(&thread_parent);
	pthread_cond_wait(&thread_worker, &thread_lock);
	pthread_mutex_unlock(&thread_lock);

	do {
<<<<<<< HEAD
<<<<<<< HEAD
		for (i = 0; i < params.nfutexes; i++, ops++) {
=======
		for (i = 0; i < nfutexes; i++, ops++) {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		for (i = 0; i < params.nfutexes; i++, ops++) {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			/*
			 * We want the futex calls to fail in order to stress
			 * the hashing of uaddr and not measure other steps,
			 * such as internal waitqueue handling, thus enlarging
			 * the critical region protected by hb->lock.
			 */
			ret = futex_wait(&w->futex[i], 1234, NULL, futex_flag);
<<<<<<< HEAD
<<<<<<< HEAD
			if (!params.silent &&
=======
			if (!silent &&
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
			if (!params.silent &&
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			    (!ret || errno != EAGAIN || errno != EWOULDBLOCK))
				warn("Non-expected futex return call");
		}
	}  while (!done);

	w->ops = ops;
	return NULL;
}

static void toggle_done(int sig __maybe_unused,
			siginfo_t *info __maybe_unused,
			void *uc __maybe_unused)
{
	/* inform all threads that we're done for the day */
	done = true;
	gettimeofday(&bench__end, NULL);
	timersub(&bench__end, &bench__start, &bench__runtime);
}

static void print_summary(void)
{
	unsigned long avg = avg_stats(&throughput_stats);
	double stddev = stddev_stats(&throughput_stats);

	printf("%sAveraged %ld operations/sec (+- %.2f%%), total secs = %d\n",
<<<<<<< HEAD
<<<<<<< HEAD
	       !params.silent ? "\n" : "", avg, rel_stddev_stats(stddev, avg),
=======
	       !silent ? "\n" : "", avg, rel_stddev_stats(stddev, avg),
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	       !params.silent ? "\n" : "", avg, rel_stddev_stats(stddev, avg),
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	       (int)bench__runtime.tv_sec);
}

int bench_futex_hash(int argc, const char **argv)
{
	int ret = 0;
	cpu_set_t cpuset;
	struct sigaction act;
	unsigned int i;
	pthread_attr_t thread_attr;
	struct worker *worker = NULL;
	struct perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_hash_usage, 0);
	if (argc) {
		usage_with_options(bench_futex_hash_usage, options);
		exit(EXIT_FAILURE);
	}

	cpu = perf_cpu_map__new(NULL);
	if (!cpu)
		goto errmem;

	memset(&act, 0, sizeof(act));
	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_done;
	sigaction(SIGINT, &act, NULL);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (params.mlockall) {
		if (mlockall(MCL_CURRENT | MCL_FUTURE))
			err(EXIT_FAILURE, "mlockall");
	}

	if (!params.nthreads) /* default to the number of CPUs */
		params.nthreads = cpu->nr;
<<<<<<< HEAD

	worker = calloc(params.nthreads, sizeof(*worker));
	if (!worker)
		goto errmem;

	if (!params.fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	printf("Run summary [PID %d]: %d threads, each operating on %d [%s] futexes for %d secs.\n\n",
	       getpid(), params.nthreads, params.nfutexes, params.fshared ? "shared":"private", params.runtime);
=======
	if (!nthreads) /* default to the number of CPUs */
		nthreads = cpu->nr;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	worker = calloc(params.nthreads, sizeof(*worker));
	if (!worker)
		goto errmem;

	if (!params.fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	printf("Run summary [PID %d]: %d threads, each operating on %d [%s] futexes for %d secs.\n\n",
<<<<<<< HEAD
	       getpid(), nthreads, nfutexes, fshared ? "shared":"private", nsecs);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	       getpid(), params.nthreads, params.nfutexes, params.fshared ? "shared":"private", params.runtime);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	init_stats(&throughput_stats);
	pthread_mutex_init(&thread_lock, NULL);
	pthread_cond_init(&thread_parent, NULL);
	pthread_cond_init(&thread_worker, NULL);

<<<<<<< HEAD
<<<<<<< HEAD
	threads_starting = params.nthreads;
	pthread_attr_init(&thread_attr);
	gettimeofday(&bench__start, NULL);
	for (i = 0; i < params.nthreads; i++) {
		worker[i].tid = i;
		worker[i].futex = calloc(params.nfutexes, sizeof(*worker[i].futex));
=======
	threads_starting = nthreads;
=======
	threads_starting = params.nthreads;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	pthread_attr_init(&thread_attr);
	gettimeofday(&bench__start, NULL);
	for (i = 0; i < params.nthreads; i++) {
		worker[i].tid = i;
<<<<<<< HEAD
		worker[i].futex = calloc(nfutexes, sizeof(*worker[i].futex));
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		worker[i].futex = calloc(params.nfutexes, sizeof(*worker[i].futex));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (!worker[i].futex)
			goto errmem;

		CPU_ZERO(&cpuset);
		CPU_SET(cpu->map[i % cpu->nr], &cpuset);

		ret = pthread_attr_setaffinity_np(&thread_attr, sizeof(cpu_set_t), &cpuset);
		if (ret)
			err(EXIT_FAILURE, "pthread_attr_setaffinity_np");

		ret = pthread_create(&worker[i].thread, &thread_attr, workerfn,
				     (void *)(struct worker *) &worker[i]);
		if (ret)
			err(EXIT_FAILURE, "pthread_create");

	}
	pthread_attr_destroy(&thread_attr);

	pthread_mutex_lock(&thread_lock);
	while (threads_starting)
		pthread_cond_wait(&thread_parent, &thread_lock);
	pthread_cond_broadcast(&thread_worker);
	pthread_mutex_unlock(&thread_lock);

<<<<<<< HEAD
<<<<<<< HEAD
	sleep(params.runtime);
	toggle_done(0, NULL, NULL);

	for (i = 0; i < params.nthreads; i++) {
=======
	sleep(nsecs);
	toggle_done(0, NULL, NULL);

	for (i = 0; i < nthreads; i++) {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	sleep(params.runtime);
	toggle_done(0, NULL, NULL);

	for (i = 0; i < params.nthreads; i++) {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		ret = pthread_join(worker[i].thread, NULL);
		if (ret)
			err(EXIT_FAILURE, "pthread_join");
	}

	/* cleanup & report results */
	pthread_cond_destroy(&thread_parent);
	pthread_cond_destroy(&thread_worker);
	pthread_mutex_destroy(&thread_lock);

<<<<<<< HEAD
<<<<<<< HEAD
	for (i = 0; i < params.nthreads; i++) {
		unsigned long t = bench__runtime.tv_sec > 0 ?
			worker[i].ops / bench__runtime.tv_sec : 0;
		update_stats(&throughput_stats, t);
		if (!params.silent) {
			if (params.nfutexes == 1)
=======
	for (i = 0; i < nthreads; i++) {
		unsigned long t = bench__runtime.tv_sec > 0 ?
			worker[i].ops / bench__runtime.tv_sec : 0;
		update_stats(&throughput_stats, t);
		if (!silent) {
			if (nfutexes == 1)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	for (i = 0; i < params.nthreads; i++) {
		unsigned long t = bench__runtime.tv_sec > 0 ?
			worker[i].ops / bench__runtime.tv_sec : 0;
		update_stats(&throughput_stats, t);
		if (!params.silent) {
			if (params.nfutexes == 1)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
				printf("[thread %2d] futex: %p [ %ld ops/sec ]\n",
				       worker[i].tid, &worker[i].futex[0], t);
			else
				printf("[thread %2d] futexes: %p ... %p [ %ld ops/sec ]\n",
				       worker[i].tid, &worker[i].futex[0],
<<<<<<< HEAD
<<<<<<< HEAD
				       &worker[i].futex[params.nfutexes-1], t);
=======
				       &worker[i].futex[nfutexes-1], t);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
				       &worker[i].futex[params.nfutexes-1], t);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		}

		zfree(&worker[i].futex);
	}

	print_summary();

	free(worker);
	free(cpu);
	return ret;
errmem:
	err(EXIT_FAILURE, "calloc");
}
