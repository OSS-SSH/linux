// SPDX-License-Identifier: GPL-2.0-only
/*
 * arch/arm/mach-tegra/board-paz00.c
 *
 * Copyright (C) 2011 Marc Dietrich <marvin24@gmx.de>
 *
 * Based on board-harmony.c
 * Copyright (C) 2010 Google, Inc.
 */

#include <linux/property.h>
#include <linux/gpio/machine.h>
#include <linux/platform_device.h>

#include "board.h"

static struct property_entry wifi_rfkill_prop[] __initdata = {
	PROPERTY_ENTRY_STRING("name", "wifi_rfkill"),
	PROPERTY_ENTRY_STRING("type", "wlan"),
	{ },
};

static struct platform_device wifi_rfkill_device = {
	.name	= "rfkill_gpio",
	.id	= -1,
};

static struct gpiod_lookup_table wifi_gpio_lookup = {
	.dev_id = "rfkill_gpio",
	.table = {
		GPIO_LOOKUP("tegra-gpio", 25, "reset", 0),
		GPIO_LOOKUP("tegra-gpio", 85, "shutdown", 0),
		{ },
	},
};

void __init tegra_paz00_wifikill_init(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
	device_create_managed_software_node(&wifi_rfkill_device.dev, wifi_rfkill_prop, NULL);
=======
	platform_device_add_properties(&wifi_rfkill_device, wifi_rfkill_prop);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	device_create_managed_software_node(&wifi_rfkill_device.dev, wifi_rfkill_prop, NULL);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	gpiod_add_lookup_table(&wifi_gpio_lookup);
	platform_device_register(&wifi_rfkill_device);
}
