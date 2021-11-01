// SPDX-License-Identifier: MIT
/*
 * Copyright © 2019 Intel Corporation
 */

#include "intel_memory_region.h"
<<<<<<< HEAD
=======
#include "intel_region_ttm.h"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#include "gem/i915_gem_region.h"
#include "gem/i915_gem_lmem.h"
#include "i915_drv.h"

<<<<<<< HEAD
=======
static void lmem_put_pages(struct drm_i915_gem_object *obj,
			   struct sg_table *pages)
{
	intel_region_ttm_node_free(obj->mm.region, obj->mm.st_mm_node);
	obj->mm.dirty = false;
	sg_free_table(pages);
	kfree(pages);
}

static int lmem_get_pages(struct drm_i915_gem_object *obj)
{
	unsigned int flags;
	struct sg_table *pages;

	flags = I915_ALLOC_MIN_PAGE_SIZE;
	if (obj->flags & I915_BO_ALLOC_CONTIGUOUS)
		flags |= I915_ALLOC_CONTIGUOUS;

	obj->mm.st_mm_node = intel_region_ttm_node_alloc(obj->mm.region,
							 obj->base.size,
							 flags);
	if (IS_ERR(obj->mm.st_mm_node))
		return PTR_ERR(obj->mm.st_mm_node);

	/* Range manager is always contigous */
	if (obj->mm.region->is_range_manager)
		obj->flags |= I915_BO_ALLOC_CONTIGUOUS;
	pages = intel_region_ttm_node_to_st(obj->mm.region, obj->mm.st_mm_node);
	if (IS_ERR(pages)) {
		intel_region_ttm_node_free(obj->mm.region, obj->mm.st_mm_node);
		return PTR_ERR(pages);
	}

	__i915_gem_object_set_pages(obj, pages, i915_sg_dma_sizes(pages->sgl));

	if (obj->flags & I915_BO_ALLOC_CPU_CLEAR) {
		void __iomem *vaddr =
			i915_gem_object_lmem_io_map(obj, 0, obj->base.size);

		if (!vaddr) {
			struct sg_table *pages =
				__i915_gem_object_unset_pages(obj);

			if (!IS_ERR_OR_NULL(pages))
				lmem_put_pages(obj, pages);
		}

		memset_io(vaddr, 0, obj->base.size);
		io_mapping_unmap(vaddr);
	}

	return 0;
}

const struct drm_i915_gem_object_ops i915_gem_lmem_obj_ops = {
	.name = "i915_gem_object_lmem",
	.flags = I915_GEM_OBJECT_HAS_IOMEM,

	.get_pages = lmem_get_pages,
	.put_pages = lmem_put_pages,
	.release = i915_gem_object_release_memory_region,
};

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
void __iomem *
i915_gem_object_lmem_io_map(struct drm_i915_gem_object *obj,
			    unsigned long n,
			    unsigned long size)
{
	resource_size_t offset;

	GEM_BUG_ON(!i915_gem_object_is_contiguous(obj));

	offset = i915_gem_object_get_dma_address(obj, n);
	offset -= obj->mm.region->region.start;

	return io_mapping_map_wc(&obj->mm.region->iomap, offset, size);
}

<<<<<<< HEAD
/**
 * i915_gem_object_is_lmem - Whether the object is resident in
 * lmem
 * @obj: The object to check.
 *
 * Even if an object is allowed to migrate and change memory region,
 * this function checks whether it will always be present in lmem when
 * valid *or* if that's not the case, whether it's currently resident in lmem.
 * For migratable and evictable objects, the latter only makes sense when
 * the object is locked.
 *
 * Return: Whether the object migratable but resident in lmem, or not
 * migratable and will be present in lmem when valid.
 */
bool i915_gem_object_is_lmem(struct drm_i915_gem_object *obj)
{
	struct intel_memory_region *mr = READ_ONCE(obj->mm.region);

#ifdef CONFIG_LOCKDEP
	if (i915_gem_object_migratable(obj) &&
	    i915_gem_object_evictable(obj))
		assert_object_held(obj);
#endif
=======
bool i915_gem_object_is_lmem(struct drm_i915_gem_object *obj)
{
	struct intel_memory_region *mr = obj->mm.region;

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	return mr && (mr->type == INTEL_MEMORY_LOCAL ||
		      mr->type == INTEL_MEMORY_STOLEN_LOCAL);
}

<<<<<<< HEAD
/**
 * __i915_gem_object_is_lmem - Whether the object is resident in
 * lmem while in the fence signaling critical path.
 * @obj: The object to check.
 *
 * This function is intended to be called from within the fence signaling
 * path where the fence keeps the object from being migrated. For example
 * during gpu reset or similar.
 *
 * Return: Whether the object is resident in lmem.
 */
bool __i915_gem_object_is_lmem(struct drm_i915_gem_object *obj)
{
	struct intel_memory_region *mr = READ_ONCE(obj->mm.region);

#ifdef CONFIG_LOCKDEP
	GEM_WARN_ON(dma_resv_test_signaled(obj->base.resv, true));
#endif
	return mr && (mr->type == INTEL_MEMORY_LOCAL ||
		      mr->type == INTEL_MEMORY_STOLEN_LOCAL);
}

/**
 * __i915_gem_object_create_lmem_with_ps - Create lmem object and force the
 * minimum page size for the backing pages.
 * @i915: The i915 instance.
 * @size: The size in bytes for the object. Note that we need to round the size
 * up depending on the @page_size. The final object size can be fished out from
 * the drm GEM object.
 * @page_size: The requested minimum page size in bytes for this object. This is
 * useful if we need something bigger than the regions min_page_size due to some
 * hw restriction, or in some very specialised cases where it needs to be
 * smaller, where the internal fragmentation cost is too great when rounding up
 * the object size.
 * @flags: The optional BO allocation flags.
 *
 * Note that this interface assumes you know what you are doing when forcing the
 * @page_size. If this is smaller than the regions min_page_size then it can
 * never be inserted into any GTT, otherwise it might lead to undefined
 * behaviour.
 *
 * Return: The object pointer, which might be an ERR_PTR in the case of failure.
 */
struct drm_i915_gem_object *
__i915_gem_object_create_lmem_with_ps(struct drm_i915_private *i915,
				      resource_size_t size,
				      resource_size_t page_size,
				      unsigned int flags)
{
	return i915_gem_object_create_region(i915->mm.regions[INTEL_REGION_LMEM],
					     size, page_size, flags);
}

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
struct drm_i915_gem_object *
i915_gem_object_create_lmem(struct drm_i915_private *i915,
			    resource_size_t size,
			    unsigned int flags)
{
	return i915_gem_object_create_region(i915->mm.regions[INTEL_REGION_LMEM],
<<<<<<< HEAD
					     size, 0, flags);
=======
					     size, flags);
}

int __i915_gem_lmem_object_init(struct intel_memory_region *mem,
				struct drm_i915_gem_object *obj,
				resource_size_t size,
				unsigned int flags)
{
	static struct lock_class_key lock_class;
	struct drm_i915_private *i915 = mem->i915;

	drm_gem_private_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &i915_gem_lmem_obj_ops, &lock_class, flags);

	obj->read_domains = I915_GEM_DOMAIN_WC | I915_GEM_DOMAIN_GTT;

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_NONE);

	i915_gem_object_init_memory_region(obj, mem);

	return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
