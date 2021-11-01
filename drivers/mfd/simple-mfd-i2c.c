// SPDX-License-Identifier: GPL-2.0-only
/*
 * Simple MFD - I2C
 *
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * Author(s):
 * 	Michael Walle <michael@walle.cc>
 * 	Lee Jones <lee.jones@linaro.org>
 *
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * This driver creates a single register map with the intention for it to be
 * shared by all sub-devices.  Children can use their parent's device structure
 * (dev.parent) in order to reference it.
 *
 * Once the register map has been successfully initialised, any sub-devices
<<<<<<< HEAD
<<<<<<< HEAD
 * represented by child nodes in Device Tree or via the MFD cells in this file
 * will be subsequently registered.
=======
 * represented by child nodes in Device Tree will be subsequently registered.
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * represented by child nodes in Device Tree or via the MFD cells in this file
 * will be subsequently registered.
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 */

#include <linux/i2c.h>
#include <linux/kernel.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/mfd/core.h>
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <linux/mfd/core.h>
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/regmap.h>

<<<<<<< HEAD
<<<<<<< HEAD
#include "simple-mfd-i2c.h"

static const struct regmap_config regmap_config_8r_8v = {
=======
static const struct regmap_config simple_regmap_config = {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include "simple-mfd-i2c.h"

static const struct regmap_config regmap_config_8r_8v = {
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	.reg_bits = 8,
	.val_bits = 8,
};

static int simple_mfd_i2c_probe(struct i2c_client *i2c)
{
<<<<<<< HEAD
<<<<<<< HEAD
	const struct simple_mfd_data *simple_mfd_data;
	const struct regmap_config *regmap_config;
	struct regmap *regmap;
	int ret;

	simple_mfd_data = device_get_match_data(&i2c->dev);

	/* If no regmap_config is specified, use the default 8reg and 8val bits */
	if (!simple_mfd_data || !simple_mfd_data->regmap_config)
		regmap_config = &regmap_config_8r_8v;
	else
		regmap_config = simple_mfd_data->regmap_config;

	regmap = devm_regmap_init_i2c(i2c, regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* If no MFD cells are spedified, use register the DT child nodes instead */
	if (!simple_mfd_data || !simple_mfd_data->mfd_cell)
		return devm_of_platform_populate(&i2c->dev);

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO,
				   simple_mfd_data->mfd_cell,
				   simple_mfd_data->mfd_cell_size,
				   NULL, 0, NULL);
	if (ret)
		dev_err(&i2c->dev, "Failed to add child devices\n");

	return ret;
=======
	const struct regmap_config *config;
=======
	const struct simple_mfd_data *simple_mfd_data;
	const struct regmap_config *regmap_config;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct regmap *regmap;
	int ret;

	simple_mfd_data = device_get_match_data(&i2c->dev);

	/* If no regmap_config is specified, use the default 8reg and 8val bits */
	if (!simple_mfd_data || !simple_mfd_data->regmap_config)
		regmap_config = &regmap_config_8r_8v;
	else
		regmap_config = simple_mfd_data->regmap_config;

	regmap = devm_regmap_init_i2c(i2c, regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

<<<<<<< HEAD
	return devm_of_platform_populate(&i2c->dev);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	/* If no MFD cells are spedified, use register the DT child nodes instead */
	if (!simple_mfd_data || !simple_mfd_data->mfd_cell)
		return devm_of_platform_populate(&i2c->dev);

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO,
				   simple_mfd_data->mfd_cell,
				   simple_mfd_data->mfd_cell_size,
				   NULL, 0, NULL);
	if (ret)
		dev_err(&i2c->dev, "Failed to add child devices\n");

	return ret;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static const struct of_device_id simple_mfd_i2c_of_match[] = {
	{ .compatible = "kontron,sl28cpld" },
	{}
};
MODULE_DEVICE_TABLE(of, simple_mfd_i2c_of_match);

static struct i2c_driver simple_mfd_i2c_driver = {
	.probe_new = simple_mfd_i2c_probe,
	.driver = {
		.name = "simple-mfd-i2c",
		.of_match_table = simple_mfd_i2c_of_match,
	},
};
module_i2c_driver(simple_mfd_i2c_driver);

MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_DESCRIPTION("Simple MFD - I2C driver");
MODULE_LICENSE("GPL v2");
