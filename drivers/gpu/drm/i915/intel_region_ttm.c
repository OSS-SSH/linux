// SPDX-License-Identifier: MIT
/*
 * Copyright © 2021 Intel Corporation
 */
#include <drm/ttm/ttm_bo_driver.h>
#include <drm/ttm/ttm_device.h>
#include <drm/ttm/ttm_range_manager.h>

#include "i915_drv.h"
#include "i915_scatterlist.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include "i915_ttm_buddy_manager.h"

#include "intel_region_ttm.h"

#include "gem/i915_gem_ttm.h" /* For the funcs/ops export only */
<<<<<<< HEAD
=======

#include "intel_region_ttm.h"

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/**
 * DOC: TTM support structure
 *
 * The code in this file deals with setting up memory managers for TTM
 * LMEM and MOCK regions and converting the output from
 * the managers to struct sg_table, Basically providing the mapping from
 * i915 GEM regions to TTM memory types and resource managers.
 */

<<<<<<< HEAD
<<<<<<< HEAD
=======
/* A Zero-initialized driver for now. We don't have a TTM backend yet. */
static struct ttm_device_funcs i915_ttm_bo_driver;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/**
 * intel_region_ttm_device_init - Initialize a TTM device
 * @dev_priv: Pointer to an i915 device private structure.
 *
 * Return: 0 on success, negative error code on failure.
 */
int intel_region_ttm_device_init(struct drm_i915_private *dev_priv)
{
	struct drm_device *drm = &dev_priv->drm;

<<<<<<< HEAD
<<<<<<< HEAD
	return ttm_device_init(&dev_priv->bdev, i915_ttm_driver(),
=======
	return ttm_device_init(&dev_priv->bdev, &i915_ttm_bo_driver,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return ttm_device_init(&dev_priv->bdev, i915_ttm_driver(),
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			       drm->dev, drm->anon_inode->i_mapping,
			       drm->vma_offset_manager, false, false);
}

/**
 * intel_region_ttm_device_fini - Finalize a TTM device
 * @dev_priv: Pointer to an i915 device private structure.
 */
void intel_region_ttm_device_fini(struct drm_i915_private *dev_priv)
{
	ttm_device_fini(&dev_priv->bdev);
}

/*
 * Map the i915 memory regions to TTM memory types. We use the
 * driver-private types for now, reserving TTM_PL_VRAM for stolen
 * memory and TTM_PL_TT for GGTT use if decided to implement this.
 */
<<<<<<< HEAD
<<<<<<< HEAD
int intel_region_to_ttm_type(const struct intel_memory_region *mem)
=======
static int intel_region_to_ttm_type(struct intel_memory_region *mem)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
int intel_region_to_ttm_type(const struct intel_memory_region *mem)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int type;

	GEM_BUG_ON(mem->type != INTEL_MEMORY_LOCAL &&
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		   mem->type != INTEL_MEMORY_MOCK &&
		   mem->type != INTEL_MEMORY_SYSTEM);

	if (mem->type == INTEL_MEMORY_SYSTEM)
		return TTM_PL_SYSTEM;
<<<<<<< HEAD
=======
		   mem->type != INTEL_MEMORY_MOCK);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	type = mem->instance + TTM_PL_PRIV;
	GEM_BUG_ON(type >= TTM_NUM_MEM_TYPES);

	return type;
}

<<<<<<< HEAD
<<<<<<< HEAD
/**
 * intel_region_ttm_init - Initialize a memory region for TTM.
 * @mem: The region to initialize.
 *
 * This function initializes a suitable TTM resource manager for the
 * region, and if it's a LMEM region type, attaches it to the TTM
 * device. MOCK regions are NOT attached to the TTM device, since we don't
 * have one for the mock selftests.
 *
 * Return: 0 on success, negative error code on failure.
 */
=======
static struct ttm_resource *
intel_region_ttm_node_reserve(struct intel_memory_region *mem,
			      resource_size_t offset,
			      resource_size_t size)
{
	struct ttm_resource_manager *man = mem->region_private;
	struct ttm_place place = {};
	struct ttm_buffer_object mock_bo = {};
	struct ttm_resource *res;
	int ret;

	/*
	 * Having to use a mock_bo is unfortunate but stems from some
	 * drivers having private managers that insist to know what the
	 * allocate memory is intended for, using it to send private
	 * data to the manager. Also recently the bo has been used to send
	 * alignment info to the manager. Assume that apart from the latter,
	 * none of the managers we use will ever access the buffer object
	 * members, hoping we can pass the alignment info in the
	 * struct ttm_place in the future.
	 */

	place.fpfn = offset >> PAGE_SHIFT;
	place.lpfn = place.fpfn + (size >> PAGE_SHIFT);
	mock_bo.base.size = size;
	ret = man->func->alloc(man, &mock_bo, &place, &res);
	if (ret == -ENOSPC)
		ret = -ENXIO;

	return ret ? ERR_PTR(ret) : res;
}

=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/**
 * intel_region_ttm_init - Initialize a memory region for TTM.
 * @mem: The region to initialize.
 *
 * This function initializes a suitable TTM resource manager for the
 * region, and if it's a LMEM region type, attaches it to the TTM
 * device. MOCK regions are NOT attached to the TTM device, since we don't
 * have one for the mock selftests.
 *
 * Return: 0 on success, negative error code on failure.
 */
<<<<<<< HEAD
void intel_region_ttm_node_free(struct intel_memory_region *mem,
				struct ttm_resource *res)
{
	struct ttm_resource_manager *man = mem->region_private;

	man->func->free(man, res);
}

static const struct intel_memory_region_private_ops priv_ops = {
	.reserve = intel_region_ttm_node_reserve,
	.free = intel_region_ttm_node_free,
};

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int intel_region_ttm_init(struct intel_memory_region *mem)
{
	struct ttm_device *bdev = &mem->i915->bdev;
	int mem_type = intel_region_to_ttm_type(mem);
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = i915_ttm_buddy_man_init(bdev, mem_type, false,
				      resource_size(&mem->region),
				      mem->min_page_size, PAGE_SIZE);
	if (ret)
		return ret;

=======
	ret = ttm_range_man_init(bdev, mem_type, false,
				 resource_size(&mem->region) >> PAGE_SHIFT);
	if (ret)
		return ret;

	mem->chunk_size = PAGE_SIZE;
	mem->max_order =
		get_order(rounddown_pow_of_two(resource_size(&mem->region)));
	mem->is_range_manager = true;
	mem->priv_ops = &priv_ops;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	ret = i915_ttm_buddy_man_init(bdev, mem_type, false,
				      resource_size(&mem->region),
				      mem->min_page_size, PAGE_SIZE);
	if (ret)
		return ret;

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	mem->region_private = ttm_manager_type(bdev, mem_type);

	return 0;
}

/**
 * intel_region_ttm_fini - Finalize a TTM region.
 * @mem: The memory region
 *
 * This functions takes down the TTM resource manager associated with the
 * memory region, and if it was registered with the TTM device,
 * removes that registration.
 */
void intel_region_ttm_fini(struct intel_memory_region *mem)
{
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = i915_ttm_buddy_man_fini(&mem->i915->bdev,
				      intel_region_to_ttm_type(mem));
=======
	ret = ttm_range_man_fini(&mem->i915->bdev,
				 intel_region_to_ttm_type(mem));
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	ret = i915_ttm_buddy_man_fini(&mem->i915->bdev,
				      intel_region_to_ttm_type(mem));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	GEM_WARN_ON(ret);
	mem->region_private = NULL;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * intel_region_ttm_resource_to_st - Convert an opaque TTM resource manager resource
 * to an sg_table.
 * @mem: The memory region.
 * @res: The resource manager resource obtained from the TTM resource manager.
=======
 * intel_region_ttm_node_to_st - Convert an opaque TTM resource manager node
 * to an sg_table.
 * @mem: The memory region.
 * @node: The resource manager node obtained from the TTM resource manager.
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * intel_region_ttm_resource_to_st - Convert an opaque TTM resource manager resource
 * to an sg_table.
 * @mem: The memory region.
 * @res: The resource manager resource obtained from the TTM resource manager.
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 *
 * The gem backends typically use sg-tables for operations on the underlying
 * io_memory. So provide a way for the backends to translate the
 * nodes they are handed from TTM to sg-tables.
 *
 * Return: A malloced sg_table on success, an error pointer on failure.
 */
<<<<<<< HEAD
<<<<<<< HEAD
struct sg_table *intel_region_ttm_resource_to_st(struct intel_memory_region *mem,
						 struct ttm_resource *res)
{
	if (mem->is_range_manager) {
		struct ttm_range_mgr_node *range_node =
			to_ttm_range_mgr_node(res);

		return i915_sg_from_mm_node(&range_node->mm_nodes[0],
					    mem->region.start);
	} else {
		return i915_sg_from_buddy_resource(res, mem->region.start);
	}
}

#ifdef CONFIG_DRM_I915_SELFTEST
/**
 * intel_region_ttm_resource_alloc - Allocate memory resources from a region
=======
struct sg_table *intel_region_ttm_node_to_st(struct intel_memory_region *mem,
					     struct ttm_resource *res)
=======
struct sg_table *intel_region_ttm_resource_to_st(struct intel_memory_region *mem,
						 struct ttm_resource *res)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	if (mem->is_range_manager) {
		struct ttm_range_mgr_node *range_node =
			to_ttm_range_mgr_node(res);

		return i915_sg_from_mm_node(&range_node->mm_nodes[0],
					    mem->region.start);
	} else {
		return i915_sg_from_buddy_resource(res, mem->region.start);
	}
}

#ifdef CONFIG_DRM_I915_SELFTEST
/**
<<<<<<< HEAD
 * intel_region_ttm_node_alloc - Allocate memory resources from a region
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * intel_region_ttm_resource_alloc - Allocate memory resources from a region
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 * @mem: The memory region,
 * @size: The requested size in bytes
 * @flags: Allocation flags
 *
 * This functionality is provided only for callers that need to allocate
 * memory from standalone TTM range managers, without the TTM eviction
 * functionality. Don't use if you are not completely sure that's the
 * case. The returned opaque node can be converted to an sg_table using
<<<<<<< HEAD
<<<<<<< HEAD
 * intel_region_ttm_resource_to_st(), and can be freed using
 * intel_region_ttm_resource_free().
=======
 * intel_region_ttm_node_to_st(), and can be freed using
 * intel_region_ttm_node_free().
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * intel_region_ttm_resource_to_st(), and can be freed using
 * intel_region_ttm_resource_free().
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 *
 * Return: A valid pointer on success, an error pointer on failure.
 */
struct ttm_resource *
<<<<<<< HEAD
<<<<<<< HEAD
intel_region_ttm_resource_alloc(struct intel_memory_region *mem,
				resource_size_t size,
				unsigned int flags)
=======
intel_region_ttm_node_alloc(struct intel_memory_region *mem,
			    resource_size_t size,
			    unsigned int flags)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
intel_region_ttm_resource_alloc(struct intel_memory_region *mem,
				resource_size_t size,
				unsigned int flags)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct ttm_resource_manager *man = mem->region_private;
	struct ttm_place place = {};
	struct ttm_buffer_object mock_bo = {};
	struct ttm_resource *res;
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	mock_bo.base.size = size;
	place.flags = flags;
=======
	/*
	 * We ignore the flags for now since we're using the range
	 * manager and contigous and min page size would be fulfilled
	 * by default if size is min page size aligned.
	 */
	mock_bo.base.size = size;

	if (mem->is_range_manager) {
		if (size >= SZ_1G)
			mock_bo.page_alignment = SZ_1G >> PAGE_SHIFT;
		else if (size >= SZ_2M)
			mock_bo.page_alignment = SZ_2M >> PAGE_SHIFT;
		else if (size >= SZ_64K)
			mock_bo.page_alignment = SZ_64K >> PAGE_SHIFT;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	mock_bo.base.size = size;
	place.flags = flags;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	ret = man->func->alloc(man, &mock_bo, &place, &res);
	if (ret == -ENOSPC)
		ret = -ENXIO;
	return ret ? ERR_PTR(ret) : res;
}
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif

/**
 * intel_region_ttm_resource_free - Free a resource allocated from a resource manager
 * @mem: The region the resource was allocated from.
 * @res: The opaque resource representing an allocation.
 */
void intel_region_ttm_resource_free(struct intel_memory_region *mem,
				    struct ttm_resource *res)
{
	struct ttm_resource_manager *man = mem->region_private;

	man->func->free(man, res);
}
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
