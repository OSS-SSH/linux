/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_ACPI_H__
#define __INTEL_ACPI_H__

struct drm_i915_private;

#ifdef CONFIG_ACPI
void intel_register_dsm_handler(void);
void intel_unregister_dsm_handler(void);
<<<<<<< HEAD
<<<<<<< HEAD
void intel_dsm_get_bios_data_funcs_supported(struct drm_i915_private *i915);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void intel_dsm_get_bios_data_funcs_supported(struct drm_i915_private *i915);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void intel_acpi_device_id_update(struct drm_i915_private *i915);
#else
static inline void intel_register_dsm_handler(void) { return; }
static inline void intel_unregister_dsm_handler(void) { return; }
static inline
<<<<<<< HEAD
<<<<<<< HEAD
void intel_dsm_get_bios_data_funcs_supported(struct drm_i915_private *i915) { return; }
static inline
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void intel_dsm_get_bios_data_funcs_supported(struct drm_i915_private *i915) { return; }
static inline
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void intel_acpi_device_id_update(struct drm_i915_private *i915) { return; }
#endif /* CONFIG_ACPI */

#endif /* __INTEL_ACPI_H__ */
