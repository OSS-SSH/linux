/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */

#ifndef __PANFROST_MMU_H__
#define __PANFROST_MMU_H__

struct panfrost_gem_mapping;
struct panfrost_file_priv;
struct panfrost_mmu;

int panfrost_mmu_map(struct panfrost_gem_mapping *mapping);
void panfrost_mmu_unmap(struct panfrost_gem_mapping *mapping);

int panfrost_mmu_init(struct panfrost_device *pfdev);
void panfrost_mmu_fini(struct panfrost_device *pfdev);
void panfrost_mmu_reset(struct panfrost_device *pfdev);

u32 panfrost_mmu_as_get(struct panfrost_device *pfdev, struct panfrost_mmu *mmu);
void panfrost_mmu_as_put(struct panfrost_device *pfdev, struct panfrost_mmu *mmu);

<<<<<<< HEAD
<<<<<<< HEAD
struct panfrost_mmu *panfrost_mmu_ctx_get(struct panfrost_mmu *mmu);
void panfrost_mmu_ctx_put(struct panfrost_mmu *mmu);
struct panfrost_mmu *panfrost_mmu_ctx_create(struct panfrost_device *pfdev);
=======
int panfrost_mmu_pgtable_alloc(struct panfrost_file_priv *priv);
void panfrost_mmu_pgtable_free(struct panfrost_file_priv *priv);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
struct panfrost_mmu *panfrost_mmu_ctx_get(struct panfrost_mmu *mmu);
void panfrost_mmu_ctx_put(struct panfrost_mmu *mmu);
struct panfrost_mmu *panfrost_mmu_ctx_create(struct panfrost_device *pfdev);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif
