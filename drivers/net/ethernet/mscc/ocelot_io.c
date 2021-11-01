// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/*
 * Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 */
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

#include "ocelot.h"

u32 __ocelot_read_ix(struct ocelot *ocelot, u32 reg, u32 offset)
{
	u16 target = reg >> TARGET_OFFSET;
	u32 val;

	WARN_ON(!target);

	regmap_read(ocelot->targets[target],
		    ocelot->map[target][reg & REG_MASK] + offset, &val);
	return val;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(__ocelot_read_ix);
=======
EXPORT_SYMBOL(__ocelot_read_ix);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(__ocelot_read_ix);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

void __ocelot_write_ix(struct ocelot *ocelot, u32 val, u32 reg, u32 offset)
{
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_write(ocelot->targets[target],
		     ocelot->map[target][reg & REG_MASK] + offset, val);
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(__ocelot_write_ix);
=======
EXPORT_SYMBOL(__ocelot_write_ix);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(__ocelot_write_ix);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

void __ocelot_rmw_ix(struct ocelot *ocelot, u32 val, u32 mask, u32 reg,
		     u32 offset)
{
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_update_bits(ocelot->targets[target],
			   ocelot->map[target][reg & REG_MASK] + offset,
			   mask, val);
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(__ocelot_rmw_ix);
=======
EXPORT_SYMBOL(__ocelot_rmw_ix);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(__ocelot_rmw_ix);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

u32 ocelot_port_readl(struct ocelot_port *port, u32 reg)
{
	struct ocelot *ocelot = port->ocelot;
	u16 target = reg >> TARGET_OFFSET;
	u32 val;

	WARN_ON(!target);

	regmap_read(port->target, ocelot->map[target][reg & REG_MASK], &val);
	return val;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(ocelot_port_readl);
=======
EXPORT_SYMBOL(ocelot_port_readl);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(ocelot_port_readl);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

void ocelot_port_writel(struct ocelot_port *port, u32 val, u32 reg)
{
	struct ocelot *ocelot = port->ocelot;
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_write(port->target, ocelot->map[target][reg & REG_MASK], val);
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(ocelot_port_writel);
=======
EXPORT_SYMBOL(ocelot_port_writel);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(ocelot_port_writel);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

void ocelot_port_rmwl(struct ocelot_port *port, u32 val, u32 mask, u32 reg)
{
	u32 cur = ocelot_port_readl(port, reg);

	ocelot_port_writel(port, (cur & (~mask)) | val, reg);
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(ocelot_port_rmwl);
=======
EXPORT_SYMBOL(ocelot_port_rmwl);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(ocelot_port_rmwl);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

u32 __ocelot_target_read_ix(struct ocelot *ocelot, enum ocelot_target target,
			    u32 reg, u32 offset)
{
	u32 val;

	regmap_read(ocelot->targets[target],
		    ocelot->map[target][reg] + offset, &val);
	return val;
}

void __ocelot_target_write_ix(struct ocelot *ocelot, enum ocelot_target target,
			      u32 val, u32 reg, u32 offset)
{
	regmap_write(ocelot->targets[target],
		     ocelot->map[target][reg] + offset, val);
}

int ocelot_regfields_init(struct ocelot *ocelot,
			  const struct reg_field *const regfields)
{
	unsigned int i;
	u16 target;

	for (i = 0; i < REGFIELD_MAX; i++) {
		struct reg_field regfield = {};
		u32 reg = regfields[i].reg;

		if (!reg)
			continue;

		target = regfields[i].reg >> TARGET_OFFSET;

		regfield.reg = ocelot->map[target][reg & REG_MASK];
		regfield.lsb = regfields[i].lsb;
		regfield.msb = regfields[i].msb;
		regfield.id_size = regfields[i].id_size;
		regfield.id_offset = regfields[i].id_offset;

		ocelot->regfields[i] =
		devm_regmap_field_alloc(ocelot->dev,
					ocelot->targets[target],
					regfield);

		if (IS_ERR(ocelot->regfields[i]))
			return PTR_ERR(ocelot->regfields[i]);
	}

	return 0;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(ocelot_regfields_init);
=======
EXPORT_SYMBOL(ocelot_regfields_init);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(ocelot_regfields_init);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

static struct regmap_config ocelot_regmap_config = {
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
};

struct regmap *ocelot_regmap_init(struct ocelot *ocelot, struct resource *res)
{
	void __iomem *regs;

	regs = devm_ioremap_resource(ocelot->dev, res);
	if (IS_ERR(regs))
		return ERR_CAST(regs);

	ocelot_regmap_config.name = res->name;

	return devm_regmap_init_mmio(ocelot->dev, regs, &ocelot_regmap_config);
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL_GPL(ocelot_regmap_init);
=======
EXPORT_SYMBOL(ocelot_regmap_init);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
EXPORT_SYMBOL_GPL(ocelot_regmap_init);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
