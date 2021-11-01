// SPDX-License-Identifier: GPL-2.0-only
/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright (c) 2021, NVIDIA CORPORATION & AFFILIATES. All rights reserved
 *
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * Copyright (c) 2021, NVIDIA CORPORATION & AFFILIATES. All rights reserved
 *
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/device.h>
#include <linux/eventfd.h>
#include <linux/file.h>
#include <linux/interrupt.h>
#include <linux/iommu.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <linux/pci.h>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>
<<<<<<< HEAD
<<<<<<< HEAD

#include <linux/vfio_pci_core.h>

=======
#include <linux/vfio.h>
#include <linux/vgaarb.h>
#include <linux/nospec.h>
#include <linux/sched/mm.h>
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#include <linux/vfio_pci_core.h>

<<<<<<< HEAD
#define DRIVER_VERSION  "0.2"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#define DRIVER_AUTHOR   "Alex Williamson <alex.williamson@redhat.com>"
#define DRIVER_DESC     "VFIO PCI - User Level meta-driver"

static char ids[1024] __initdata;
module_param_string(ids, ids, sizeof(ids), 0);
MODULE_PARM_DESC(ids, "Initial PCI IDs to add to the vfio driver, format is \"vendor:device[:subvendor[:subdevice[:class[:class_mask]]]]\" and multiple comma separated entries can be specified");

static bool nointxmask;
module_param_named(nointxmask, nointxmask, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(nointxmask,
		  "Disable support for PCI 2.3 style INTx masking.  If this resolves problems for specific devices, report lspci -vvvxxx to linux-pci@vger.kernel.org so the device can be fixed automatically via the broken_intx_masking flag.");

#ifdef CONFIG_VFIO_PCI_VGA
static bool disable_vga;
module_param(disable_vga, bool, S_IRUGO);
MODULE_PARM_DESC(disable_vga, "Disable VGA resource access through vfio-pci");
#endif

static bool disable_idle_d3;
module_param(disable_idle_d3, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(disable_idle_d3,
		 "Disable using the PCI D3 low power state for idle, unused devices");

static bool enable_sriov;
#ifdef CONFIG_PCI_IOV
module_param(enable_sriov, bool, 0644);
MODULE_PARM_DESC(enable_sriov, "Enable support for SR-IOV configuration.  Enabling SR-IOV on a PF typically requires support of the userspace PF driver, enabling VFs without such support may result in non-functional VFs or PF.");
#endif

static bool disable_denylist;
module_param(disable_denylist, bool, 0444);
MODULE_PARM_DESC(disable_denylist, "Disable use of device denylist. Disabling the denylist allows binding to devices with known errata that may lead to exploitable stability or security issues when accessed by untrusted users.");

<<<<<<< HEAD
<<<<<<< HEAD
=======
static inline bool vfio_vga_disabled(void)
{
#ifdef CONFIG_VFIO_PCI_VGA
	return disable_vga;
#else
	return true;
#endif
}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static bool vfio_pci_dev_in_denylist(struct pci_dev *pdev)
{
	switch (pdev->vendor) {
	case PCI_VENDOR_ID_INTEL:
		switch (pdev->device) {
		case PCI_DEVICE_ID_INTEL_QAT_C3XXX:
		case PCI_DEVICE_ID_INTEL_QAT_C3XXX_VF:
		case PCI_DEVICE_ID_INTEL_QAT_C62X:
		case PCI_DEVICE_ID_INTEL_QAT_C62X_VF:
		case PCI_DEVICE_ID_INTEL_QAT_DH895XCC:
		case PCI_DEVICE_ID_INTEL_QAT_DH895XCC_VF:
			return true;
		default:
			return false;
		}
	}

	return false;
}

static bool vfio_pci_is_denylisted(struct pci_dev *pdev)
{
	if (!vfio_pci_dev_in_denylist(pdev))
		return false;

	if (disable_denylist) {
		pci_warn(pdev,
			 "device denylist disabled - allowing device %04x:%04x.\n",
			 pdev->vendor, pdev->device);
		return false;
	}

	pci_warn(pdev, "%04x:%04x exists in vfio-pci device denylist, driver probing disallowed.\n",
		 pdev->vendor, pdev->device);

	return true;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int vfio_pci_open_device(struct vfio_device *core_vdev)
{
	struct vfio_pci_core_device *vdev =
		container_of(core_vdev, struct vfio_pci_core_device, vdev);
	struct pci_dev *pdev = vdev->pdev;
	int ret;

	ret = vfio_pci_core_enable(vdev);
	if (ret)
		return ret;

=======
/*
 * Our VGA arbiter participation is limited since we don't know anything
 * about the device itself.  However, if the device is the only VGA device
 * downstream of a bridge and VFIO VGA support is disabled, then we can
 * safely return legacy VGA IO and memory as not decoded since the user
 * has no way to get to it and routing can be disabled externally at the
 * bridge.
 */
static unsigned int vfio_pci_set_vga_decode(void *opaque, bool single_vga)
{
	struct vfio_pci_device *vdev = opaque;
	struct pci_dev *tmp = NULL, *pdev = vdev->pdev;
	unsigned char max_busnr;
	unsigned int decodes;

	if (single_vga || !vfio_vga_disabled() || pci_is_root_bus(pdev->bus))
		return VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM |
		       VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;

	max_busnr = pci_bus_max_busnr(pdev->bus);
	decodes = VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;

	while ((tmp = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, tmp)) != NULL) {
		if (tmp == pdev ||
		    pci_domain_nr(tmp->bus) != pci_domain_nr(pdev->bus) ||
		    pci_is_root_bus(tmp->bus))
			continue;

		if (tmp->bus->number >= pdev->bus->number &&
		    tmp->bus->number <= max_busnr) {
			pci_dev_put(tmp);
			decodes |= VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
			break;
		}
	}

	return decodes;
}

static inline bool vfio_pci_is_vga(struct pci_dev *pdev)
{
	return (pdev->class >> 8) == PCI_CLASS_DISPLAY_VGA;
}

static void vfio_pci_probe_mmaps(struct vfio_pci_device *vdev)
{
	struct resource *res;
	int i;
	struct vfio_pci_dummy_resource *dummy_res;

	for (i = 0; i < PCI_STD_NUM_BARS; i++) {
		int bar = i + PCI_STD_RESOURCES;

		res = &vdev->pdev->resource[bar];

		if (!IS_ENABLED(CONFIG_VFIO_PCI_MMAP))
			goto no_mmap;

		if (!(res->flags & IORESOURCE_MEM))
			goto no_mmap;

		/*
		 * The PCI core shouldn't set up a resource with a
		 * type but zero size. But there may be bugs that
		 * cause us to do that.
		 */
		if (!resource_size(res))
			goto no_mmap;

		if (resource_size(res) >= PAGE_SIZE) {
			vdev->bar_mmap_supported[bar] = true;
			continue;
		}

		if (!(res->start & ~PAGE_MASK)) {
			/*
			 * Add a dummy resource to reserve the remainder
			 * of the exclusive page in case that hot-add
			 * device's bar is assigned into it.
			 */
			dummy_res = kzalloc(sizeof(*dummy_res), GFP_KERNEL);
			if (dummy_res == NULL)
				goto no_mmap;

			dummy_res->resource.name = "vfio sub-page reserved";
			dummy_res->resource.start = res->end + 1;
			dummy_res->resource.end = res->start + PAGE_SIZE - 1;
			dummy_res->resource.flags = res->flags;
			if (request_resource(res->parent,
						&dummy_res->resource)) {
				kfree(dummy_res);
				goto no_mmap;
			}
			dummy_res->index = bar;
			list_add(&dummy_res->res_next,
					&vdev->dummy_resources_list);
			vdev->bar_mmap_supported[bar] = true;
			continue;
		}
		/*
		 * Here we don't handle the case when the BAR is not page
		 * aligned because we can't expect the BAR will be
		 * assigned into the same location in a page in guest
		 * when we passthrough the BAR. And it's hard to access
		 * this BAR in userspace because we have no way to get
		 * the BAR's location in a page.
		 */
no_mmap:
		vdev->bar_mmap_supported[bar] = false;
	}
}

static void vfio_pci_try_bus_reset(struct vfio_pci_device *vdev);
static void vfio_pci_disable(struct vfio_pci_device *vdev);
static int vfio_pci_try_zap_and_vma_lock_cb(struct pci_dev *pdev, void *data);

/*
 * INTx masking requires the ability to disable INTx signaling via PCI_COMMAND
 * _and_ the ability detect when the device is asserting INTx via PCI_STATUS.
 * If a device implements the former but not the latter we would typically
 * expect broken_intx_masking be set and require an exclusive interrupt.
 * However since we do have control of the device's ability to assert INTx,
 * we can instead pretend that the device does not implement INTx, virtualizing
 * the pin register to report zero and maintaining DisINTx set on the host.
 */
static bool vfio_pci_nointx(struct pci_dev *pdev)
{
	switch (pdev->vendor) {
	case PCI_VENDOR_ID_INTEL:
		switch (pdev->device) {
		/* All i40e (XL710/X710/XXV710) 10/20/25/40GbE NICs */
		case 0x1572:
		case 0x1574:
		case 0x1580 ... 0x1581:
		case 0x1583 ... 0x158b:
		case 0x37d0 ... 0x37d2:
		/* X550 */
		case 0x1563:
			return true;
		default:
			return false;
		}
	}

	return false;
}

static void vfio_pci_probe_power_state(struct vfio_pci_device *vdev)
{
	struct pci_dev *pdev = vdev->pdev;
	u16 pmcsr;

	if (!pdev->pm_cap)
		return;

	pci_read_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &pmcsr);

	vdev->needs_pm_restore = !(pmcsr & PCI_PM_CTRL_NO_SOFT_RESET);
}

/*
 * pci_set_power_state() wrapper handling devices which perform a soft reset on
 * D3->D0 transition.  Save state prior to D0/1/2->D3, stash it on the vdev,
 * restore when returned to D0.  Saved separately from pci_saved_state for use
 * by PM capability emulation and separately from pci_dev internal saved state
 * to avoid it being overwritten and consumed around other resets.
 */
int vfio_pci_set_power_state(struct vfio_pci_device *vdev, pci_power_t state)
{
	struct pci_dev *pdev = vdev->pdev;
	bool needs_restore = false, needs_save = false;
	int ret;

	if (vdev->needs_pm_restore) {
		if (pdev->current_state < PCI_D3hot && state >= PCI_D3hot) {
			pci_save_state(pdev);
			needs_save = true;
		}

		if (pdev->current_state >= PCI_D3hot && state <= PCI_D0)
			needs_restore = true;
	}

	ret = pci_set_power_state(pdev, state);

	if (!ret) {
		/* D3 might be unsupported via quirk, skip unless in D3 */
		if (needs_save && pdev->current_state >= PCI_D3hot) {
			vdev->pm_save = pci_store_saved_state(pdev);
		} else if (needs_restore) {
			pci_load_and_free_saved_state(pdev, &vdev->pm_save);
			pci_restore_state(pdev);
		}
	}

	return ret;
}

static int vfio_pci_enable(struct vfio_pci_device *vdev)
=======
static int vfio_pci_open_device(struct vfio_device *core_vdev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct vfio_pci_core_device *vdev =
		container_of(core_vdev, struct vfio_pci_core_device, vdev);
	struct pci_dev *pdev = vdev->pdev;
	int ret;

	ret = vfio_pci_core_enable(vdev);
	if (ret)
		return ret;

<<<<<<< HEAD
	/* If reset fails because of the device lock, fail this path entirely */
	ret = pci_try_reset_function(pdev);
	if (ret == -EAGAIN) {
		pci_disable_device(pdev);
		return ret;
	}

	vdev->reset_works = !ret;
	pci_save_state(pdev);
	vdev->pci_saved_state = pci_store_saved_state(pdev);
	if (!vdev->pci_saved_state)
		pci_dbg(pdev, "%s: Couldn't store saved state\n", __func__);

	if (likely(!nointxmask)) {
		if (vfio_pci_nointx(pdev)) {
			pci_info(pdev, "Masking broken INTx support\n");
			vdev->nointx = true;
			pci_intx(pdev, 0);
		} else
			vdev->pci_2_3 = pci_intx_mask_supported(pdev);
	}

	pci_read_config_word(pdev, PCI_COMMAND, &cmd);
	if (vdev->pci_2_3 && (cmd & PCI_COMMAND_INTX_DISABLE)) {
		cmd &= ~PCI_COMMAND_INTX_DISABLE;
		pci_write_config_word(pdev, PCI_COMMAND, cmd);
	}

	ret = vfio_config_init(vdev);
	if (ret) {
		kfree(vdev->pci_saved_state);
		vdev->pci_saved_state = NULL;
		pci_disable_device(pdev);
		return ret;
	}

	msix_pos = pdev->msix_cap;
	if (msix_pos) {
		u16 flags;
		u32 table;

		pci_read_config_word(pdev, msix_pos + PCI_MSIX_FLAGS, &flags);
		pci_read_config_dword(pdev, msix_pos + PCI_MSIX_TABLE, &table);

		vdev->msix_bar = table & PCI_MSIX_TABLE_BIR;
		vdev->msix_offset = table & PCI_MSIX_TABLE_OFFSET;
		vdev->msix_size = ((flags & PCI_MSIX_FLAGS_QSIZE) + 1) * 16;
	} else
		vdev->msix_bar = 0xFF;

	if (!vfio_vga_disabled() && vfio_pci_is_vga(pdev))
		vdev->has_vga = true;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (vfio_pci_is_vga(pdev) &&
	    pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    IS_ENABLED(CONFIG_VFIO_PCI_IGD)) {
		ret = vfio_pci_igd_init(vdev);
		if (ret && ret != -ENODEV) {
			pci_warn(pdev, "Failed to setup Intel IGD regions\n");
<<<<<<< HEAD
<<<<<<< HEAD
			vfio_pci_core_disable(vdev);
			return ret;
		}
	}

	vfio_pci_core_finish_enable(vdev);

	return 0;
}

static const struct vfio_device_ops vfio_pci_ops = {
	.name		= "vfio-pci",
	.open_device	= vfio_pci_open_device,
	.close_device	= vfio_pci_core_close_device,
	.ioctl		= vfio_pci_core_ioctl,
	.read		= vfio_pci_core_read,
	.write		= vfio_pci_core_write,
	.mmap		= vfio_pci_core_mmap,
	.request	= vfio_pci_core_request,
	.match		= vfio_pci_core_match,
};

static int vfio_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct vfio_pci_core_device *vdev;
	int ret;

	if (vfio_pci_is_denylisted(pdev))
		return -EINVAL;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev)
		return -ENOMEM;
	vfio_pci_core_init_device(vdev, pdev, &vfio_pci_ops);

	ret = vfio_pci_core_register_device(vdev);
	if (ret)
		goto out_free;
	dev_set_drvdata(&pdev->dev, vdev);
	return 0;

out_free:
	vfio_pci_core_uninit_device(vdev);
	kfree(vdev);
	return ret;
}

static void vfio_pci_remove(struct pci_dev *pdev)
{
	struct vfio_pci_core_device *vdev = dev_get_drvdata(&pdev->dev);

	vfio_pci_core_unregister_device(vdev);
	vfio_pci_core_uninit_device(vdev);
	kfree(vdev);
}

static int vfio_pci_sriov_configure(struct pci_dev *pdev, int nr_virtfn)
{
	if (!enable_sriov)
		return -ENOENT;

	return vfio_pci_core_sriov_configure(pdev, nr_virtfn);
}

static const struct pci_device_id vfio_pci_table[] = {
	{ PCI_DRIVER_OVERRIDE_DEVICE_VFIO(PCI_ANY_ID, PCI_ANY_ID) }, /* match all by default */
	{}
};

MODULE_DEVICE_TABLE(pci, vfio_pci_table);

static struct pci_driver vfio_pci_driver = {
	.name			= "vfio-pci",
	.id_table		= vfio_pci_table,
	.probe			= vfio_pci_probe,
	.remove			= vfio_pci_remove,
	.sriov_configure	= vfio_pci_sriov_configure,
	.err_handler		= &vfio_pci_core_err_handlers,
};

static void __init vfio_pci_fill_ids(void)
{
	char *p, *id;
	int rc;

	/* no ids passed actually */
	if (ids[0] == '\0')
		return;

	/* add ids specified in the module parameter */
	p = ids;
	while ((id = strsep(&p, ","))) {
		unsigned int vendor, device, subvendor = PCI_ANY_ID,
			subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
		int fields;

		if (!strlen(id))
			continue;

		fields = sscanf(id, "%x:%x:%x:%x:%x:%x",
				&vendor, &device, &subvendor, &subdevice,
				&class, &class_mask);

		if (fields < 2) {
			pr_warn("invalid id string \"%s\"\n", id);
			continue;
		}

		rc = pci_add_dynid(&vfio_pci_driver, vendor, device,
				   subvendor, subdevice, class, class_mask, 0);
		if (rc)
			pr_warn("failed to add dynamic id [%04x:%04x[%04x:%04x]] class %#08x/%08x (%d)\n",
				vendor, device, subvendor, subdevice,
				class, class_mask, rc);
		else
			pr_info("add [%04x:%04x[%04x:%04x]] class %#08x/%08x\n",
				vendor, device, subvendor, subdevice,
				class, class_mask);
	}
}

static int __init vfio_pci_init(void)
{
	int ret;
	bool is_disable_vga = true;

#ifdef CONFIG_VFIO_PCI_VGA
	is_disable_vga = disable_vga;
#endif

	vfio_pci_core_set_params(nointxmask, is_disable_vga, disable_idle_d3);

	/* Register and scan for devices */
	ret = pci_register_driver(&vfio_pci_driver);
	if (ret)
		return ret;

	vfio_pci_fill_ids();

	if (disable_denylist)
		pr_warn("device denylist disabled.\n");

	return 0;
}
module_init(vfio_pci_init);

static void __exit vfio_pci_cleanup(void)
{
	pci_unregister_driver(&vfio_pci_driver);
}
module_exit(vfio_pci_cleanup);

=======
			goto disable_exit;
=======
			vfio_pci_core_disable(vdev);
			return ret;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		}
	}

	vfio_pci_core_finish_enable(vdev);

	return 0;
}

static const struct vfio_device_ops vfio_pci_ops = {
	.name		= "vfio-pci",
	.open_device	= vfio_pci_open_device,
	.close_device	= vfio_pci_core_close_device,
	.ioctl		= vfio_pci_core_ioctl,
	.read		= vfio_pci_core_read,
	.write		= vfio_pci_core_write,
	.mmap		= vfio_pci_core_mmap,
	.request	= vfio_pci_core_request,
	.match		= vfio_pci_core_match,
};

static int vfio_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct vfio_pci_core_device *vdev;
	int ret;

	if (vfio_pci_is_denylisted(pdev))
		return -EINVAL;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev)
		return -ENOMEM;
	vfio_pci_core_init_device(vdev, pdev, &vfio_pci_ops);

	ret = vfio_pci_core_register_device(vdev);
	if (ret)
		goto out_free;
	dev_set_drvdata(&pdev->dev, vdev);
	return 0;

out_free:
	vfio_pci_core_uninit_device(vdev);
	kfree(vdev);
	return ret;
}

static void vfio_pci_remove(struct pci_dev *pdev)
{
	struct vfio_pci_core_device *vdev = dev_get_drvdata(&pdev->dev);

	vfio_pci_core_unregister_device(vdev);
	vfio_pci_core_uninit_device(vdev);
	kfree(vdev);
}

static int vfio_pci_sriov_configure(struct pci_dev *pdev, int nr_virtfn)
{
	if (!enable_sriov)
		return -ENOENT;

	return vfio_pci_core_sriov_configure(pdev, nr_virtfn);
}

static const struct pci_device_id vfio_pci_table[] = {
	{ PCI_DRIVER_OVERRIDE_DEVICE_VFIO(PCI_ANY_ID, PCI_ANY_ID) }, /* match all by default */
	{}
};

MODULE_DEVICE_TABLE(pci, vfio_pci_table);

static struct pci_driver vfio_pci_driver = {
	.name			= "vfio-pci",
	.id_table		= vfio_pci_table,
	.probe			= vfio_pci_probe,
	.remove			= vfio_pci_remove,
	.sriov_configure	= vfio_pci_sriov_configure,
	.err_handler		= &vfio_pci_core_err_handlers,
};

static void __init vfio_pci_fill_ids(void)
{
	char *p, *id;
	int rc;

	/* no ids passed actually */
	if (ids[0] == '\0')
		return;

	/* add ids specified in the module parameter */
	p = ids;
	while ((id = strsep(&p, ","))) {
		unsigned int vendor, device, subvendor = PCI_ANY_ID,
			subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
		int fields;

		if (!strlen(id))
			continue;

		fields = sscanf(id, "%x:%x:%x:%x:%x:%x",
				&vendor, &device, &subvendor, &subdevice,
				&class, &class_mask);

		if (fields < 2) {
			pr_warn("invalid id string \"%s\"\n", id);
			continue;
		}

		rc = pci_add_dynid(&vfio_pci_driver, vendor, device,
				   subvendor, subdevice, class, class_mask, 0);
		if (rc)
			pr_warn("failed to add dynamic id [%04x:%04x[%04x:%04x]] class %#08x/%08x (%d)\n",
				vendor, device, subvendor, subdevice,
				class, class_mask, rc);
		else
			pr_info("add [%04x:%04x[%04x:%04x]] class %#08x/%08x\n",
				vendor, device, subvendor, subdevice,
				class, class_mask);
	}
}

static int __init vfio_pci_init(void)
{
	int ret;
	bool is_disable_vga = true;

#ifdef CONFIG_VFIO_PCI_VGA
	is_disable_vga = disable_vga;
#endif

	vfio_pci_core_set_params(nointxmask, is_disable_vga, disable_idle_d3);

	/* Register and scan for devices */
	ret = pci_register_driver(&vfio_pci_driver);
	if (ret)
		return ret;

	vfio_pci_fill_ids();

	if (disable_denylist)
		pr_warn("device denylist disabled.\n");

	return 0;
}
module_init(vfio_pci_init);

static void __exit vfio_pci_cleanup(void)
{
	pci_unregister_driver(&vfio_pci_driver);
}
module_exit(vfio_pci_cleanup);

<<<<<<< HEAD
MODULE_VERSION(DRIVER_VERSION);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
