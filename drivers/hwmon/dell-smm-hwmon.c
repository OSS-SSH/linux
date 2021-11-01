// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * dell-smm-hwmon.c -- Linux driver for accessing the SMM BIOS on Dell laptops.
 *
 * Copyright (C) 2001  Massimo Dal Zotto <dz@debian.org>
 *
 * Hwmon integration:
 * Copyright (C) 2011  Jean Delvare <jdelvare@suse.de>
 * Copyright (C) 2013, 2014  Guenter Roeck <linux@roeck-us.net>
 * Copyright (C) 2014, 2015  Pali Rohár <pali@kernel.org>
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpu.h>
#include <linux/delay.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/err.h>
#include <linux/module.h>
#include <linux/platform_device.h>
=======
#include <linux/module.h>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <linux/err.h>
#include <linux/module.h>
#include <linux/platform_device.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/types.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/dmi.h>
#include <linux/capability.h>
#include <linux/mutex.h>
#include <linux/hwmon.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <linux/hwmon-sysfs.h>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/sched.h>
#include <linux/ctype.h>
#include <linux/smp.h>

#include <linux/i8k.h>

#define I8K_SMM_FN_STATUS	0x0025
#define I8K_SMM_POWER_STATUS	0x0069
#define I8K_SMM_SET_FAN		0x01a3
#define I8K_SMM_GET_FAN		0x00a3
#define I8K_SMM_GET_SPEED	0x02a3
#define I8K_SMM_GET_FAN_TYPE	0x03a3
#define I8K_SMM_GET_NOM_SPEED	0x04a3
#define I8K_SMM_GET_TEMP	0x10a3
#define I8K_SMM_GET_TEMP_TYPE	0x11a3
#define I8K_SMM_GET_DELL_SIG1	0xfea3
#define I8K_SMM_GET_DELL_SIG2	0xffa3

#define I8K_FAN_MULT		30
#define I8K_FAN_MAX_RPM		30000
#define I8K_MAX_TEMP		127

#define I8K_FN_NONE		0x00
#define I8K_FN_UP		0x01
#define I8K_FN_DOWN		0x02
#define I8K_FN_MUTE		0x04
#define I8K_FN_MASK		0x07
#define I8K_FN_SHIFT		8

#define I8K_POWER_AC		0x05
#define I8K_POWER_BATTERY	0x01

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define DELL_SMM_NO_TEMP	10
#define DELL_SMM_NO_FANS	3

struct dell_smm_data {
	struct mutex i8k_mutex; /* lock for sensors writes */
	char bios_version[4];
	char bios_machineid[16];
	uint i8k_fan_mult;
	uint i8k_pwm_mult;
	uint i8k_fan_max;
	bool disallow_fan_type_call;
	bool disallow_fan_support;
	unsigned int manual_fan;
	unsigned int auto_fan;
	int temp_type[DELL_SMM_NO_TEMP];
	bool fan[DELL_SMM_NO_FANS];
	int fan_type[DELL_SMM_NO_FANS];
};
<<<<<<< HEAD
=======
static DEFINE_MUTEX(i8k_mutex);
static char bios_version[4];
static char bios_machineid[16];
static struct device *i8k_hwmon_dev;
static u32 i8k_hwmon_flags;
static uint i8k_fan_mult = I8K_FAN_MULT;
static uint i8k_pwm_mult;
static uint i8k_fan_max = I8K_FAN_HIGH;
static bool disallow_fan_type_call;
static bool disallow_fan_support;
static unsigned int manual_fan;
static unsigned int auto_fan;

#define I8K_HWMON_HAVE_TEMP1	(1 << 0)
#define I8K_HWMON_HAVE_TEMP2	(1 << 1)
#define I8K_HWMON_HAVE_TEMP3	(1 << 2)
#define I8K_HWMON_HAVE_TEMP4	(1 << 3)
#define I8K_HWMON_HAVE_TEMP5	(1 << 4)
#define I8K_HWMON_HAVE_TEMP6	(1 << 5)
#define I8K_HWMON_HAVE_TEMP7	(1 << 6)
#define I8K_HWMON_HAVE_TEMP8	(1 << 7)
#define I8K_HWMON_HAVE_TEMP9	(1 << 8)
#define I8K_HWMON_HAVE_TEMP10	(1 << 9)
#define I8K_HWMON_HAVE_FAN1	(1 << 10)
#define I8K_HWMON_HAVE_FAN2	(1 << 11)
#define I8K_HWMON_HAVE_FAN3	(1 << 12)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

MODULE_AUTHOR("Massimo Dal Zotto (dz@debian.org)");
MODULE_AUTHOR("Pali Rohár <pali@kernel.org>");
MODULE_DESCRIPTION("Dell laptop SMM BIOS hwmon driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("i8k");

static bool force;
module_param(force, bool, 0);
MODULE_PARM_DESC(force, "Force loading without checking for supported models");

static bool ignore_dmi;
module_param(ignore_dmi, bool, 0);
MODULE_PARM_DESC(ignore_dmi, "Continue probing hardware even if DMI data does not match");

#if IS_ENABLED(CONFIG_I8K)
static bool restricted = true;
module_param(restricted, bool, 0);
MODULE_PARM_DESC(restricted, "Restrict fan control and serial number to CAP_SYS_ADMIN (default: 1)");

static bool power_status;
module_param(power_status, bool, 0600);
MODULE_PARM_DESC(power_status, "Report power status in /proc/i8k (default: 0)");
#endif

static uint fan_mult;
module_param(fan_mult, uint, 0);
MODULE_PARM_DESC(fan_mult, "Factor to multiply fan speed with (default: autodetect)");

static uint fan_max;
module_param(fan_max, uint, 0);
MODULE_PARM_DESC(fan_max, "Maximum configurable fan speed (default: autodetect)");

struct smm_regs {
	unsigned int eax;
	unsigned int ebx __packed;
	unsigned int ecx __packed;
	unsigned int edx __packed;
	unsigned int esi __packed;
	unsigned int edi __packed;
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static const char * const temp_labels[] = {
	"CPU",
	"GPU",
	"SODIMM",
	"Other",
	"Ambient",
	"Other",
};

static const char * const fan_labels[] = {
	"Processor Fan",
	"Motherboard Fan",
	"Video Fan",
	"Power Supply Fan",
	"Chipset Fan",
	"Other Fan",
};

static const char * const docking_labels[] = {
	"Docking Processor Fan",
	"Docking Motherboard Fan",
	"Docking Video Fan",
	"Docking Power Supply Fan",
	"Docking Chipset Fan",
	"Docking Other Fan",
};

static inline const char __init *i8k_get_dmi_data(int field)
<<<<<<< HEAD
=======
static inline const char *i8k_get_dmi_data(int field)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	const char *dmi_data = dmi_get_system_info(field);

	return dmi_data && *dmi_data ? dmi_data : "?";
}

/*
 * Call the System Management Mode BIOS. Code provided by Jonathan Buzzard.
 */
static int i8k_smm_func(void *par)
{
<<<<<<< HEAD
<<<<<<< HEAD
	ktime_t calltime = ktime_get();
	struct smm_regs *regs = par;
	int eax = regs->eax;
	int ebx = regs->ebx;
	long long duration;
	int rc;
=======
	int rc;
=======
	ktime_t calltime = ktime_get();
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct smm_regs *regs = par;
	int eax = regs->eax;
	int ebx = regs->ebx;
<<<<<<< HEAD
	unsigned long duration;
	ktime_t calltime, delta, rettime;

	calltime = ktime_get();
#endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	long long duration;
	int rc;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* SMM requires CPU 0 */
	if (smp_processor_id() != 0)
		return -EBUSY;

#if defined(CONFIG_X86_64)
	asm volatile("pushq %%rax\n\t"
		"movl 0(%%rax),%%edx\n\t"
		"pushq %%rdx\n\t"
		"movl 4(%%rax),%%ebx\n\t"
		"movl 8(%%rax),%%ecx\n\t"
		"movl 12(%%rax),%%edx\n\t"
		"movl 16(%%rax),%%esi\n\t"
		"movl 20(%%rax),%%edi\n\t"
		"popq %%rax\n\t"
		"out %%al,$0xb2\n\t"
		"out %%al,$0x84\n\t"
		"xchgq %%rax,(%%rsp)\n\t"
		"movl %%ebx,4(%%rax)\n\t"
		"movl %%ecx,8(%%rax)\n\t"
		"movl %%edx,12(%%rax)\n\t"
		"movl %%esi,16(%%rax)\n\t"
		"movl %%edi,20(%%rax)\n\t"
		"popq %%rdx\n\t"
		"movl %%edx,0(%%rax)\n\t"
		"pushfq\n\t"
		"popq %%rax\n\t"
		"andl $1,%%eax\n"
		: "=a"(rc)
		:    "a"(regs)
		:    "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");
#else
	asm volatile("pushl %%eax\n\t"
	    "movl 0(%%eax),%%edx\n\t"
	    "push %%edx\n\t"
	    "movl 4(%%eax),%%ebx\n\t"
	    "movl 8(%%eax),%%ecx\n\t"
	    "movl 12(%%eax),%%edx\n\t"
	    "movl 16(%%eax),%%esi\n\t"
	    "movl 20(%%eax),%%edi\n\t"
	    "popl %%eax\n\t"
	    "out %%al,$0xb2\n\t"
	    "out %%al,$0x84\n\t"
	    "xchgl %%eax,(%%esp)\n\t"
	    "movl %%ebx,4(%%eax)\n\t"
	    "movl %%ecx,8(%%eax)\n\t"
	    "movl %%edx,12(%%eax)\n\t"
	    "movl %%esi,16(%%eax)\n\t"
	    "movl %%edi,20(%%eax)\n\t"
	    "popl %%edx\n\t"
	    "movl %%edx,0(%%eax)\n\t"
	    "lahf\n\t"
	    "shrl $8,%%eax\n\t"
	    "andl $1,%%eax\n"
	    : "=a"(rc)
	    :    "a"(regs)
	    :    "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");
#endif
	if (rc != 0 || (regs->eax & 0xffff) == 0xffff || regs->eax == eax)
		rc = -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
	duration = ktime_us_delta(ktime_get(), calltime);
	pr_debug("smm(0x%.4x 0x%.4x) = 0x%.4x  (took %7lld usecs)\n", eax, ebx,
		 (rc ? 0xffff : regs->eax & 0xffff), duration);
=======
#ifdef DEBUG
	rettime = ktime_get();
	delta = ktime_sub(rettime, calltime);
	duration = ktime_to_ns(delta) >> 10;
	pr_debug("smm(0x%.4x 0x%.4x) = 0x%.4x  (took %7lu usecs)\n", eax, ebx,
		(rc ? 0xffff : regs->eax & 0xffff), duration);
#endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	duration = ktime_us_delta(ktime_get(), calltime);
	pr_debug("smm(0x%.4x 0x%.4x) = 0x%.4x  (took %7lld usecs)\n", eax, ebx,
		 (rc ? 0xffff : regs->eax & 0xffff), duration);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return rc;
}

/*
 * Call the System Management Mode BIOS.
 */
static int i8k_smm(struct smm_regs *regs)
{
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	cpus_read_lock();
	ret = smp_call_on_cpu(0, i8k_smm_func, regs, true);
	cpus_read_unlock();
=======
	get_online_cpus();
	ret = smp_call_on_cpu(0, i8k_smm_func, regs, true);
	put_online_cpus();
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	cpus_read_lock();
	ret = smp_call_on_cpu(0, i8k_smm_func, regs, true);
	cpus_read_unlock();
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return ret;
}

/*
 * Read the fan status.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int i8k_get_fan_status(const struct dell_smm_data *data, int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_FAN, };

	if (data->disallow_fan_support)
=======
static int i8k_get_fan_status(int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_FAN, };

	if (disallow_fan_support)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int i8k_get_fan_status(const struct dell_smm_data *data, int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_FAN, };

	if (data->disallow_fan_support)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return -EINVAL;

	regs.ebx = fan & 0xff;
	return i8k_smm(&regs) ? : regs.eax & 0xff;
}

/*
 * Read the fan speed in RPM.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int i8k_get_fan_speed(const struct dell_smm_data *data, int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_SPEED, };

	if (data->disallow_fan_support)
		return -EINVAL;

	regs.ebx = fan & 0xff;
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * data->i8k_fan_mult;
=======
static int i8k_get_fan_speed(int fan)
=======
static int i8k_get_fan_speed(const struct dell_smm_data *data, int fan)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_SPEED, };

	if (data->disallow_fan_support)
		return -EINVAL;

	regs.ebx = fan & 0xff;
<<<<<<< HEAD
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * i8k_fan_mult;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * data->i8k_fan_mult;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

/*
 * Read the fan type.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int _i8k_get_fan_type(const struct dell_smm_data *data, int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_FAN_TYPE, };

	if (data->disallow_fan_support || data->disallow_fan_type_call)
=======
static int _i8k_get_fan_type(int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_FAN_TYPE, };

	if (disallow_fan_support || disallow_fan_type_call)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int _i8k_get_fan_type(const struct dell_smm_data *data, int fan)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_FAN_TYPE, };

	if (data->disallow_fan_support || data->disallow_fan_type_call)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return -EINVAL;

	regs.ebx = fan & 0xff;
	return i8k_smm(&regs) ? : regs.eax & 0xff;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int i8k_get_fan_type(struct dell_smm_data *data, int fan)
{
	/* I8K_SMM_GET_FAN_TYPE SMM call is expensive, so cache values */
	if (data->fan_type[fan] == INT_MIN)
		data->fan_type[fan] = _i8k_get_fan_type(data, fan);

	return data->fan_type[fan];
=======
static int i8k_get_fan_type(int fan)
=======
static int i8k_get_fan_type(struct dell_smm_data *data, int fan)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	/* I8K_SMM_GET_FAN_TYPE SMM call is expensive, so cache values */
	if (data->fan_type[fan] == INT_MIN)
		data->fan_type[fan] = _i8k_get_fan_type(data, fan);

<<<<<<< HEAD
	return types[fan];
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return data->fan_type[fan];
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

/*
 * Read the fan nominal rpm for specific fan speed.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int __init i8k_get_fan_nominal_speed(const struct dell_smm_data *data, int fan, int speed)
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_NOM_SPEED, };

	if (data->disallow_fan_support)
		return -EINVAL;

	regs.ebx = (fan & 0xff) | (speed << 8);
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * data->i8k_fan_mult;
=======
static int i8k_get_fan_nominal_speed(int fan, int speed)
=======
static int __init i8k_get_fan_nominal_speed(const struct dell_smm_data *data, int fan, int speed)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_NOM_SPEED, };

	if (data->disallow_fan_support)
		return -EINVAL;

	regs.ebx = (fan & 0xff) | (speed << 8);
<<<<<<< HEAD
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * i8k_fan_mult;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return i8k_smm(&regs) ? : (regs.eax & 0xffff) * data->i8k_fan_mult;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

/*
 * Enable or disable automatic BIOS fan control support
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int i8k_enable_fan_auto_mode(const struct dell_smm_data *data, bool enable)
{
	struct smm_regs regs = { };

	if (data->disallow_fan_support)
		return -EINVAL;

	regs.eax = enable ? data->auto_fan : data->manual_fan;
=======
static int i8k_enable_fan_auto_mode(bool enable)
=======
static int i8k_enable_fan_auto_mode(const struct dell_smm_data *data, bool enable)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct smm_regs regs = { };

	if (data->disallow_fan_support)
		return -EINVAL;

<<<<<<< HEAD
	regs.eax = enable ? auto_fan : manual_fan;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	regs.eax = enable ? data->auto_fan : data->manual_fan;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	return i8k_smm(&regs);
}

/*
 * Set the fan speed (off, low, high). Returns the new fan status.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int i8k_set_fan(const struct dell_smm_data *data, int fan, int speed)
{
	struct smm_regs regs = { .eax = I8K_SMM_SET_FAN, };

	if (data->disallow_fan_support)
		return -EINVAL;

	speed = (speed < 0) ? 0 : ((speed > data->i8k_fan_max) ? data->i8k_fan_max : speed);
	regs.ebx = (fan & 0xff) | (speed << 8);

	return i8k_smm(&regs) ? : i8k_get_fan_status(data, fan);
}

static int __init i8k_get_temp_type(int sensor)
=======
static int i8k_set_fan(int fan, int speed)
=======
static int i8k_set_fan(const struct dell_smm_data *data, int fan, int speed)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct smm_regs regs = { .eax = I8K_SMM_SET_FAN, };

	if (data->disallow_fan_support)
		return -EINVAL;

	speed = (speed < 0) ? 0 : ((speed > data->i8k_fan_max) ? data->i8k_fan_max : speed);
	regs.ebx = (fan & 0xff) | (speed << 8);

	return i8k_smm(&regs) ? : i8k_get_fan_status(data, fan);
}

<<<<<<< HEAD
static int i8k_get_temp_type(int sensor)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int __init i8k_get_temp_type(int sensor)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct smm_regs regs = { .eax = I8K_SMM_GET_TEMP_TYPE, };

	regs.ebx = sensor & 0xff;
	return i8k_smm(&regs) ? : regs.eax & 0xff;
}

/*
 * Read the cpu temperature.
 */
static int _i8k_get_temp(int sensor)
{
	struct smm_regs regs = {
		.eax = I8K_SMM_GET_TEMP,
		.ebx = sensor & 0xff,
	};

	return i8k_smm(&regs) ? : regs.eax & 0xff;
}

static int i8k_get_temp(int sensor)
{
	int temp = _i8k_get_temp(sensor);

	/*
	 * Sometimes the temperature sensor returns 0x99, which is out of range.
	 * In this case we retry (once) before returning an error.
	 # 1003655137 00000058 00005a4b
	 # 1003655138 00000099 00003a80 <--- 0x99 = 153 degrees
	 # 1003655139 00000054 00005c52
	 */
	if (temp == 0x99) {
		msleep(100);
		temp = _i8k_get_temp(sensor);
	}
	/*
	 * Return -ENODATA for all invalid temperatures.
	 *
	 * Known instances are the 0x99 value as seen above as well as
	 * 0xc1 (193), which may be returned when trying to read the GPU
	 * temperature if the system supports a GPU and it is currently
	 * turned off.
	 */
	if (temp > I8K_MAX_TEMP)
		return -ENODATA;

	return temp;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int __init i8k_get_dell_signature(int req_fn)
=======
static int i8k_get_dell_signature(int req_fn)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int __init i8k_get_dell_signature(int req_fn)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct smm_regs regs = { .eax = req_fn, };
	int rc;

	rc = i8k_smm(&regs);
	if (rc < 0)
		return rc;

	return regs.eax == 1145651527 && regs.edx == 1145392204 ? 0 : -1;
}

#if IS_ENABLED(CONFIG_I8K)

/*
 * Read the Fn key status.
 */
static int i8k_get_fn_status(void)
{
	struct smm_regs regs = { .eax = I8K_SMM_FN_STATUS, };
	int rc;

	rc = i8k_smm(&regs);
	if (rc < 0)
		return rc;

	switch ((regs.eax >> I8K_FN_SHIFT) & I8K_FN_MASK) {
	case I8K_FN_UP:
		return I8K_VOL_UP;
	case I8K_FN_DOWN:
		return I8K_VOL_DOWN;
	case I8K_FN_MUTE:
		return I8K_VOL_MUTE;
	default:
		return 0;
	}
}

/*
 * Read the power status.
 */
static int i8k_get_power_status(void)
{
	struct smm_regs regs = { .eax = I8K_SMM_POWER_STATUS, };
	int rc;

	rc = i8k_smm(&regs);
	if (rc < 0)
		return rc;

	return (regs.eax & 0xff) == I8K_POWER_AC ? I8K_AC : I8K_BATTERY;
}

/*
 * Procfs interface
 */

static int
<<<<<<< HEAD
<<<<<<< HEAD
i8k_ioctl_unlocked(struct file *fp, struct dell_smm_data *data, unsigned int cmd, unsigned long arg)
=======
i8k_ioctl_unlocked(struct file *fp, unsigned int cmd, unsigned long arg)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
i8k_ioctl_unlocked(struct file *fp, struct dell_smm_data *data, unsigned int cmd, unsigned long arg)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int val = 0;
	int speed;
	unsigned char buff[16];
	int __user *argp = (int __user *)arg;

	if (!argp)
		return -EINVAL;

	switch (cmd) {
	case I8K_BIOS_VERSION:
<<<<<<< HEAD
<<<<<<< HEAD
		if (!isdigit(data->bios_version[0]) || !isdigit(data->bios_version[1]) ||
		    !isdigit(data->bios_version[2]))
			return -EINVAL;

		val = (data->bios_version[0] << 16) |
				(data->bios_version[1] << 8) | data->bios_version[2];
=======
		if (!isdigit(bios_version[0]) || !isdigit(bios_version[1]) ||
		    !isdigit(bios_version[2]))
			return -EINVAL;

		val = (bios_version[0] << 16) |
				(bios_version[1] << 8) | bios_version[2];
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		if (!isdigit(data->bios_version[0]) || !isdigit(data->bios_version[1]) ||
		    !isdigit(data->bios_version[2]))
			return -EINVAL;

		val = (data->bios_version[0] << 16) |
				(data->bios_version[1] << 8) | data->bios_version[2];
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;

	case I8K_MACHINE_ID:
		if (restricted && !capable(CAP_SYS_ADMIN))
			return -EPERM;

		memset(buff, 0, sizeof(buff));
<<<<<<< HEAD
<<<<<<< HEAD
		strscpy(buff, data->bios_machineid, sizeof(buff));
=======
		strlcpy(buff, bios_machineid, sizeof(buff));
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		strscpy(buff, data->bios_machineid, sizeof(buff));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;

	case I8K_FN_STATUS:
		val = i8k_get_fn_status();
		break;

	case I8K_POWER_STATUS:
		val = i8k_get_power_status();
		break;

	case I8K_GET_TEMP:
		val = i8k_get_temp(0);
		break;

	case I8K_GET_SPEED:
		if (copy_from_user(&val, argp, sizeof(int)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		val = i8k_get_fan_speed(data, val);
=======
		val = i8k_get_fan_speed(val);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		val = i8k_get_fan_speed(data, val);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;

	case I8K_GET_FAN:
		if (copy_from_user(&val, argp, sizeof(int)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		val = i8k_get_fan_status(data, val);
=======
		val = i8k_get_fan_status(val);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		val = i8k_get_fan_status(data, val);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;

	case I8K_SET_FAN:
		if (restricted && !capable(CAP_SYS_ADMIN))
			return -EPERM;

		if (copy_from_user(&val, argp, sizeof(int)))
			return -EFAULT;

		if (copy_from_user(&speed, argp + 1, sizeof(int)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		val = i8k_set_fan(data, val, speed);
=======
		val = i8k_set_fan(val, speed);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		val = i8k_set_fan(data, val, speed);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;

	default:
		return -EINVAL;
	}

	if (val < 0)
		return val;

	switch (cmd) {
	case I8K_BIOS_VERSION:
		if (copy_to_user(argp, &val, 4))
			return -EFAULT;

		break;
	case I8K_MACHINE_ID:
		if (copy_to_user(argp, buff, 16))
			return -EFAULT;

		break;
	default:
		if (copy_to_user(argp, &val, sizeof(int)))
			return -EFAULT;

		break;
	}

	return 0;
}

static long i8k_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct dell_smm_data *data = PDE_DATA(file_inode(fp));
	long ret;

	mutex_lock(&data->i8k_mutex);
	ret = i8k_ioctl_unlocked(fp, data, cmd, arg);
	mutex_unlock(&data->i8k_mutex);
=======
	long ret;

	mutex_lock(&i8k_mutex);
	ret = i8k_ioctl_unlocked(fp, cmd, arg);
	mutex_unlock(&i8k_mutex);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct dell_smm_data *data = PDE_DATA(file_inode(fp));
	long ret;

	mutex_lock(&data->i8k_mutex);
	ret = i8k_ioctl_unlocked(fp, data, cmd, arg);
	mutex_unlock(&data->i8k_mutex);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return ret;
}

/*
 * Print the information for /proc/i8k.
 */
static int i8k_proc_show(struct seq_file *seq, void *offset)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct dell_smm_data *data = seq->private;
	int fn_key, cpu_temp, ac_power;
	int left_fan, right_fan, left_speed, right_speed;

	cpu_temp	= i8k_get_temp(0);				/* 11100 µs */
	left_fan	= i8k_get_fan_status(data, I8K_FAN_LEFT);	/*   580 µs */
	right_fan	= i8k_get_fan_status(data, I8K_FAN_RIGHT);	/*   580 µs */
	left_speed	= i8k_get_fan_speed(data, I8K_FAN_LEFT);	/*   580 µs */
	right_speed	= i8k_get_fan_speed(data, I8K_FAN_RIGHT);	/*   580 µs */
	fn_key		= i8k_get_fn_status();				/*   750 µs */
	if (power_status)
		ac_power = i8k_get_power_status();			/* 14700 µs */
=======
=======
	struct dell_smm_data *data = seq->private;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	int fn_key, cpu_temp, ac_power;
	int left_fan, right_fan, left_speed, right_speed;

	cpu_temp	= i8k_get_temp(0);				/* 11100 µs */
	left_fan	= i8k_get_fan_status(data, I8K_FAN_LEFT);	/*   580 µs */
	right_fan	= i8k_get_fan_status(data, I8K_FAN_RIGHT);	/*   580 µs */
	left_speed	= i8k_get_fan_speed(data, I8K_FAN_LEFT);	/*   580 µs */
	right_speed	= i8k_get_fan_speed(data, I8K_FAN_RIGHT);	/*   580 µs */
	fn_key		= i8k_get_fn_status();				/*   750 µs */
	if (power_status)
<<<<<<< HEAD
		ac_power = i8k_get_power_status();		/* 14700 µs */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		ac_power = i8k_get_power_status();			/* 14700 µs */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	else
		ac_power = -1;

	/*
	 * Info:
	 *
	 * 1)  Format version (this will change if format changes)
	 * 2)  BIOS version
	 * 3)  BIOS machine ID
	 * 4)  Cpu temperature
	 * 5)  Left fan status
	 * 6)  Right fan status
	 * 7)  Left fan speed
	 * 8)  Right fan speed
	 * 9)  AC power
	 * 10) Fn Key status
	 */
	seq_printf(seq, "%s %s %s %d %d %d %d %d %d %d\n",
		   I8K_PROC_FMT,
<<<<<<< HEAD
<<<<<<< HEAD
		   data->bios_version,
		   (restricted && !capable(CAP_SYS_ADMIN)) ? "-1" : data->bios_machineid,
=======
		   bios_version,
		   (restricted && !capable(CAP_SYS_ADMIN)) ? "-1" : bios_machineid,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		   data->bios_version,
		   (restricted && !capable(CAP_SYS_ADMIN)) ? "-1" : data->bios_machineid,
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		   cpu_temp,
		   left_fan, right_fan, left_speed, right_speed,
		   ac_power, fn_key);

	return 0;
}

static int i8k_open_fs(struct inode *inode, struct file *file)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return single_open(file, i8k_proc_show, PDE_DATA(inode));
=======
	return single_open(file, i8k_proc_show, NULL);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return single_open(file, i8k_proc_show, PDE_DATA(inode));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static const struct proc_ops i8k_proc_ops = {
	.proc_open	= i8k_open_fs,
	.proc_read	= seq_read,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ioctl	= i8k_ioctl,
};

<<<<<<< HEAD
<<<<<<< HEAD
static void i8k_exit_procfs(void *param)
{
	remove_proc_entry("i8k", NULL);
}

static void __init i8k_init_procfs(struct device *dev)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);

	/* Register the proc entry */
	proc_create_data("i8k", 0, NULL, &i8k_proc_ops, data);

	devm_add_action_or_reset(dev, i8k_exit_procfs, NULL);
=======
static void __init i8k_init_procfs(void)
=======
static void i8k_exit_procfs(void *param)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	remove_proc_entry("i8k", NULL);
}

static void __init i8k_init_procfs(struct device *dev)
{
<<<<<<< HEAD
	remove_proc_entry("i8k", NULL);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
=======
	struct dell_smm_data *data = dev_get_drvdata(dev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* Register the proc entry */
	proc_create_data("i8k", 0, NULL, &i8k_proc_ops, data);

<<<<<<< HEAD
<<<<<<< HEAD
static void __init i8k_init_procfs(struct device *dev)
=======
static inline void __init i8k_init_procfs(void)
{
}

static inline void __exit i8k_exit_procfs(void)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	devm_add_action_or_reset(dev, i8k_exit_procfs, NULL);
}

#else

static void __init i8k_init_procfs(struct device *dev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
}

#endif

/*
 * Hwmon interface
 */

<<<<<<< HEAD
<<<<<<< HEAD
static umode_t dell_smm_is_visible(const void *drvdata, enum hwmon_sensor_types type, u32 attr,
				   int channel)
{
	const struct dell_smm_data *data = drvdata;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_label:
			if (data->temp_type[channel] >= 0)
				return 0444;

			break;
		default:
			break;
		}
		break;
	case hwmon_fan:
		if (data->disallow_fan_support)
			break;

		switch (attr) {
		case hwmon_fan_input:
			if (data->fan[channel])
				return 0444;

			break;
		case hwmon_fan_label:
			if (data->fan[channel] && !data->disallow_fan_type_call)
				return 0444;

			break;
		default:
			break;
		}
		break;
	case hwmon_pwm:
		if (data->disallow_fan_support)
			break;

		switch (attr) {
		case hwmon_pwm_input:
			if (data->fan[channel])
				return 0644;

			break;
		case hwmon_pwm_enable:
			if (data->auto_fan)
				/*
				 * There is no command for retrieve the current status
				 * from BIOS, and userspace/firmware itself can change
				 * it.
				 * Thus we can only provide write-only access for now.
				 */
				return 0200;

			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}

static int dell_smm_read(struct device *dev, enum hwmon_sensor_types type, u32 attr, int channel,
			 long *val)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);
	int ret;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			ret = i8k_get_temp(channel);
			if (ret < 0)
				return ret;

			*val = ret * 1000;

			return 0;
		default:
			break;
		}
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_input:
			ret = i8k_get_fan_speed(data, channel);
			if (ret < 0)
				return ret;

			*val = ret;

			return 0;
		default:
			break;
		}
		break;
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			ret = i8k_get_fan_status(data, channel);
			if (ret < 0)
				return ret;

			*val = clamp_val(ret * data->i8k_pwm_mult, 0, 255);

			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static const char *dell_smm_fan_label(struct dell_smm_data *data, int channel)
{
	bool dock = false;
	int type = i8k_get_fan_type(data, channel);

	if (type < 0)
		return ERR_PTR(type);
=======
static ssize_t i8k_hwmon_temp_label_show(struct device *dev,
					 struct device_attribute *devattr,
					 char *buf)
=======
static umode_t dell_smm_is_visible(const void *drvdata, enum hwmon_sensor_types type, u32 attr,
				   int channel)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	const struct dell_smm_data *data = drvdata;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
		case hwmon_temp_label:
			if (data->temp_type[channel] >= 0)
				return 0444;

			break;
		default:
			break;
		}
		break;
	case hwmon_fan:
		if (data->disallow_fan_support)
			break;

		switch (attr) {
		case hwmon_fan_input:
			if (data->fan[channel])
				return 0444;

			break;
		case hwmon_fan_label:
			if (data->fan[channel] && !data->disallow_fan_type_call)
				return 0444;

			break;
		default:
			break;
		}
		break;
	case hwmon_pwm:
		if (data->disallow_fan_support)
			break;

		switch (attr) {
		case hwmon_pwm_input:
			if (data->fan[channel])
				return 0644;

			break;
		case hwmon_pwm_enable:
			if (data->auto_fan)
				/*
				 * There is no command for retrieve the current status
				 * from BIOS, and userspace/firmware itself can change
				 * it.
				 * Thus we can only provide write-only access for now.
				 */
				return 0200;

			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}

static int dell_smm_read(struct device *dev, enum hwmon_sensor_types type, u32 attr, int channel,
			 long *val)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);
	int ret;

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_input:
			ret = i8k_get_temp(channel);
			if (ret < 0)
				return ret;

			*val = ret * 1000;

			return 0;
		default:
			break;
		}
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_input:
			ret = i8k_get_fan_speed(data, channel);
			if (ret < 0)
				return ret;

			*val = ret;

			return 0;
		default:
			break;
		}
		break;
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			ret = i8k_get_fan_status(data, channel);
			if (ret < 0)
				return ret;

			*val = clamp_val(ret * data->i8k_pwm_mult, 0, 255);

			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static const char *dell_smm_fan_label(struct dell_smm_data *data, int channel)
{
	bool dock = false;
	int type = i8k_get_fan_type(data, channel);

	if (type < 0)
<<<<<<< HEAD
		return type;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		return ERR_PTR(type);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	if (type & 0x10) {
		dock = true;
		type &= 0x0F;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	if (type >= ARRAY_SIZE(fan_labels))
		type = ARRAY_SIZE(fan_labels) - 1;

	return dock ? docking_labels[type] : fan_labels[type];
}

static int dell_smm_read_string(struct device *dev, enum hwmon_sensor_types type, u32 attr,
				int channel, const char **str)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_label:
			*str = temp_labels[data->temp_type[channel]];
			return 0;
		default:
			break;
		}
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_label:
			*str = dell_smm_fan_label(data, channel);
			return PTR_ERR_OR_ZERO(*str);
		default:
			break;
		}
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static int dell_smm_write(struct device *dev, enum hwmon_sensor_types type, u32 attr, int channel,
			  long val)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);
	unsigned long pwm;
	bool enable;
	int err;

	switch (type) {
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			pwm = clamp_val(DIV_ROUND_CLOSEST(val, data->i8k_pwm_mult), 0,
					data->i8k_fan_max);

			mutex_lock(&data->i8k_mutex);
			err = i8k_set_fan(data, channel, pwm);
			mutex_unlock(&data->i8k_mutex);

			if (err < 0)
				return err;

			return 0;
		case hwmon_pwm_enable:
			if (!val)
				return -EINVAL;

			if (val == 1)
				enable = false;
			else
				enable = true;

			mutex_lock(&data->i8k_mutex);
			err = i8k_enable_fan_auto_mode(data, enable);
			mutex_unlock(&data->i8k_mutex);

			if (err < 0)
				return err;

			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static const struct hwmon_ops dell_smm_ops = {
	.is_visible = dell_smm_is_visible,
	.read = dell_smm_read,
	.read_string = dell_smm_read_string,
	.write = dell_smm_write,
};

static const struct hwmon_channel_info *dell_smm_info[] = {
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL
			   ),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_LABEL,
			   HWMON_F_INPUT | HWMON_F_LABEL,
			   HWMON_F_INPUT | HWMON_F_LABEL
			   ),
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT
			   ),
	NULL
};

static const struct hwmon_chip_info dell_smm_chip_info = {
	.ops = &dell_smm_ops,
	.info = dell_smm_info,
};

static int __init dell_smm_init_hwmon(struct device *dev)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);
	struct device *dell_smm_hwmon_dev;
	int i, err;

	for (i = 0; i < DELL_SMM_NO_TEMP; i++) {
		data->temp_type[i] = i8k_get_temp_type(i);
		if (data->temp_type[i] < 0)
			continue;

		if (data->temp_type[i] >= ARRAY_SIZE(temp_labels))
			data->temp_type[i] = ARRAY_SIZE(temp_labels) - 1;
	}

	for (i = 0; i < DELL_SMM_NO_FANS; i++) {
		data->fan_type[i] = INT_MIN;
		err = i8k_get_fan_status(data, i);
		if (err < 0)
			err = i8k_get_fan_type(data, i);
		if (err >= 0)
			data->fan[i] = true;
	}

	dell_smm_hwmon_dev = devm_hwmon_device_register_with_info(dev, "dell_smm", data,
								  &dell_smm_chip_info, NULL);

	return PTR_ERR_OR_ZERO(dell_smm_hwmon_dev);
=======
	if (type >= ARRAY_SIZE(labels))
		type = (ARRAY_SIZE(labels) - 1);

	return sprintf(buf, "%s%s\n", (dock ? "Docking " : ""), labels[type]);
}

static ssize_t i8k_hwmon_fan_show(struct device *dev,
				  struct device_attribute *devattr, char *buf)
{
	int index = to_sensor_dev_attr(devattr)->index;
	int fan_speed;
=======
	if (type >= ARRAY_SIZE(fan_labels))
		type = ARRAY_SIZE(fan_labels) - 1;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return dock ? docking_labels[type] : fan_labels[type];
}

static int dell_smm_read_string(struct device *dev, enum hwmon_sensor_types type, u32 attr,
				int channel, const char **str)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);

	switch (type) {
	case hwmon_temp:
		switch (attr) {
		case hwmon_temp_label:
			*str = temp_labels[data->temp_type[channel]];
			return 0;
		default:
			break;
		}
		break;
	case hwmon_fan:
		switch (attr) {
		case hwmon_fan_label:
			*str = dell_smm_fan_label(data, channel);
			return PTR_ERR_OR_ZERO(*str);
		default:
			break;
		}
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static int dell_smm_write(struct device *dev, enum hwmon_sensor_types type, u32 attr, int channel,
			  long val)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);
	unsigned long pwm;
	bool enable;
	int err;

	switch (type) {
	case hwmon_pwm:
		switch (attr) {
		case hwmon_pwm_input:
			pwm = clamp_val(DIV_ROUND_CLOSEST(val, data->i8k_pwm_mult), 0,
					data->i8k_fan_max);

			mutex_lock(&data->i8k_mutex);
			err = i8k_set_fan(data, channel, pwm);
			mutex_unlock(&data->i8k_mutex);

			if (err < 0)
				return err;

			return 0;
		case hwmon_pwm_enable:
			if (!val)
				return -EINVAL;

			if (val == 1)
				enable = false;
			else
				enable = true;

			mutex_lock(&data->i8k_mutex);
			err = i8k_enable_fan_auto_mode(data, enable);
			mutex_unlock(&data->i8k_mutex);

			if (err < 0)
				return err;

			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static const struct hwmon_ops dell_smm_ops = {
	.is_visible = dell_smm_is_visible,
	.read = dell_smm_read,
	.read_string = dell_smm_read_string,
	.write = dell_smm_write,
};

static const struct hwmon_channel_info *dell_smm_info[] = {
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL
			   ),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_LABEL,
			   HWMON_F_INPUT | HWMON_F_LABEL,
			   HWMON_F_INPUT | HWMON_F_LABEL
			   ),
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT
			   ),
	NULL
};

static const struct hwmon_chip_info dell_smm_chip_info = {
	.ops = &dell_smm_ops,
	.info = dell_smm_info,
};

static int __init dell_smm_init_hwmon(struct device *dev)
{
	struct dell_smm_data *data = dev_get_drvdata(dev);
	struct device *dell_smm_hwmon_dev;
	int i, err;

	for (i = 0; i < DELL_SMM_NO_TEMP; i++) {
		data->temp_type[i] = i8k_get_temp_type(i);
		if (data->temp_type[i] < 0)
			continue;

		if (data->temp_type[i] >= ARRAY_SIZE(temp_labels))
			data->temp_type[i] = ARRAY_SIZE(temp_labels) - 1;
	}

	for (i = 0; i < DELL_SMM_NO_FANS; i++) {
		data->fan_type[i] = INT_MIN;
		err = i8k_get_fan_status(data, i);
		if (err < 0)
			err = i8k_get_fan_type(data, i);
		if (err >= 0)
			data->fan[i] = true;
	}

	dell_smm_hwmon_dev = devm_hwmon_device_register_with_info(dev, "dell_smm", data,
								  &dell_smm_chip_info, NULL);

<<<<<<< HEAD
	i8k_hwmon_flags = 0;

	/* CPU temperature attributes, if temperature type is OK */
	err = i8k_get_temp_type(0);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP1;
	/* check for additional temperature sensors */
	err = i8k_get_temp_type(1);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP2;
	err = i8k_get_temp_type(2);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP3;
	err = i8k_get_temp_type(3);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP4;
	err = i8k_get_temp_type(4);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP5;
	err = i8k_get_temp_type(5);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP6;
	err = i8k_get_temp_type(6);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP7;
	err = i8k_get_temp_type(7);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP8;
	err = i8k_get_temp_type(8);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP9;
	err = i8k_get_temp_type(9);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_TEMP10;

	/* First fan attributes, if fan status or type is OK */
	err = i8k_get_fan_status(0);
	if (err < 0)
		err = i8k_get_fan_type(0);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_FAN1;

	/* Second fan attributes, if fan status or type is OK */
	err = i8k_get_fan_status(1);
	if (err < 0)
		err = i8k_get_fan_type(1);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_FAN2;

	/* Third fan attributes, if fan status or type is OK */
	err = i8k_get_fan_status(2);
	if (err < 0)
		err = i8k_get_fan_type(2);
	if (err >= 0)
		i8k_hwmon_flags |= I8K_HWMON_HAVE_FAN3;

	i8k_hwmon_dev = hwmon_device_register_with_groups(NULL, "dell_smm",
							  NULL, i8k_groups);
	if (IS_ERR(i8k_hwmon_dev)) {
		err = PTR_ERR(i8k_hwmon_dev);
		i8k_hwmon_dev = NULL;
		pr_err("hwmon registration failed (%d)\n", err);
		return err;
	}
	return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return PTR_ERR_OR_ZERO(dell_smm_hwmon_dev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

struct i8k_config_data {
	uint fan_mult;
	uint fan_max;
};

enum i8k_configs {
	DELL_LATITUDE_D520,
	DELL_PRECISION_490,
	DELL_STUDIO,
	DELL_XPS,
};

<<<<<<< HEAD
<<<<<<< HEAD
static const struct i8k_config_data i8k_config_data[] __initconst = {
=======
static const struct i8k_config_data i8k_config_data[] = {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static const struct i8k_config_data i8k_config_data[] __initconst = {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	[DELL_LATITUDE_D520] = {
		.fan_mult = 1,
		.fan_max = I8K_FAN_TURBO,
	},
	[DELL_PRECISION_490] = {
		.fan_mult = 1,
		.fan_max = I8K_FAN_TURBO,
	},
	[DELL_STUDIO] = {
		.fan_mult = 1,
		.fan_max = I8K_FAN_HIGH,
	},
	[DELL_XPS] = {
		.fan_mult = 1,
		.fan_max = I8K_FAN_HIGH,
	},
};

static const struct dmi_system_id i8k_dmi_table[] __initconst = {
	{
		.ident = "Dell Inspiron",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron"),
		},
	},
	{
		.ident = "Dell Latitude",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude"),
		},
	},
	{
		.ident = "Dell Inspiron 2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron"),
		},
	},
	{
		.ident = "Dell Latitude D520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D520"),
		},
		.driver_data = (void *)&i8k_config_data[DELL_LATITUDE_D520],
	},
	{
		.ident = "Dell Latitude 2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude"),
		},
	},
	{	/* UK Inspiron 6400  */
		.ident = "Dell Inspiron 3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MM061"),
		},
	},
	{
		.ident = "Dell Inspiron 3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MP061"),
		},
	},
	{
		.ident = "Dell Precision 490",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME,
				  "Precision WorkStation 490"),
		},
		.driver_data = (void *)&i8k_config_data[DELL_PRECISION_490],
	},
	{
		.ident = "Dell Precision",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Precision"),
		},
	},
	{
		.ident = "Dell Vostro",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro"),
		},
	},
	{
		.ident = "Dell Studio",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Studio"),
		},
		.driver_data = (void *)&i8k_config_data[DELL_STUDIO],
	},
	{
		.ident = "Dell XPS M140",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MXC051"),
		},
		.driver_data = (void *)&i8k_config_data[DELL_XPS],
	},
	{
		.ident = "Dell XPS",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS"),
		},
	},
	{ }
};

MODULE_DEVICE_TABLE(dmi, i8k_dmi_table);

/*
 * On some machines once I8K_SMM_GET_FAN_TYPE is issued then CPU fan speed
 * randomly going up and down due to bug in Dell SMM or BIOS. Here is blacklist
 * of affected Dell machines for which we disallow I8K_SMM_GET_FAN_TYPE call.
 * See bug: https://bugzilla.kernel.org/show_bug.cgi?id=100121
 */
static const struct dmi_system_id i8k_blacklist_fan_type_dmi_table[] __initconst = {
	{
		.ident = "Dell Studio XPS 8000",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Studio XPS 8000"),
		},
	},
	{
		.ident = "Dell Studio XPS 8100",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Studio XPS 8100"),
		},
	},
	{
		.ident = "Dell Inspiron 580",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Inspiron 580 "),
		},
	},
	{ }
};

/*
 * On some machines all fan related SMM functions implemented by Dell BIOS
 * firmware freeze kernel for about 500ms. Until Dell fixes these problems fan
 * support for affected blacklisted Dell machines stay disabled.
 * See bug: https://bugzilla.kernel.org/show_bug.cgi?id=195751
 */
<<<<<<< HEAD
<<<<<<< HEAD
static const struct dmi_system_id i8k_blacklist_fan_support_dmi_table[] __initconst = {
=======
static struct dmi_system_id i8k_blacklist_fan_support_dmi_table[] __initdata = {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static const struct dmi_system_id i8k_blacklist_fan_support_dmi_table[] __initconst = {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	{
		.ident = "Dell Inspiron 7720",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Inspiron 7720"),
		},
	},
	{
		.ident = "Dell Vostro 3360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Vostro 3360"),
		},
	},
	{
		.ident = "Dell XPS13 9333",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "XPS13 9333"),
		},
	},
	{
		.ident = "Dell XPS 15 L502X",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Dell System XPS L502X"),
		},
	},
	{ }
};

struct i8k_fan_control_data {
	unsigned int manual_fan;
	unsigned int auto_fan;
};

enum i8k_fan_controls {
	I8K_FAN_34A3_35A3,
};

<<<<<<< HEAD
<<<<<<< HEAD
static const struct i8k_fan_control_data i8k_fan_control_data[] __initconst = {
=======
static const struct i8k_fan_control_data i8k_fan_control_data[] = {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static const struct i8k_fan_control_data i8k_fan_control_data[] __initconst = {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	[I8K_FAN_34A3_35A3] = {
		.manual_fan = 0x34a3,
		.auto_fan = 0x35a3,
	},
};

<<<<<<< HEAD
<<<<<<< HEAD
static const struct dmi_system_id i8k_whitelist_fan_control[] __initconst = {
	{
		.ident = "Dell Latitude 5480",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude 5480"),
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Dell Latitude E6440",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude E6440"),
=======
static struct dmi_system_id i8k_whitelist_fan_control[] __initdata = {
	{
		.ident = "Dell Precision 5530",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Precision 5530"),
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
=======
static const struct dmi_system_id i8k_whitelist_fan_control[] __initconst = {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	{
<<<<<<< HEAD
		.ident = "Dell Latitude E7440",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude E7440"),
=======
		.ident = "Dell Latitude 5480",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude 5480"),
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
	{
<<<<<<< HEAD
		.ident = "Dell Precision 5530",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Precision 5530"),
=======
		.ident = "Dell Latitude E6440",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude E6440"),
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
	{
<<<<<<< HEAD
		.ident = "Dell Precision 7510",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Precision 7510"),
=======
		.ident = "Dell Latitude E7440",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Latitude E7440"),
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Dell Precision 5530",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Precision 5530"),
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Dell Precision 7510",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Precision 7510"),
		},
		.driver_data = (void *)&i8k_fan_control_data[I8K_FAN_34A3_35A3],
	},
	{ }
};

<<<<<<< HEAD
<<<<<<< HEAD
static int __init dell_smm_probe(struct platform_device *pdev)
{
	struct dell_smm_data *data;
	const struct dmi_system_id *id, *fan_control;
	int fan, ret;

	data = devm_kzalloc(&pdev->dev, sizeof(struct dell_smm_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	mutex_init(&data->i8k_mutex);
	data->i8k_fan_mult = I8K_FAN_MULT;
	data->i8k_fan_max = I8K_FAN_HIGH;
	platform_set_drvdata(pdev, data);

	if (dmi_check_system(i8k_blacklist_fan_support_dmi_table)) {
		dev_warn(&pdev->dev, "broken Dell BIOS detected, disallow fan support\n");
		if (!force)
			data->disallow_fan_support = true;
	}

	if (dmi_check_system(i8k_blacklist_fan_type_dmi_table)) {
		dev_warn(&pdev->dev, "broken Dell BIOS detected, disallow fan type call\n");
		if (!force)
			data->disallow_fan_type_call = true;
	}

	strscpy(data->bios_version, i8k_get_dmi_data(DMI_BIOS_VERSION),
		sizeof(data->bios_version));
	strscpy(data->bios_machineid, i8k_get_dmi_data(DMI_PRODUCT_SERIAL),
		sizeof(data->bios_machineid));
=======
/*
 * Probe for the presence of a supported laptop.
 */
static int __init i8k_probe(void)
=======
static int __init dell_smm_probe(struct platform_device *pdev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct dell_smm_data *data;
	const struct dmi_system_id *id, *fan_control;
	int fan, ret;

	data = devm_kzalloc(&pdev->dev, sizeof(struct dell_smm_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	mutex_init(&data->i8k_mutex);
	data->i8k_fan_mult = I8K_FAN_MULT;
	data->i8k_fan_max = I8K_FAN_HIGH;
	platform_set_drvdata(pdev, data);

	if (dmi_check_system(i8k_blacklist_fan_support_dmi_table)) {
		dev_warn(&pdev->dev, "broken Dell BIOS detected, disallow fan support\n");
		if (!force)
			data->disallow_fan_support = true;
	}

	if (dmi_check_system(i8k_blacklist_fan_type_dmi_table)) {
		dev_warn(&pdev->dev, "broken Dell BIOS detected, disallow fan type call\n");
		if (!force)
			data->disallow_fan_type_call = true;
	}

<<<<<<< HEAD
	strlcpy(bios_version, i8k_get_dmi_data(DMI_BIOS_VERSION),
		sizeof(bios_version));
	strlcpy(bios_machineid, i8k_get_dmi_data(DMI_PRODUCT_SERIAL),
		sizeof(bios_machineid));

	/*
	 * Get SMM Dell signature
	 */
	if (i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG1) &&
	    i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG2)) {
		pr_err("unable to get SMM Dell signature\n");
		if (!force)
			return -ENODEV;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	strscpy(data->bios_version, i8k_get_dmi_data(DMI_BIOS_VERSION),
		sizeof(data->bios_version));
	strscpy(data->bios_machineid, i8k_get_dmi_data(DMI_PRODUCT_SERIAL),
		sizeof(data->bios_machineid));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/*
	 * Set fan multiplier and maximal fan speed from dmi config
	 * Values specified in module parameters override values from dmi
	 */
	id = dmi_first_match(i8k_dmi_table);
	if (id && id->driver_data) {
		const struct i8k_config_data *conf = id->driver_data;
<<<<<<< HEAD
<<<<<<< HEAD

		if (!fan_mult && conf->fan_mult)
			fan_mult = conf->fan_mult;

=======
		if (!fan_mult && conf->fan_mult)
			fan_mult = conf->fan_mult;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

		if (!fan_mult && conf->fan_mult)
			fan_mult = conf->fan_mult;

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (!fan_max && conf->fan_max)
			fan_max = conf->fan_max;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	data->i8k_fan_max = fan_max ? : I8K_FAN_HIGH;	/* Must not be 0 */
	data->i8k_pwm_mult = DIV_ROUND_UP(255, data->i8k_fan_max);

	fan_control = dmi_first_match(i8k_whitelist_fan_control);
	if (fan_control && fan_control->driver_data) {
		const struct i8k_fan_control_data *control = fan_control->driver_data;

		data->manual_fan = control->manual_fan;
		data->auto_fan = control->auto_fan;
		dev_info(&pdev->dev, "enabling support for setting automatic/manual fan control\n");
=======
	i8k_fan_max = fan_max ? : I8K_FAN_HIGH;	/* Must not be 0 */
	i8k_pwm_mult = DIV_ROUND_UP(255, i8k_fan_max);
=======
	data->i8k_fan_max = fan_max ? : I8K_FAN_HIGH;	/* Must not be 0 */
	data->i8k_pwm_mult = DIV_ROUND_UP(255, data->i8k_fan_max);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	fan_control = dmi_first_match(i8k_whitelist_fan_control);
	if (fan_control && fan_control->driver_data) {
		const struct i8k_fan_control_data *control = fan_control->driver_data;

<<<<<<< HEAD
		manual_fan = data->manual_fan;
		auto_fan = data->auto_fan;
		pr_info("enabling support for setting automatic/manual fan control\n");
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		data->manual_fan = control->manual_fan;
		data->auto_fan = control->auto_fan;
		dev_info(&pdev->dev, "enabling support for setting automatic/manual fan control\n");
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	}

	if (!fan_mult) {
		/*
		 * Autodetect fan multiplier based on nominal rpm
		 * If fan reports rpm value too high then set multiplier to 1
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		for (fan = 0; fan < DELL_SMM_NO_FANS; ++fan) {
			ret = i8k_get_fan_nominal_speed(data, fan, data->i8k_fan_max);
			if (ret < 0)
				continue;

			if (ret > I8K_FAN_MAX_RPM)
				data->i8k_fan_mult = 1;
=======
		for (fan = 0; fan < 2; ++fan) {
			ret = i8k_get_fan_nominal_speed(fan, i8k_fan_max);
=======
		for (fan = 0; fan < DELL_SMM_NO_FANS; ++fan) {
			ret = i8k_get_fan_nominal_speed(data, fan, data->i8k_fan_max);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			if (ret < 0)
				continue;

			if (ret > I8K_FAN_MAX_RPM)
<<<<<<< HEAD
				i8k_fan_mult = 1;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
				data->i8k_fan_mult = 1;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			break;
		}
	} else {
		/* Fan multiplier was specified in module param or in dmi */
<<<<<<< HEAD
<<<<<<< HEAD
		data->i8k_fan_mult = fan_mult;
	}

	ret = dell_smm_init_hwmon(&pdev->dev);
	if (ret)
		return ret;

	i8k_init_procfs(&pdev->dev);

	return 0;
}

static struct platform_driver dell_smm_driver = {
	.driver		= {
		.name	= KBUILD_MODNAME,
	},
};

static struct platform_device *dell_smm_device;

/*
 * Probe for the presence of a supported laptop.
 */
static int __init i8k_init(void)
{
	/*
	 * Get DMI information
	 */
	if (!dmi_check_system(i8k_dmi_table)) {
		if (!ignore_dmi && !force)
			return -ENODEV;

		pr_info("not running on a supported Dell system.\n");
		pr_info("vendor=%s, model=%s, version=%s\n",
			i8k_get_dmi_data(DMI_SYS_VENDOR),
			i8k_get_dmi_data(DMI_PRODUCT_NAME),
			i8k_get_dmi_data(DMI_BIOS_VERSION));
	}

	/*
	 * Get SMM Dell signature
	 */
	if (i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG1) &&
	    i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG2)) {
		pr_err("unable to get SMM Dell signature\n");
		if (!force)
			return -ENODEV;
	}

	dell_smm_device = platform_create_bundle(&dell_smm_driver, dell_smm_probe, NULL, 0, NULL,
						 0);

	return PTR_ERR_OR_ZERO(dell_smm_device);
=======
		i8k_fan_mult = fan_mult;
=======
		data->i8k_fan_mult = fan_mult;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	}

	ret = dell_smm_init_hwmon(&pdev->dev);
	if (ret)
		return ret;

	i8k_init_procfs(&pdev->dev);

	return 0;
}

static struct platform_driver dell_smm_driver = {
	.driver		= {
		.name	= KBUILD_MODNAME,
	},
};

static struct platform_device *dell_smm_device;

/*
 * Probe for the presence of a supported laptop.
 */
static int __init i8k_init(void)
{
	/*
	 * Get DMI information
	 */
	if (!dmi_check_system(i8k_dmi_table)) {
		if (!ignore_dmi && !force)
			return -ENODEV;

		pr_info("not running on a supported Dell system.\n");
		pr_info("vendor=%s, model=%s, version=%s\n",
			i8k_get_dmi_data(DMI_SYS_VENDOR),
			i8k_get_dmi_data(DMI_PRODUCT_NAME),
			i8k_get_dmi_data(DMI_BIOS_VERSION));
	}

	/*
	 * Get SMM Dell signature
	 */
	if (i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG1) &&
	    i8k_get_dell_signature(I8K_SMM_GET_DELL_SIG2)) {
		pr_err("unable to get SMM Dell signature\n");
		if (!force)
			return -ENODEV;
	}

<<<<<<< HEAD
	i8k_init_procfs();
	return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	dell_smm_device = platform_create_bundle(&dell_smm_driver, dell_smm_probe, NULL, 0, NULL,
						 0);

	return PTR_ERR_OR_ZERO(dell_smm_device);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static void __exit i8k_exit(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
	platform_device_unregister(dell_smm_device);
	platform_driver_unregister(&dell_smm_driver);
=======
	hwmon_device_unregister(i8k_hwmon_dev);
	i8k_exit_procfs();
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	platform_device_unregister(dell_smm_device);
	platform_driver_unregister(&dell_smm_driver);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

module_init(i8k_init);
module_exit(i8k_exit);
