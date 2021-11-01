/* SPDX-License-Identifier: GPL-2.0 */
#ifndef ASM_VDSO_GETTIMEOFDAY_H
#define ASM_VDSO_GETTIMEOFDAY_H

#define VDSO_HAS_TIME 1

#define VDSO_HAS_CLOCK_GETRES 1

<<<<<<< HEAD
<<<<<<< HEAD
#include <asm/syscall.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <asm/syscall.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <asm/timex.h>
#include <asm/unistd.h>
#include <linux/compiler.h>

#define vdso_calc_delta __arch_vdso_calc_delta
static __always_inline u64 __arch_vdso_calc_delta(u64 cycles, u64 last, u64 mask, u32 mult)
{
	return (cycles - last) * mult;
}

static __always_inline const struct vdso_data *__arch_get_vdso_data(void)
{
	return _vdso_data;
}

static inline u64 __arch_get_hw_counter(s32 clock_mode, const struct vdso_data *vd)
{
	u64 adj, now;

	now = get_tod_clock();
	adj = vd->arch_data.tod_steering_end - now;
	if (unlikely((s64) adj > 0))
		now += (vd->arch_data.tod_steering_delta < 0) ? (adj >> 15) : -(adj >> 15);
	return now;
}

static __always_inline
long clock_gettime_fallback(clockid_t clkid, struct __kernel_timespec *ts)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return syscall2(__NR_clock_gettime, (long)clkid, (long)ts);
=======
	register unsigned long r1 __asm__("r1") = __NR_clock_gettime;
	register unsigned long r2 __asm__("r2") = (unsigned long)clkid;
	register void *r3 __asm__("r3") = ts;

	asm ("svc 0\n" : "+d" (r2) : "d" (r1), "d" (r3) : "cc", "memory");
	return r2;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return syscall2(__NR_clock_gettime, (long)clkid, (long)ts);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static __always_inline
long gettimeofday_fallback(register struct __kernel_old_timeval *tv,
			   register struct timezone *tz)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return syscall2(__NR_gettimeofday, (long)tv, (long)tz);
=======
	register unsigned long r1 __asm__("r1") = __NR_gettimeofday;
	register unsigned long r2 __asm__("r2") = (unsigned long)tv;
	register void *r3 __asm__("r3") = tz;

	asm ("svc 0\n" : "+d" (r2) : "d" (r1), "d" (r3) : "cc", "memory");
	return r2;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return syscall2(__NR_gettimeofday, (long)tv, (long)tz);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static __always_inline
long clock_getres_fallback(clockid_t clkid, struct __kernel_timespec *ts)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return syscall2(__NR_clock_getres, (long)clkid, (long)ts);
=======
	register unsigned long r1 __asm__("r1") = __NR_clock_getres;
	register unsigned long r2 __asm__("r2") = (unsigned long)clkid;
	register void *r3 __asm__("r3") = ts;

	asm ("svc 0\n" : "+d" (r2) : "d" (r1), "d" (r3) : "cc", "memory");
	return r2;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return syscall2(__NR_clock_getres, (long)clkid, (long)ts);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

#ifdef CONFIG_TIME_NS
static __always_inline
const struct vdso_data *__arch_get_timens_vdso_data(const struct vdso_data *vd)
{
	return _timens_data;
}
#endif

#endif
