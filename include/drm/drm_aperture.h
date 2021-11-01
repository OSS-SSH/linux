/* SPDX-License-Identifier: MIT */

#ifndef _DRM_APERTURE_H_
#define _DRM_APERTURE_H_

#include <linux/types.h>

struct drm_device;
<<<<<<< HEAD
<<<<<<< HEAD
struct drm_driver;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
struct drm_driver;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
struct pci_dev;

int devm_aperture_acquire_from_firmware(struct drm_device *dev, resource_size_t base,
					resource_size_t size);

int drm_aperture_remove_conflicting_framebuffers(resource_size_t base, resource_size_t size,
<<<<<<< HEAD
<<<<<<< HEAD
						 bool primary, const struct drm_driver *req_driver);

int drm_aperture_remove_conflicting_pci_framebuffers(struct pci_dev *pdev,
						     const struct drm_driver *req_driver);
=======
						 bool primary, const char *name);

int drm_aperture_remove_conflicting_pci_framebuffers(struct pci_dev *pdev, const char *name);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
						 bool primary, const struct drm_driver *req_driver);

int drm_aperture_remove_conflicting_pci_framebuffers(struct pci_dev *pdev,
						     const struct drm_driver *req_driver);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

/**
 * drm_aperture_remove_framebuffers - remove all existing framebuffers
 * @primary: also kick vga16fb if present
<<<<<<< HEAD
<<<<<<< HEAD
 * @req_driver: requesting DRM driver
=======
 * @name: requesting driver name
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * @req_driver: requesting DRM driver
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 *
 * This function removes all graphics device drivers. Use this function on systems
 * that can have their framebuffer located anywhere in memory.
 *
 * Returns:
 * 0 on success, or a negative errno code otherwise
 */
<<<<<<< HEAD
<<<<<<< HEAD
static inline int
drm_aperture_remove_framebuffers(bool primary, const struct drm_driver *req_driver)
{
	return drm_aperture_remove_conflicting_framebuffers(0, (resource_size_t)-1, primary,
							    req_driver);
=======
static inline int drm_aperture_remove_framebuffers(bool primary, const char *name)
{
	return drm_aperture_remove_conflicting_framebuffers(0, (resource_size_t)-1, primary, name);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static inline int
drm_aperture_remove_framebuffers(bool primary, const struct drm_driver *req_driver)
{
	return drm_aperture_remove_conflicting_framebuffers(0, (resource_size_t)-1, primary,
							    req_driver);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

#endif
