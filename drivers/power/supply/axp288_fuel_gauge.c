// SPDX-License-Identifier: GPL-2.0-only
/*
 * axp288_fuel_gauge.c - Xpower AXP288 PMIC Fuel Gauge Driver
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright (C) 2020-2021 Andrejus Basovas <xxx@yyy.tld>
 * Copyright (C) 2016-2021 Hans de Goede <hdegoede@redhat.com>
=======
 * Copyright (C) 2016-2017 Hans de Goede <hdegoede@redhat.com>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * Copyright (C) 2020-2021 Andrejus Basovas <xxx@yyy.tld>
 * Copyright (C) 2016-2021 Hans de Goede <hdegoede@redhat.com>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * Copyright (C) 2014 Intel Corporation
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <linux/dmi.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/regmap.h>
#include <linux/jiffies.h>
#include <linux/interrupt.h>
#include <linux/mfd/axp20x.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/iio/consumer.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <asm/unaligned.h>
#include <asm/iosf_mbi.h>

#define PS_STAT_VBUS_TRIGGER			(1 << 0)
#define PS_STAT_BAT_CHRG_DIR			(1 << 2)
#define PS_STAT_VBAT_ABOVE_VHOLD		(1 << 3)
#define PS_STAT_VBUS_VALID			(1 << 4)
#define PS_STAT_VBUS_PRESENT			(1 << 5)

#define CHRG_STAT_BAT_SAFE_MODE			(1 << 3)
#define CHRG_STAT_BAT_VALID			(1 << 4)
#define CHRG_STAT_BAT_PRESENT			(1 << 5)
=======
#include <linux/debugfs.h>
#include <linux/seq_file.h>
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <asm/unaligned.h>
#include <asm/iosf_mbi.h>

#define PS_STAT_VBUS_TRIGGER			(1 << 0)
#define PS_STAT_BAT_CHRG_DIR			(1 << 2)
#define PS_STAT_VBAT_ABOVE_VHOLD		(1 << 3)
#define PS_STAT_VBUS_VALID			(1 << 4)
#define PS_STAT_VBUS_PRESENT			(1 << 5)

#define CHRG_STAT_BAT_SAFE_MODE			(1 << 3)
#define CHRG_STAT_BAT_VALID			(1 << 4)
<<<<<<< HEAD
#define CHRG_STAT_BAT_PRESENT		(1 << 5)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define CHRG_STAT_BAT_PRESENT			(1 << 5)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define CHRG_STAT_CHARGING			(1 << 6)
#define CHRG_STAT_PMIC_OTP			(1 << 7)

#define CHRG_CCCV_CC_MASK			0xf     /* 4 bits */
<<<<<<< HEAD
<<<<<<< HEAD
#define CHRG_CCCV_CC_BIT_POS			0
#define CHRG_CCCV_CC_OFFSET			200     /* 200mA */
#define CHRG_CCCV_CC_LSB_RES			200     /* 200mA */
#define CHRG_CCCV_ITERM_20P			(1 << 4)    /* 20% of CC */
#define CHRG_CCCV_CV_MASK			0x60        /* 2 bits */
#define CHRG_CCCV_CV_BIT_POS			5
=======
#define CHRG_CCCV_CC_BIT_POS		0
=======
#define CHRG_CCCV_CC_BIT_POS			0
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define CHRG_CCCV_CC_OFFSET			200     /* 200mA */
#define CHRG_CCCV_CC_LSB_RES			200     /* 200mA */
#define CHRG_CCCV_ITERM_20P			(1 << 4)    /* 20% of CC */
#define CHRG_CCCV_CV_MASK			0x60        /* 2 bits */
<<<<<<< HEAD
#define CHRG_CCCV_CV_BIT_POS		5
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define CHRG_CCCV_CV_BIT_POS			5
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define CHRG_CCCV_CV_4100MV			0x0     /* 4.10V */
#define CHRG_CCCV_CV_4150MV			0x1     /* 4.15V */
#define CHRG_CCCV_CV_4200MV			0x2     /* 4.20V */
#define CHRG_CCCV_CV_4350MV			0x3     /* 4.35V */
#define CHRG_CCCV_CHG_EN			(1 << 7)

<<<<<<< HEAD
<<<<<<< HEAD
#define FG_CNTL_OCV_ADJ_STAT			(1 << 2)
#define FG_CNTL_OCV_ADJ_EN			(1 << 3)
#define FG_CNTL_CAP_ADJ_STAT			(1 << 4)
=======
#define FG_CNTL_OCV_ADJ_STAT		(1 << 2)
#define FG_CNTL_OCV_ADJ_EN			(1 << 3)
#define FG_CNTL_CAP_ADJ_STAT		(1 << 4)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define FG_CNTL_OCV_ADJ_STAT			(1 << 2)
#define FG_CNTL_OCV_ADJ_EN			(1 << 3)
#define FG_CNTL_CAP_ADJ_STAT			(1 << 4)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define FG_CNTL_CAP_ADJ_EN			(1 << 5)
#define FG_CNTL_CC_EN				(1 << 6)
#define FG_CNTL_GAUGE_EN			(1 << 7)

#define FG_15BIT_WORD_VALID			(1 << 15)
#define FG_15BIT_VAL_MASK			0x7fff

#define FG_REP_CAP_VALID			(1 << 7)
#define FG_REP_CAP_VAL_MASK			0x7F

#define FG_DES_CAP1_VALID			(1 << 7)
#define FG_DES_CAP_RES_LSB			1456    /* 1.456mAhr */

#define FG_DES_CC_RES_LSB			1456    /* 1.456mAhr */

#define FG_OCV_CAP_VALID			(1 << 7)
#define FG_OCV_CAP_VAL_MASK			0x7F
#define FG_CC_CAP_VALID				(1 << 7)
#define FG_CC_CAP_VAL_MASK			0x7F

<<<<<<< HEAD
<<<<<<< HEAD
#define FG_LOW_CAP_THR1_MASK			0xf0    /* 5% tp 20% */
#define FG_LOW_CAP_THR1_VAL			0xa0    /* 15 perc */
#define FG_LOW_CAP_THR2_MASK			0x0f    /* 0% to 15% */
=======
#define FG_LOW_CAP_THR1_MASK		0xf0    /* 5% tp 20% */
#define FG_LOW_CAP_THR1_VAL			0xa0    /* 15 perc */
#define FG_LOW_CAP_THR2_MASK		0x0f    /* 0% to 15% */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define FG_LOW_CAP_THR1_MASK			0xf0    /* 5% tp 20% */
#define FG_LOW_CAP_THR1_VAL			0xa0    /* 15 perc */
#define FG_LOW_CAP_THR2_MASK			0x0f    /* 0% to 15% */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define FG_LOW_CAP_WARN_THR			14  /* 14 perc */
#define FG_LOW_CAP_CRIT_THR			4   /* 4 perc */
#define FG_LOW_CAP_SHDN_THR			0   /* 0 perc */

<<<<<<< HEAD
<<<<<<< HEAD
#define DEV_NAME				"axp288_fuel_gauge"
=======
#define NR_RETRY_CNT    3
#define DEV_NAME	"axp288_fuel_gauge"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define DEV_NAME				"axp288_fuel_gauge"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

/* 1.1mV per LSB expressed in uV */
#define VOLTAGE_FROM_ADC(a)			((a * 11) / 10)
/* properties converted to uV, uA */
<<<<<<< HEAD
<<<<<<< HEAD
#define PROP_VOLT(a)				((a) * 1000)
#define PROP_CURR(a)				((a) * 1000)

#define AXP288_REG_UPDATE_INTERVAL		(60 * HZ)
#define AXP288_FG_INTR_NUM			6
=======
#define PROP_VOLT(a)		((a) * 1000)
#define PROP_CURR(a)		((a) * 1000)

#define AXP288_FG_INTR_NUM	6
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define PROP_VOLT(a)				((a) * 1000)
#define PROP_CURR(a)				((a) * 1000)

#define AXP288_REG_UPDATE_INTERVAL		(60 * HZ)
#define AXP288_FG_INTR_NUM			6
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
enum {
	QWBTU_IRQ = 0,
	WBTU_IRQ,
	QWBTO_IRQ,
	WBTO_IRQ,
	WL2_IRQ,
	WL1_IRQ,
};

enum {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	BAT_TEMP = 0,
	PMIC_TEMP,
	SYSTEM_TEMP,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	BAT_CHRG_CURR,
	BAT_D_CURR,
	BAT_VOLT,
	IIO_CHANNEL_NUM
};

struct axp288_fg_info {
<<<<<<< HEAD
<<<<<<< HEAD
	struct device *dev;
=======
	struct platform_device *pdev;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct device *dev;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct regmap *regmap;
	struct regmap_irq_chip_data *regmap_irqc;
	int irq[AXP288_FG_INTR_NUM];
	struct iio_channel *iio_channel[IIO_CHANNEL_NUM];
	struct power_supply *bat;
	struct mutex lock;
	int status;
	int max_volt;
<<<<<<< HEAD
<<<<<<< HEAD
	int pwr_op;
	int low_cap;
	struct dentry *debug_file;

	char valid;                 /* zero until following fields are valid */
	unsigned long last_updated; /* in jiffies */

	int pwr_stat;
	int fg_res;
	int bat_volt;
	int d_curr;
	int c_curr;
	int ocv;
	int fg_cc_mtr1;
	int fg_des_cap1;
=======
	struct dentry *debug_file;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	int pwr_op;
	int low_cap;
	struct dentry *debug_file;

	char valid;                 /* zero until following fields are valid */
	unsigned long last_updated; /* in jiffies */

	int pwr_stat;
	int fg_res;
	int bat_volt;
	int d_curr;
	int c_curr;
	int ocv;
	int fg_cc_mtr1;
	int fg_des_cap1;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

static enum power_supply_property fuel_gauge_props[] = {
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
};

static int fuel_gauge_reg_readb(struct axp288_fg_info *info, int reg)
{
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned int val;
	int ret;

	ret = regmap_read(info->regmap, reg, &val);
	if (ret < 0) {
		dev_err(info->dev, "Error reading reg 0x%02x err: %d\n", reg, ret);
=======
	int ret, i;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	unsigned int val;
	int ret;

	ret = regmap_read(info->regmap, reg, &val);
	if (ret < 0) {
<<<<<<< HEAD
		dev_err(&info->pdev->dev, "axp288 reg read err:%d\n", ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_err(info->dev, "Error reading reg 0x%02x err: %d\n", reg, ret);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return ret;
	}

	return val;
}

static int fuel_gauge_reg_writeb(struct axp288_fg_info *info, int reg, u8 val)
{
	int ret;

	ret = regmap_write(info->regmap, reg, (unsigned int)val);

	if (ret < 0)
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(info->dev, "Error writing reg 0x%02x err: %d\n", reg, ret);
=======
		dev_err(&info->pdev->dev, "axp288 reg write err:%d\n", ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_err(info->dev, "Error writing reg 0x%02x err: %d\n", reg, ret);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return ret;
}

static int fuel_gauge_read_15bit_word(struct axp288_fg_info *info, int reg)
{
	unsigned char buf[2];
	int ret;

	ret = regmap_bulk_read(info->regmap, reg, buf, 2);
	if (ret < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(info->dev, "Error reading reg 0x%02x err: %d\n", reg, ret);
=======
		dev_err(&info->pdev->dev, "Error reading reg 0x%02x err: %d\n",
			reg, ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_err(info->dev, "Error reading reg 0x%02x err: %d\n", reg, ret);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return ret;
	}

	ret = get_unaligned_be16(buf);
	if (!(ret & FG_15BIT_WORD_VALID)) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(info->dev, "Error reg 0x%02x contents not valid\n", reg);
=======
		dev_err(&info->pdev->dev, "Error reg 0x%02x contents not valid\n",
			reg);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_err(info->dev, "Error reg 0x%02x contents not valid\n", reg);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return -ENXIO;
	}

	return ret & FG_15BIT_VAL_MASK;
}

static int fuel_gauge_read_12bit_word(struct axp288_fg_info *info, int reg)
{
	unsigned char buf[2];
	int ret;

	ret = regmap_bulk_read(info->regmap, reg, buf, 2);
	if (ret < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(info->dev, "Error reading reg 0x%02x err: %d\n", reg, ret);
=======
		dev_err(&info->pdev->dev, "Error reading reg 0x%02x err: %d\n",
			reg, ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_err(info->dev, "Error reading reg 0x%02x err: %d\n", reg, ret);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return ret;
	}

	/* 12-bit data values have upper 8 bits in buf[0], lower 4 in buf[1] */
	return (buf[0] << 4) | ((buf[1] >> 4) & 0x0f);
}

<<<<<<< HEAD
<<<<<<< HEAD
static int fuel_gauge_update_registers(struct axp288_fg_info *info)
{
	int ret;

	if (info->valid && time_before(jiffies, info->last_updated + AXP288_REG_UPDATE_INTERVAL))
		return 0;

	dev_dbg(info->dev, "Fuel Gauge updating register values...\n");

	ret = iosf_mbi_block_punit_i2c_access();
	if (ret < 0)
		return ret;

	ret = fuel_gauge_reg_readb(info, AXP20X_PWR_INPUT_STATUS);
	if (ret < 0)
		goto out;
	info->pwr_stat = ret;

	ret = fuel_gauge_reg_readb(info, AXP20X_FG_RES);
	if (ret < 0)
		goto out;
	info->fg_res = ret;

	ret = iio_read_channel_raw(info->iio_channel[BAT_VOLT], &info->bat_volt);
	if (ret < 0)
		goto out;

	if (info->pwr_stat & PS_STAT_BAT_CHRG_DIR) {
		info->d_curr = 0;
		ret = iio_read_channel_raw(info->iio_channel[BAT_CHRG_CURR], &info->c_curr);
		if (ret < 0)
			goto out;
	} else {
		info->c_curr = 0;
		ret = iio_read_channel_raw(info->iio_channel[BAT_D_CURR], &info->d_curr);
		if (ret < 0)
			goto out;
	}

	ret = fuel_gauge_read_12bit_word(info, AXP288_FG_OCVH_REG);
	if (ret < 0)
		goto out;
	info->ocv = ret;

	ret = fuel_gauge_read_15bit_word(info, AXP288_FG_CC_MTR1_REG);
	if (ret < 0)
		goto out;
	info->fg_cc_mtr1 = ret;

	ret = fuel_gauge_read_15bit_word(info, AXP288_FG_DES_CAP1_REG);
	if (ret < 0)
		goto out;
	info->fg_des_cap1 = ret;

	info->last_updated = jiffies;
	info->valid = 1;
	ret = 0;
out:
	iosf_mbi_unblock_punit_i2c_access();
	return ret;
}

static void fuel_gauge_get_status(struct axp288_fg_info *info)
{
	int pwr_stat = info->pwr_stat;
	int fg_res = info->fg_res;
	int curr = info->d_curr;
=======
#ifdef CONFIG_DEBUG_FS
static int fuel_gauge_debug_show(struct seq_file *s, void *data)
=======
static int fuel_gauge_update_registers(struct axp288_fg_info *info)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int ret;

	if (info->valid && time_before(jiffies, info->last_updated + AXP288_REG_UPDATE_INTERVAL))
		return 0;

	dev_dbg(info->dev, "Fuel Gauge updating register values...\n");

	ret = iosf_mbi_block_punit_i2c_access();
	if (ret < 0)
		return ret;

	ret = fuel_gauge_reg_readb(info, AXP20X_PWR_INPUT_STATUS);
	if (ret < 0)
		goto out;
	info->pwr_stat = ret;

	ret = fuel_gauge_reg_readb(info, AXP20X_FG_RES);
	if (ret < 0)
		goto out;
	info->fg_res = ret;

	ret = iio_read_channel_raw(info->iio_channel[BAT_VOLT], &info->bat_volt);
	if (ret < 0)
		goto out;

	if (info->pwr_stat & PS_STAT_BAT_CHRG_DIR) {
		info->d_curr = 0;
		ret = iio_read_channel_raw(info->iio_channel[BAT_CHRG_CURR], &info->c_curr);
		if (ret < 0)
			goto out;
	} else {
		info->c_curr = 0;
		ret = iio_read_channel_raw(info->iio_channel[BAT_D_CURR], &info->d_curr);
		if (ret < 0)
			goto out;
	}

	ret = fuel_gauge_read_12bit_word(info, AXP288_FG_OCVH_REG);
	if (ret < 0)
		goto out;
	info->ocv = ret;

	ret = fuel_gauge_read_15bit_word(info, AXP288_FG_CC_MTR1_REG);
	if (ret < 0)
		goto out;
	info->fg_cc_mtr1 = ret;

	ret = fuel_gauge_read_15bit_word(info, AXP288_FG_DES_CAP1_REG);
	if (ret < 0)
		goto out;
	info->fg_des_cap1 = ret;

	info->last_updated = jiffies;
	info->valid = 1;
	ret = 0;
out:
	iosf_mbi_unblock_punit_i2c_access();
	return ret;
}

static void fuel_gauge_get_status(struct axp288_fg_info *info)
{
<<<<<<< HEAD
	int pwr_stat, fg_res, curr, ret;

	pwr_stat = fuel_gauge_reg_readb(info, AXP20X_PWR_INPUT_STATUS);
	if (pwr_stat < 0) {
		dev_err(&info->pdev->dev,
			"PWR STAT read failed:%d\n", pwr_stat);
		return;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	int pwr_stat = info->pwr_stat;
	int fg_res = info->fg_res;
	int curr = info->d_curr;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* Report full if Vbus is valid and the reported capacity is 100% */
	if (!(pwr_stat & PS_STAT_VBUS_VALID))
		goto not_full;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	fg_res = fuel_gauge_reg_readb(info, AXP20X_FG_RES);
	if (fg_res < 0) {
		dev_err(&info->pdev->dev, "FG RES read failed: %d\n", fg_res);
		return;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (!(fg_res & FG_REP_CAP_VALID))
		goto not_full;

	fg_res &= ~FG_REP_CAP_VALID;
	if (fg_res == 100) {
		info->status = POWER_SUPPLY_STATUS_FULL;
		return;
	}

	/*
	 * Sometimes the charger turns itself off before fg-res reaches 100%.
	 * When this happens the AXP288 reports a not-charging status and
	 * 0 mA discharge current.
	 */
	if (fg_res < 90 || (pwr_stat & PS_STAT_BAT_CHRG_DIR))
		goto not_full;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	ret = iio_read_channel_raw(info->iio_channel[BAT_D_CURR], &curr);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "FG get current failed: %d\n", ret);
		return;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (curr == 0) {
		info->status = POWER_SUPPLY_STATUS_FULL;
		return;
	}

not_full:
	if (pwr_stat & PS_STAT_BAT_CHRG_DIR)
		info->status = POWER_SUPPLY_STATUS_CHARGING;
	else
		info->status = POWER_SUPPLY_STATUS_DISCHARGING;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int fuel_gauge_battery_health(struct axp288_fg_info *info)
{
	int vocv = VOLTAGE_FROM_ADC(info->ocv);
	int health = POWER_SUPPLY_HEALTH_UNKNOWN;
=======
static int fuel_gauge_get_vbatt(struct axp288_fg_info *info, int *vbatt)
{
	int ret = 0, raw_val;

	ret = iio_read_channel_raw(info->iio_channel[BAT_VOLT], &raw_val);
	if (ret < 0)
		goto vbatt_read_fail;

	*vbatt = VOLTAGE_FROM_ADC(raw_val);
vbatt_read_fail:
	return ret;
}

static int fuel_gauge_get_current(struct axp288_fg_info *info, int *cur)
{
	int ret, discharge;

	/* First check discharge current, so that we do only 1 read on bat. */
	ret = iio_read_channel_raw(info->iio_channel[BAT_D_CURR], &discharge);
	if (ret < 0)
		return ret;

	if (discharge > 0) {
		*cur = -1 * discharge;
		return 0;
	}

	return iio_read_channel_raw(info->iio_channel[BAT_CHRG_CURR], cur);
}

static int fuel_gauge_get_vocv(struct axp288_fg_info *info, int *vocv)
{
	int ret;

	ret = fuel_gauge_read_12bit_word(info, AXP288_FG_OCVH_REG);
	if (ret >= 0)
		*vocv = VOLTAGE_FROM_ADC(ret);

	return ret;
}

static int fuel_gauge_battery_health(struct axp288_fg_info *info)
{
	int ret, vocv, health = POWER_SUPPLY_HEALTH_UNKNOWN;

	ret = fuel_gauge_get_vocv(info, &vocv);
	if (ret < 0)
		goto health_read_fail;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int fuel_gauge_battery_health(struct axp288_fg_info *info)
{
	int vocv = VOLTAGE_FROM_ADC(info->ocv);
	int health = POWER_SUPPLY_HEALTH_UNKNOWN;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	if (vocv > info->max_volt)
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	else
		health = POWER_SUPPLY_HEALTH_GOOD;

<<<<<<< HEAD
<<<<<<< HEAD
=======
health_read_fail:
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	return health;
}

static int fuel_gauge_get_property(struct power_supply *ps,
		enum power_supply_property prop,
		union power_supply_propval *val)
{
	struct axp288_fg_info *info = power_supply_get_drvdata(ps);
<<<<<<< HEAD
<<<<<<< HEAD
	int ret, value;

	mutex_lock(&info->lock);

	ret = fuel_gauge_update_registers(info);
	if (ret < 0)
		goto out;

=======
	int ret = 0, value;

	mutex_lock(&info->lock);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	int ret, value;

	mutex_lock(&info->lock);

	ret = fuel_gauge_update_registers(info);
	if (ret < 0)
		goto out;

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	switch (prop) {
	case POWER_SUPPLY_PROP_STATUS:
		fuel_gauge_get_status(info);
		val->intval = info->status;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = fuel_gauge_battery_health(info);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
<<<<<<< HEAD
<<<<<<< HEAD
		value = VOLTAGE_FROM_ADC(info->bat_volt);
		val->intval = PROP_VOLT(value);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		value = VOLTAGE_FROM_ADC(info->ocv);
		val->intval = PROP_VOLT(value);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (info->d_curr > 0)
			value = -1 * info->d_curr;
		else
			value = info->c_curr;

		val->intval = PROP_CURR(value);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		if (info->pwr_op & CHRG_STAT_BAT_PRESENT)
=======
		ret = fuel_gauge_get_vbatt(info, &value);
		if (ret < 0)
			goto fuel_gauge_read_err;
=======
		value = VOLTAGE_FROM_ADC(info->bat_volt);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		val->intval = PROP_VOLT(value);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		value = VOLTAGE_FROM_ADC(info->ocv);
		val->intval = PROP_VOLT(value);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (info->d_curr > 0)
			value = -1 * info->d_curr;
		else
			value = info->c_curr;

		val->intval = PROP_CURR(value);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
<<<<<<< HEAD
		ret = fuel_gauge_reg_readb(info, AXP20X_PWR_OP_MODE);
		if (ret < 0)
			goto fuel_gauge_read_err;

		if (ret & CHRG_STAT_BAT_PRESENT)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		if (info->pwr_op & CHRG_STAT_BAT_PRESENT)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			val->intval = 1;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
<<<<<<< HEAD
<<<<<<< HEAD
		if (!(info->fg_res & FG_REP_CAP_VALID))
			dev_err(info->dev, "capacity measurement not valid\n");
		val->intval = (info->fg_res & FG_REP_CAP_VAL_MASK);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		val->intval = (info->low_cap & 0x0f);
=======
		ret = fuel_gauge_reg_readb(info, AXP20X_FG_RES);
		if (ret < 0)
			goto fuel_gauge_read_err;

		if (!(ret & FG_REP_CAP_VALID))
			dev_err(&info->pdev->dev,
				"capacity measurement not valid\n");
		val->intval = (ret & FG_REP_CAP_VAL_MASK);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		ret = fuel_gauge_reg_readb(info, AXP288_FG_LOW_CAP_REG);
		if (ret < 0)
			goto fuel_gauge_read_err;
		val->intval = (ret & 0x0f);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		if (!(info->fg_res & FG_REP_CAP_VALID))
			dev_err(info->dev, "capacity measurement not valid\n");
		val->intval = (info->fg_res & FG_REP_CAP_VAL_MASK);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		val->intval = (info->low_cap & 0x0f);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
<<<<<<< HEAD
<<<<<<< HEAD
		val->intval = info->fg_cc_mtr1 * FG_DES_CAP_RES_LSB;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = info->fg_des_cap1 * FG_DES_CAP_RES_LSB;
=======
		ret = fuel_gauge_read_15bit_word(info, AXP288_FG_CC_MTR1_REG);
		if (ret < 0)
			goto fuel_gauge_read_err;

		val->intval = ret * FG_DES_CAP_RES_LSB;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = fuel_gauge_read_15bit_word(info, AXP288_FG_DES_CAP1_REG);
		if (ret < 0)
			goto fuel_gauge_read_err;

		val->intval = ret * FG_DES_CAP_RES_LSB;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		val->intval = info->fg_cc_mtr1 * FG_DES_CAP_RES_LSB;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = info->fg_des_cap1 * FG_DES_CAP_RES_LSB;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = PROP_VOLT(info->max_volt);
		break;
	default:
<<<<<<< HEAD
<<<<<<< HEAD
		ret = -EINVAL;
	}

out:
=======
		mutex_unlock(&info->lock);
		return -EINVAL;
	}

	mutex_unlock(&info->lock);
	return 0;

fuel_gauge_read_err:
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		ret = -EINVAL;
	}

out:
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	mutex_unlock(&info->lock);
	return ret;
}

static int fuel_gauge_set_property(struct power_supply *ps,
		enum power_supply_property prop,
		const union power_supply_propval *val)
{
	struct axp288_fg_info *info = power_supply_get_drvdata(ps);
<<<<<<< HEAD
<<<<<<< HEAD
	int new_low_cap, ret = 0;
=======
	int ret = 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	int new_low_cap, ret = 0;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	mutex_lock(&info->lock);
	switch (prop) {
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		if ((val->intval < 0) || (val->intval > 15)) {
			ret = -EINVAL;
			break;
		}
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		new_low_cap = info->low_cap;
		new_low_cap &= 0xf0;
		new_low_cap |= (val->intval & 0xf);
		ret = fuel_gauge_reg_writeb(info, AXP288_FG_LOW_CAP_REG, new_low_cap);
		if (ret == 0)
			info->low_cap = new_low_cap;
<<<<<<< HEAD
=======
		ret = fuel_gauge_reg_readb(info, AXP288_FG_LOW_CAP_REG);
		if (ret < 0)
			break;
		ret &= 0xf0;
		ret |= (val->intval & 0xf);
		ret = fuel_gauge_reg_writeb(info, AXP288_FG_LOW_CAP_REG, ret);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&info->lock);
	return ret;
}

static int fuel_gauge_property_is_writeable(struct power_supply *psy,
	enum power_supply_property psp)
{
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		ret = 1;
		break;
	default:
		ret = 0;
	}

	return ret;
}

static irqreturn_t fuel_gauge_thread_handler(int irq, void *dev)
{
	struct axp288_fg_info *info = dev;
	int i;

	for (i = 0; i < AXP288_FG_INTR_NUM; i++) {
		if (info->irq[i] == irq)
			break;
	}

	if (i >= AXP288_FG_INTR_NUM) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_warn(info->dev, "spurious interrupt!!\n");
=======
		dev_warn(&info->pdev->dev, "spurious interrupt!!\n");
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		dev_warn(info->dev, "spurious interrupt!!\n");
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return IRQ_NONE;
	}

	switch (i) {
	case QWBTU_IRQ:
<<<<<<< HEAD
<<<<<<< HEAD
		dev_info(info->dev, "Quit Battery under temperature in work mode IRQ (QWBTU)\n");
		break;
	case WBTU_IRQ:
		dev_info(info->dev, "Battery under temperature in work mode IRQ (WBTU)\n");
		break;
	case QWBTO_IRQ:
		dev_info(info->dev, "Quit Battery over temperature in work mode IRQ (QWBTO)\n");
		break;
	case WBTO_IRQ:
		dev_info(info->dev, "Battery over temperature in work mode IRQ (WBTO)\n");
		break;
	case WL2_IRQ:
		dev_info(info->dev, "Low Batt Warning(2) INTR\n");
		break;
	case WL1_IRQ:
		dev_info(info->dev, "Low Batt Warning(1) INTR\n");
		break;
	default:
		dev_warn(info->dev, "Spurious Interrupt!!!\n");
	}

	info->valid = 0; /* Force updating of the cached registers */

=======
		dev_info(&info->pdev->dev,
			"Quit Battery under temperature in work mode IRQ (QWBTU)\n");
=======
		dev_info(info->dev, "Quit Battery under temperature in work mode IRQ (QWBTU)\n");
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		break;
	case WBTU_IRQ:
		dev_info(info->dev, "Battery under temperature in work mode IRQ (WBTU)\n");
		break;
	case QWBTO_IRQ:
		dev_info(info->dev, "Quit Battery over temperature in work mode IRQ (QWBTO)\n");
		break;
	case WBTO_IRQ:
		dev_info(info->dev, "Battery over temperature in work mode IRQ (WBTO)\n");
		break;
	case WL2_IRQ:
		dev_info(info->dev, "Low Batt Warning(2) INTR\n");
		break;
	case WL1_IRQ:
		dev_info(info->dev, "Low Batt Warning(1) INTR\n");
		break;
	default:
		dev_warn(info->dev, "Spurious Interrupt!!!\n");
	}

<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	info->valid = 0; /* Force updating of the cached registers */

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	power_supply_changed(info->bat);
	return IRQ_HANDLED;
}

static void fuel_gauge_external_power_changed(struct power_supply *psy)
{
	struct axp288_fg_info *info = power_supply_get_drvdata(psy);

<<<<<<< HEAD
<<<<<<< HEAD
	info->valid = 0; /* Force updating of the cached registers */
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	info->valid = 0; /* Force updating of the cached registers */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	power_supply_changed(info->bat);
}

static const struct power_supply_desc fuel_gauge_desc = {
	.name			= DEV_NAME,
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= fuel_gauge_props,
	.num_properties		= ARRAY_SIZE(fuel_gauge_props),
	.get_property		= fuel_gauge_get_property,
	.set_property		= fuel_gauge_set_property,
	.property_is_writeable	= fuel_gauge_property_is_writeable,
	.external_power_changed	= fuel_gauge_external_power_changed,
};

<<<<<<< HEAD
<<<<<<< HEAD
static void fuel_gauge_init_irq(struct axp288_fg_info *info, struct platform_device *pdev)
=======
static void fuel_gauge_init_irq(struct axp288_fg_info *info)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static void fuel_gauge_init_irq(struct axp288_fg_info *info, struct platform_device *pdev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int ret, i, pirq;

	for (i = 0; i < AXP288_FG_INTR_NUM; i++) {
<<<<<<< HEAD
<<<<<<< HEAD
		pirq = platform_get_irq(pdev, i);
		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		if (info->irq[i] < 0) {
			dev_warn(info->dev, "regmap_irq get virq failed for IRQ %d: %d\n",
=======
		pirq = platform_get_irq(info->pdev, i);
		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		if (info->irq[i] < 0) {
			dev_warn(&info->pdev->dev,
				"regmap_irq get virq failed for IRQ %d: %d\n",
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		pirq = platform_get_irq(pdev, i);
		info->irq[i] = regmap_irq_get_virq(info->regmap_irqc, pirq);
		if (info->irq[i] < 0) {
			dev_warn(info->dev, "regmap_irq get virq failed for IRQ %d: %d\n",
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
				pirq, info->irq[i]);
			info->irq[i] = -1;
			goto intr_failed;
		}
		ret = request_threaded_irq(info->irq[i],
				NULL, fuel_gauge_thread_handler,
				IRQF_ONESHOT, DEV_NAME, info);
		if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
			dev_warn(info->dev, "request irq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			goto intr_failed;
=======
			dev_warn(&info->pdev->dev,
				"request irq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			goto intr_failed;
		} else {
			dev_info(&info->pdev->dev, "HW IRQ %d -> VIRQ %d\n",
				pirq, info->irq[i]);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
			dev_warn(info->dev, "request irq failed for IRQ %d: %d\n",
				pirq, info->irq[i]);
			info->irq[i] = -1;
			goto intr_failed;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		}
	}
	return;

intr_failed:
	for (; i > 0; i--) {
		free_irq(info->irq[i - 1], info);
		info->irq[i - 1] = -1;
	}
}

/*
 * Some devices have no battery (HDMI sticks) and the axp288 battery's
 * detection reports one despite it not being there.
 * Please keep this listed sorted alphabetically.
 */
static const struct dmi_system_id axp288_no_battery_list[] = {
	{
		/* ACEPC T8 Cherry Trail Z8350 mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "T8"),
			/* also match on somewhat unique bios-version */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1.000"),
		},
	},
	{
		/* ACEPC T11 Cherry Trail Z8350 mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "To be filled by O.E.M."),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Cherry Trail CR"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "T11"),
			/* also match on somewhat unique bios-version */
			DMI_EXACT_MATCH(DMI_BIOS_VERSION, "1.000"),
		},
	},
	{
		/* ECS EF20EA */
		.matches = {
			DMI_MATCH(DMI_PRODUCT_NAME, "EF20EA"),
		},
	},
	{
		/* Intel Cherry Trail Compute Stick, Windows version */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Intel"),
			DMI_MATCH(DMI_PRODUCT_NAME, "STK1AW32SC"),
		},
	},
	{
		/* Intel Cherry Trail Compute Stick, version without an OS */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Intel"),
			DMI_MATCH(DMI_PRODUCT_NAME, "STK1A32SC"),
		},
	},
	{
		/* Meegopad T02 */
		.matches = {
			DMI_MATCH(DMI_PRODUCT_NAME, "MEEGOPAD T02"),
		},
	},
	{	/* Mele PCG03 Mini PC */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "Mini PC"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Mini PC"),
		},
	},
	{
		/* Minix Neo Z83-4 mini PC */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "MINIX"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Z83-4"),
		}
	},
	{
		/* Various Ace PC/Meegopad/MinisForum/Wintel Mini-PCs/HDMI-sticks */
		.matches = {
			DMI_MATCH(DMI_BOARD_NAME, "T3 MRD"),
			DMI_MATCH(DMI_CHASSIS_TYPE, "3"),
			DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
			DMI_MATCH(DMI_BIOS_VERSION, "5.11"),
		},
	},
	{}
};

static int axp288_fuel_gauge_probe(struct platform_device *pdev)
{
	int i, ret = 0;
	struct axp288_fg_info *info;
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	struct power_supply_config psy_cfg = {};
	static const char * const iio_chan_name[] = {
<<<<<<< HEAD
<<<<<<< HEAD
=======
		[BAT_TEMP] = "axp288-batt-temp",
		[PMIC_TEMP] = "axp288-pmic-temp",
		[SYSTEM_TEMP] = "axp288-system-temp",
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		[BAT_CHRG_CURR] = "axp288-chrg-curr",
		[BAT_D_CURR] = "axp288-chrg-d-curr",
		[BAT_VOLT] = "axp288-batt-volt",
	};
	unsigned int val;

	if (dmi_check_system(axp288_no_battery_list))
		return -ENODEV;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	/*
	 * On some devices the fuelgauge and charger parts of the axp288 are
	 * not used, check that the fuelgauge is enabled (CC_CTRL != 0).
	 */
	ret = regmap_read(axp20x->regmap, AXP20X_CC_CTRL, &val);
	if (ret < 0)
		return ret;
	if (val == 0)
		return -ENODEV;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

<<<<<<< HEAD
<<<<<<< HEAD
	info->dev = &pdev->dev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;
	info->valid = 0;
=======
	info->pdev = pdev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	info->dev = &pdev->dev;
	info->regmap = axp20x->regmap;
	info->regmap_irqc = axp20x->regmap_irqc;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;
	info->valid = 0;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	platform_set_drvdata(pdev, info);

	mutex_init(&info->lock);

	for (i = 0; i < IIO_CHANNEL_NUM; i++) {
		/*
		 * Note cannot use devm_iio_channel_get because x86 systems
		 * lack the device<->channel maps which iio_channel_get will
		 * try to use when passed a non NULL device pointer.
		 */
		info->iio_channel[i] =
			iio_channel_get(NULL, iio_chan_name[i]);
		if (IS_ERR(info->iio_channel[i])) {
			ret = PTR_ERR(info->iio_channel[i]);
			dev_dbg(&pdev->dev, "error getting iiochan %s: %d\n",
				iio_chan_name[i], ret);
			/* Wait for axp288_adc to load */
			if (ret == -ENODEV)
				ret = -EPROBE_DEFER;

			goto out_free_iio_chan;
		}
	}

<<<<<<< HEAD
<<<<<<< HEAD
	ret = iosf_mbi_block_punit_i2c_access();
	if (ret < 0)
		goto out_free_iio_chan;

	/*
	 * On some devices the fuelgauge and charger parts of the axp288 are
	 * not used, check that the fuelgauge is enabled (CC_CTRL != 0).
	 */
	ret = regmap_read(axp20x->regmap, AXP20X_CC_CTRL, &val);
	if (ret < 0)
		goto unblock_punit_i2c_access;
	if (val == 0) {
		ret = -ENODEV;
		goto unblock_punit_i2c_access;
	}

	ret = fuel_gauge_reg_readb(info, AXP288_FG_DES_CAP1_REG);
	if (ret < 0)
		goto unblock_punit_i2c_access;
=======
	ret = fuel_gauge_reg_readb(info, AXP288_FG_DES_CAP1_REG);
=======
	ret = iosf_mbi_block_punit_i2c_access();
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (ret < 0)
		goto out_free_iio_chan;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

	/*
	 * On some devices the fuelgauge and charger parts of the axp288 are
	 * not used, check that the fuelgauge is enabled (CC_CTRL != 0).
	 */
	ret = regmap_read(axp20x->regmap, AXP20X_CC_CTRL, &val);
	if (ret < 0)
		goto unblock_punit_i2c_access;
	if (val == 0) {
		ret = -ENODEV;
		goto unblock_punit_i2c_access;
	}

	ret = fuel_gauge_reg_readb(info, AXP288_FG_DES_CAP1_REG);
	if (ret < 0)
		goto unblock_punit_i2c_access;

	if (!(ret & FG_DES_CAP1_VALID)) {
		dev_err(&pdev->dev, "axp288 not configured by firmware\n");
		ret = -ENODEV;
<<<<<<< HEAD
<<<<<<< HEAD
		goto unblock_punit_i2c_access;
=======
		goto out_free_iio_chan;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		goto unblock_punit_i2c_access;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	}

	ret = fuel_gauge_reg_readb(info, AXP20X_CHRG_CTRL1);
	if (ret < 0)
<<<<<<< HEAD
<<<<<<< HEAD
		goto unblock_punit_i2c_access;
=======
		goto out_free_iio_chan;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		goto unblock_punit_i2c_access;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	switch ((ret & CHRG_CCCV_CV_MASK) >> CHRG_CCCV_CV_BIT_POS) {
	case CHRG_CCCV_CV_4100MV:
		info->max_volt = 4100;
		break;
	case CHRG_CCCV_CV_4150MV:
		info->max_volt = 4150;
		break;
	case CHRG_CCCV_CV_4200MV:
		info->max_volt = 4200;
		break;
	case CHRG_CCCV_CV_4350MV:
		info->max_volt = 4350;
		break;
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	ret = fuel_gauge_reg_readb(info, AXP20X_PWR_OP_MODE);
	if (ret < 0)
		goto unblock_punit_i2c_access;
	info->pwr_op = ret;

	ret = fuel_gauge_reg_readb(info, AXP288_FG_LOW_CAP_REG);
	if (ret < 0)
		goto unblock_punit_i2c_access;
	info->low_cap = ret;

unblock_punit_i2c_access:
	iosf_mbi_unblock_punit_i2c_access();
	/* In case we arrive here by goto because of a register access error */
	if (ret < 0)
		goto out_free_iio_chan;

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	psy_cfg.drv_data = info;
	info->bat = power_supply_register(&pdev->dev, &fuel_gauge_desc, &psy_cfg);
	if (IS_ERR(info->bat)) {
		ret = PTR_ERR(info->bat);
		dev_err(&pdev->dev, "failed to register battery: %d\n", ret);
		goto out_free_iio_chan;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	fuel_gauge_init_irq(info, pdev);
=======
	fuel_gauge_create_debugfs(info);
	fuel_gauge_init_irq(info);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	fuel_gauge_init_irq(info, pdev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return 0;

out_free_iio_chan:
	for (i = 0; i < IIO_CHANNEL_NUM; i++)
		if (!IS_ERR_OR_NULL(info->iio_channel[i]))
			iio_channel_release(info->iio_channel[i]);

	return ret;
}

static const struct platform_device_id axp288_fg_id_table[] = {
	{ .name = DEV_NAME },
	{},
};
MODULE_DEVICE_TABLE(platform, axp288_fg_id_table);

static int axp288_fuel_gauge_remove(struct platform_device *pdev)
{
	struct axp288_fg_info *info = platform_get_drvdata(pdev);
	int i;

	power_supply_unregister(info->bat);
<<<<<<< HEAD
<<<<<<< HEAD
=======
	fuel_gauge_remove_debugfs(info);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	for (i = 0; i < AXP288_FG_INTR_NUM; i++)
		if (info->irq[i] >= 0)
			free_irq(info->irq[i], info);

	for (i = 0; i < IIO_CHANNEL_NUM; i++)
		iio_channel_release(info->iio_channel[i]);

	return 0;
}

static struct platform_driver axp288_fuel_gauge_driver = {
	.probe = axp288_fuel_gauge_probe,
	.remove = axp288_fuel_gauge_remove,
	.id_table = axp288_fg_id_table,
	.driver = {
		.name = DEV_NAME,
	},
};

module_platform_driver(axp288_fuel_gauge_driver);

MODULE_AUTHOR("Ramakrishna Pallala <ramakrishna.pallala@intel.com>");
MODULE_AUTHOR("Todd Brandt <todd.e.brandt@linux.intel.com>");
MODULE_DESCRIPTION("Xpower AXP288 Fuel Gauge Driver");
MODULE_LICENSE("GPL");
