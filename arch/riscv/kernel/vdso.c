// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2004 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 * Copyright (C) 2012 ARM Limited
 * Copyright (C) 2015 Regents of the University of California
 */

#include <linux/elf.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/binfmts.h>
#include <linux/err.h>
#include <asm/page.h>
<<<<<<< HEAD
#include <asm/vdso.h>

#ifdef CONFIG_GENERIC_TIME_VSYSCALL
#include <vdso/datapage.h>
#else
struct vdso_data {
};
=======
#ifdef CONFIG_GENERIC_TIME_VSYSCALL
#include <vdso/datapage.h>
#else
#include <asm/vdso.h>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
#endif

extern char vdso_start[], vdso_end[];

<<<<<<< HEAD
enum vvar_pages {
	VVAR_DATA_PAGE_OFFSET,
	VVAR_NR_PAGES,
};

#define VVAR_SIZE  (VVAR_NR_PAGES << PAGE_SHIFT)

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
static unsigned int vdso_pages __ro_after_init;
static struct page **vdso_pagelist __ro_after_init;

/*
 * The vDSO data page.
 */
static union {
	struct vdso_data	data;
	u8			page[PAGE_SIZE];
} vdso_data_store __page_aligned_data;
struct vdso_data *vdso_data = &vdso_data_store.data;

static int __init vdso_init(void)
{
	unsigned int i;

	vdso_pages = (vdso_end - vdso_start) >> PAGE_SHIFT;
	vdso_pagelist =
<<<<<<< HEAD
		kcalloc(vdso_pages + VVAR_NR_PAGES, sizeof(struct page *), GFP_KERNEL);
=======
		kcalloc(vdso_pages + 1, sizeof(struct page *), GFP_KERNEL);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	if (unlikely(vdso_pagelist == NULL)) {
		pr_err("vdso: pagelist allocation failed\n");
		return -ENOMEM;
	}

	for (i = 0; i < vdso_pages; i++) {
		struct page *pg;

		pg = virt_to_page(vdso_start + (i << PAGE_SHIFT));
		vdso_pagelist[i] = pg;
	}
	vdso_pagelist[i] = virt_to_page(vdso_data);

	return 0;
}
arch_initcall(vdso_init);

int arch_setup_additional_pages(struct linux_binprm *bprm,
	int uses_interp)
{
	struct mm_struct *mm = current->mm;
	unsigned long vdso_base, vdso_len;
	int ret;

<<<<<<< HEAD
	BUILD_BUG_ON(VVAR_NR_PAGES != __VVAR_PAGES);

	vdso_len = (vdso_pages + VVAR_NR_PAGES) << PAGE_SHIFT;

	if (mmap_write_lock_killable(mm))
		return -EINTR;

=======
	vdso_len = (vdso_pages + 1) << PAGE_SHIFT;

	mmap_write_lock(mm);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	vdso_base = get_unmapped_area(NULL, 0, vdso_len, 0, 0);
	if (IS_ERR_VALUE(vdso_base)) {
		ret = vdso_base;
		goto end;
	}

<<<<<<< HEAD
	mm->context.vdso = NULL;
	ret = install_special_mapping(mm, vdso_base, VVAR_SIZE,
		(VM_READ | VM_MAYREAD), &vdso_pagelist[vdso_pages]);
	if (unlikely(ret))
		goto end;

	ret =
	   install_special_mapping(mm, vdso_base + VVAR_SIZE,
		vdso_pages << PAGE_SHIFT,
		(VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC),
		vdso_pagelist);

	if (unlikely(ret))
		goto end;

	/*
	 * Put vDSO base into mm struct. We need to do this before calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO (since arch_vma_name fails).
	 */
	mm->context.vdso = (void *)vdso_base + VVAR_SIZE;

=======
	/*
	 * Put vDSO base into mm struct. We need to do this before calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO (since arch_vma_name fails).
	 */
	mm->context.vdso = (void *)vdso_base;

	ret =
	   install_special_mapping(mm, vdso_base, vdso_pages << PAGE_SHIFT,
		(VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC),
		vdso_pagelist);

	if (unlikely(ret)) {
		mm->context.vdso = NULL;
		goto end;
	}

	vdso_base += (vdso_pages << PAGE_SHIFT);
	ret = install_special_mapping(mm, vdso_base, PAGE_SIZE,
		(VM_READ | VM_MAYREAD), &vdso_pagelist[vdso_pages]);

	if (unlikely(ret))
		mm->context.vdso = NULL;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
end:
	mmap_write_unlock(mm);
	return ret;
}

const char *arch_vma_name(struct vm_area_struct *vma)
{
	if (vma->vm_mm && (vma->vm_start == (long)vma->vm_mm->context.vdso))
		return "[vdso]";
	if (vma->vm_mm && (vma->vm_start ==
<<<<<<< HEAD
			   (long)vma->vm_mm->context.vdso - VVAR_SIZE))
=======
			   (long)vma->vm_mm->context.vdso + PAGE_SIZE))
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		return "[vdso_data]";
	return NULL;
}
