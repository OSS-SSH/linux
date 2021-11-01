// SPDX-License-Identifier: MIT
/*
 * Copyright © 2020 Intel Corporation
 */

#include <drm/drm_print.h>

#include "gt/debugfs_gt.h"
#include "intel_guc.h"
#include "intel_guc_debugfs.h"
#include "intel_guc_log_debugfs.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include "gt/uc/intel_guc_ct.h"
#include "gt/uc/intel_guc_ads.h"
#include "gt/uc/intel_guc_submission.h"
#include "gt/uc/intel_guc_slpc.h"
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

static int guc_info_show(struct seq_file *m, void *data)
{
	struct intel_guc *guc = m->private;
	struct drm_printer p = drm_seq_file_printer(m);

	if (!intel_guc_is_supported(guc))
		return -ENODEV;

	intel_guc_load_status(guc, &p);
	drm_puts(&p, "\n");
	intel_guc_log_info(&guc->log, &p);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (!intel_guc_submission_is_used(guc))
		return 0;

	intel_guc_ct_print_info(&guc->ct, &p);
	intel_guc_submission_print_info(guc, &p);
	intel_guc_ads_print_policy_info(guc, &p);
<<<<<<< HEAD
=======
	/* Add more as required ... */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	return 0;
}
DEFINE_GT_DEBUGFS_ATTRIBUTE(guc_info);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int guc_registered_contexts_show(struct seq_file *m, void *data)
{
	struct intel_guc *guc = m->private;
	struct drm_printer p = drm_seq_file_printer(m);

	if (!intel_guc_submission_is_used(guc))
		return -ENODEV;

	intel_guc_submission_print_context_info(guc, &p);

	return 0;
}
DEFINE_GT_DEBUGFS_ATTRIBUTE(guc_registered_contexts);

static int guc_slpc_info_show(struct seq_file *m, void *unused)
{
	struct intel_guc *guc = m->private;
	struct intel_guc_slpc *slpc = &guc->slpc;
	struct drm_printer p = drm_seq_file_printer(m);

	if (!intel_guc_slpc_is_used(guc))
		return -ENODEV;

	return intel_guc_slpc_print_info(slpc, &p);
}
DEFINE_GT_DEBUGFS_ATTRIBUTE(guc_slpc_info);

static bool intel_eval_slpc_support(void *data)
{
	struct intel_guc *guc = (struct intel_guc *)data;

	return intel_guc_slpc_is_used(guc);
}

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void intel_guc_debugfs_register(struct intel_guc *guc, struct dentry *root)
{
	static const struct debugfs_gt_file files[] = {
		{ "guc_info", &guc_info_fops, NULL },
<<<<<<< HEAD
<<<<<<< HEAD
		{ "guc_registered_contexts", &guc_registered_contexts_fops, NULL },
		{ "guc_slpc_info", &guc_slpc_info_fops, &intel_eval_slpc_support},
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		{ "guc_registered_contexts", &guc_registered_contexts_fops, NULL },
		{ "guc_slpc_info", &guc_slpc_info_fops, &intel_eval_slpc_support},
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	};

	if (!intel_guc_is_supported(guc))
		return;

	intel_gt_debugfs_register_files(root, files, ARRAY_SIZE(files), guc);
	intel_guc_log_debugfs_register(&guc->log, root);
}
