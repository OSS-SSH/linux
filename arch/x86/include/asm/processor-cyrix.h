/* SPDX-License-Identifier: GPL-2.0 */
/*
 * NSC/Cyrix CPU indexed register access. Must be inlined instead of
 * macros to ensure correct access ordering
 * Access order is always 0x22 (=offset), 0x23 (=value)
 */

<<<<<<< HEAD
<<<<<<< HEAD
#include <asm/pc-conf-reg.h>

static inline u8 getCx86(u8 reg)
{
	return pc_conf_get(reg);
=======
static inline u8 getCx86(u8 reg)
{
	outb(reg, 0x22);
	return inb(0x23);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <asm/pc-conf-reg.h>

static inline u8 getCx86(u8 reg)
{
	return pc_conf_get(reg);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static inline void setCx86(u8 reg, u8 data)
{
<<<<<<< HEAD
<<<<<<< HEAD
	pc_conf_set(reg, data);
=======
	outb(reg, 0x22);
	outb(data, 0x23);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	pc_conf_set(reg, data);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}
