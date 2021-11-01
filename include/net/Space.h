/* SPDX-License-Identifier: GPL-2.0 */
/* A unified ethernet device probe.  This is the easiest way to have every
 * ethernet adaptor have the name "eth[0123...]".
 */

struct net_device *hp100_probe(int unit);
struct net_device *ultra_probe(int unit);
struct net_device *wd_probe(int unit);
struct net_device *ne_probe(int unit);
struct net_device *fmv18x_probe(int unit);
<<<<<<< HEAD
<<<<<<< HEAD
struct net_device *ni65_probe(int unit);
struct net_device *sonic_probe(int unit);
struct net_device *smc_init(int unit);
struct net_device *cs89x0_probe(int unit);
struct net_device *tc515_probe(int unit);
struct net_device *lance_probe(int unit);
struct net_device *cops_probe(int unit);

/* Fibre Channel adapters */
int iph5526_probe(struct net_device *dev);
=======
struct net_device *i82596_probe(int unit);
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
struct net_device *ni65_probe(int unit);
struct net_device *sonic_probe(int unit);
struct net_device *smc_init(int unit);
struct net_device *cs89x0_probe(int unit);
struct net_device *tc515_probe(int unit);
struct net_device *lance_probe(int unit);
struct net_device *cops_probe(int unit);

/* Fibre Channel adapters */
int iph5526_probe(struct net_device *dev);
<<<<<<< HEAD

/* SBNI adapters */
int sbni_probe(int unit);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
