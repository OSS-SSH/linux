// SPDX-License-Identifier: GPL-2.0
/*
 * Implement the sparc iomap interfaces
 */
#include <linux/pci.h>
#include <linux/module.h>
#include <asm/io.h>

/* Create a virtual mapping cookie for an IO port range */
void __iomem *ioport_map(unsigned long port, unsigned int nr)
{
	return (void __iomem *) (unsigned long) port;
}

void ioport_unmap(void __iomem *addr)
{
	/* Nothing to do */
}
EXPORT_SYMBOL(ioport_map);
EXPORT_SYMBOL(ioport_unmap);

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_PCI
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifdef CONFIG_PCI
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void pci_iounmap(struct pci_dev *dev, void __iomem * addr)
{
	/* nothing to do */
}
EXPORT_SYMBOL(pci_iounmap);
<<<<<<< HEAD
<<<<<<< HEAD
#endif
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#endif
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
