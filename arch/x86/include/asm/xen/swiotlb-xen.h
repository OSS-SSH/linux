/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_SWIOTLB_XEN_H
#define _ASM_X86_SWIOTLB_XEN_H

#ifdef CONFIG_SWIOTLB_XEN
<<<<<<< HEAD
<<<<<<< HEAD
extern int __init pci_xen_swiotlb_detect(void);
extern int pci_xen_swiotlb_init_late(void);
#else
#define pci_xen_swiotlb_detect NULL
=======
extern int xen_swiotlb;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
extern int __init pci_xen_swiotlb_detect(void);
extern int pci_xen_swiotlb_init_late(void);
#else
<<<<<<< HEAD
#define xen_swiotlb (0)
static inline int __init pci_xen_swiotlb_detect(void) { return 0; }
static inline void __init pci_xen_swiotlb_init(void) { }
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#define pci_xen_swiotlb_detect NULL
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static inline int pci_xen_swiotlb_init_late(void) { return -ENXIO; }
#endif

#endif /* _ASM_X86_SWIOTLB_XEN_H */
