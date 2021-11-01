/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_SWIOTLB_XEN_H
#define _ASM_X86_SWIOTLB_XEN_H

#ifdef CONFIG_SWIOTLB_XEN
<<<<<<< HEAD
extern int __init pci_xen_swiotlb_detect(void);
extern int pci_xen_swiotlb_init_late(void);
#else
#define pci_xen_swiotlb_detect NULL
=======
extern int xen_swiotlb;
extern int __init pci_xen_swiotlb_detect(void);
extern void __init pci_xen_swiotlb_init(void);
extern int pci_xen_swiotlb_init_late(void);
#else
#define xen_swiotlb (0)
static inline int __init pci_xen_swiotlb_detect(void) { return 0; }
static inline void __init pci_xen_swiotlb_init(void) { }
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
static inline int pci_xen_swiotlb_init_late(void) { return -ENXIO; }
#endif

#endif /* _ASM_X86_SWIOTLB_XEN_H */
