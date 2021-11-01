/* SPDX-License-Identifier: GPL-2.0 */

#ifndef selftest
#define selftest(x, y)
#endif

/*
 * List each unit test as selftest(name, function)
 *
 * The name is used as both an enum and expanded as subtest__name to create
 * a module parameter. It must be unique and legal for a C identifier.
 *
 * The function should be of type int function(void). It may be conditionally
 * compiled using #if IS_ENABLED(CONFIG_DRM_I915_SELFTEST).
 *
 * Tests are executed in order by igt/i915_selftest
 */
selftest(engine_cs, intel_engine_cs_perf_selftests)
selftest(request, i915_request_perf_selftests)
<<<<<<< HEAD
<<<<<<< HEAD
selftest(migrate, intel_migrate_perf_selftests)
=======
selftest(blt, i915_gem_object_blt_perf_selftests)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
selftest(migrate, intel_migrate_perf_selftests)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
selftest(region, intel_memory_region_perf_selftests)
