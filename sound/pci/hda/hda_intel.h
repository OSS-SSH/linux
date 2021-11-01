/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 */
#ifndef __SOUND_HDA_INTEL_H
#define __SOUND_HDA_INTEL_H

#include "hda_controller.h"

struct hda_intel {
	struct azx chip;

	/* for pending irqs */
	struct work_struct irq_pending_work;

	/* sync probing */
	struct completion probe_wait;
<<<<<<< HEAD
<<<<<<< HEAD
	struct delayed_work probe_work;
=======
	struct work_struct probe_work;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct delayed_work probe_work;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* card list (for power_save trigger) */
	struct list_head list;

	/* extra flags */
	unsigned int irq_pending_warned:1;
	unsigned int probe_continued:1;

	/* vga_switcheroo setup */
	unsigned int use_vga_switcheroo:1;
	unsigned int vga_switcheroo_registered:1;
	unsigned int init_failed:1; /* delayed init failed */
	unsigned int freed:1; /* resources already released */

	bool need_i915_power:1; /* the hda controller needs i915 power */
<<<<<<< HEAD
<<<<<<< HEAD

	int probe_retry;	/* being probe-retry */
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

	int probe_retry;	/* being probe-retry */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

#endif
