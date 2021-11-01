// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2001-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#ifndef __XFS_ACL_H__
#define __XFS_ACL_H__

struct inode;
struct posix_acl;

#ifdef CONFIG_XFS_POSIX_ACL
<<<<<<< HEAD
<<<<<<< HEAD
extern struct posix_acl *xfs_get_acl(struct inode *inode, int type, bool rcu);
=======
extern struct posix_acl *xfs_get_acl(struct inode *inode, int type);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
extern struct posix_acl *xfs_get_acl(struct inode *inode, int type, bool rcu);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
extern int xfs_set_acl(struct user_namespace *mnt_userns, struct inode *inode,
		       struct posix_acl *acl, int type);
extern int __xfs_set_acl(struct inode *inode, struct posix_acl *acl, int type);
void xfs_forget_acl(struct inode *inode, const char *name);
#else
<<<<<<< HEAD
<<<<<<< HEAD
static inline struct posix_acl *xfs_get_acl(struct inode *inode, int type, bool rcu)
=======
static inline struct posix_acl *xfs_get_acl(struct inode *inode, int type)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static inline struct posix_acl *xfs_get_acl(struct inode *inode, int type, bool rcu)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	return NULL;
}
# define xfs_set_acl					NULL
static inline void xfs_forget_acl(struct inode *inode, const char *name)
{
}
#endif /* CONFIG_XFS_POSIX_ACL */

#endif	/* __XFS_ACL_H__ */
