// SPDX-License-Identifier: GPL-2.0-only
/*
 * linux/fs/lockd/svcsubs.c
 *
 * Various support routines for the NLM server.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#include <linux/types.h>
#include <linux/string.h>
#include <linux/time.h>
#include <linux/in.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/sunrpc/svc.h>
#include <linux/sunrpc/addr.h>
#include <linux/lockd/lockd.h>
#include <linux/lockd/share.h>
#include <linux/module.h>
#include <linux/mount.h>
#include <uapi/linux/nfs2.h>

#define NLMDBG_FACILITY		NLMDBG_SVCSUBS


/*
 * Global file hash table
 */
#define FILE_HASH_BITS		7
#define FILE_NRHASH		(1<<FILE_HASH_BITS)
static struct hlist_head	nlm_files[FILE_NRHASH];
static DEFINE_MUTEX(nlm_file_mutex);

#ifdef CONFIG_SUNRPC_DEBUG
static inline void nlm_debug_print_fh(char *msg, struct nfs_fh *f)
{
	u32 *fhp = (u32*)f->data;

	/* print the first 32 bytes of the fh */
	dprintk("lockd: %s (%08x %08x %08x %08x %08x %08x %08x %08x)\n",
		msg, fhp[0], fhp[1], fhp[2], fhp[3],
		fhp[4], fhp[5], fhp[6], fhp[7]);
}

static inline void nlm_debug_print_file(char *msg, struct nlm_file *file)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct inode *inode = nlmsvc_file_inode(file);
=======
	struct inode *inode = locks_inode(file->f_file);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct inode *inode = nlmsvc_file_inode(file);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	dprintk("lockd: %s %s/%ld\n",
		msg, inode->i_sb->s_id, inode->i_ino);
}
#else
static inline void nlm_debug_print_fh(char *msg, struct nfs_fh *f)
{
	return;
}

static inline void nlm_debug_print_file(char *msg, struct nlm_file *file)
{
	return;
}
#endif

static inline unsigned int file_hash(struct nfs_fh *f)
{
	unsigned int tmp=0;
	int i;
	for (i=0; i<NFS2_FHSIZE;i++)
		tmp += f->data[i];
	return tmp & (FILE_NRHASH - 1);
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int lock_to_openmode(struct file_lock *lock)
{
	return (lock->fl_type == F_WRLCK) ? O_WRONLY : O_RDONLY;
}

/*
 * Open the file. Note that if we're reexporting, for example,
 * this could block the lockd thread for a while.
 *
 * We have to make sure we have the right credential to open
 * the file.
 */
static __be32 nlm_do_fopen(struct svc_rqst *rqstp,
			   struct nlm_file *file, int mode)
{
	struct file **fp = &file->f_file[mode];
	__be32	nfserr;

	if (*fp)
		return 0;
	nfserr = nlmsvc_ops->fopen(rqstp, &file->f_handle, fp, mode);
	if (nfserr)
		dprintk("lockd: open failed (error %d)\n", nfserr);
	return nfserr;
}

<<<<<<< HEAD
/*
 * Lookup file info. If it doesn't exist, create a file info struct
 * and open a (VFS) file for the given inode.
 */
__be32
nlm_lookup_file(struct svc_rqst *rqstp, struct nlm_file **result,
					struct nlm_lock *lock)
=======
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Lookup file info. If it doesn't exist, create a file info struct
 * and open a (VFS) file for the given inode.
 */
__be32
nlm_lookup_file(struct svc_rqst *rqstp, struct nlm_file **result,
<<<<<<< HEAD
					struct nfs_fh *f)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
					struct nlm_lock *lock)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct nlm_file	*file;
	unsigned int	hash;
	__be32		nfserr;
<<<<<<< HEAD
<<<<<<< HEAD
	int		mode;

	nlm_debug_print_fh("nlm_lookup_file", &lock->fh);

	hash = file_hash(&lock->fh);
	mode = lock_to_openmode(&lock->fl);
=======
=======
	int		mode;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	nlm_debug_print_fh("nlm_lookup_file", &lock->fh);

<<<<<<< HEAD
	hash = file_hash(f);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	hash = file_hash(&lock->fh);
	mode = lock_to_openmode(&lock->fl);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	/* Lock file table */
	mutex_lock(&nlm_file_mutex);

	hlist_for_each_entry(file, &nlm_files[hash], f_list)
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (!nfs_compare_fh(&file->f_handle, &lock->fh)) {
			mutex_lock(&file->f_mutex);
			nfserr = nlm_do_fopen(rqstp, file, mode);
			mutex_unlock(&file->f_mutex);
<<<<<<< HEAD
			goto found;
		}
	nlm_debug_print_fh("creating file for", &lock->fh);
=======
		if (!nfs_compare_fh(&file->f_handle, f))
			goto found;

	nlm_debug_print_fh("creating file for", f);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
			goto found;
		}
	nlm_debug_print_fh("creating file for", &lock->fh);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	nfserr = nlm_lck_denied_nolocks;
	file = kzalloc(sizeof(*file), GFP_KERNEL);
	if (!file)
<<<<<<< HEAD
<<<<<<< HEAD
		goto out_free;

	memcpy(&file->f_handle, &lock->fh, sizeof(struct nfs_fh));
=======
		goto out_unlock;

	memcpy(&file->f_handle, f, sizeof(struct nfs_fh));
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		goto out_free;

	memcpy(&file->f_handle, &lock->fh, sizeof(struct nfs_fh));
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	mutex_init(&file->f_mutex);
	INIT_HLIST_NODE(&file->f_list);
	INIT_LIST_HEAD(&file->f_blocks);

<<<<<<< HEAD
<<<<<<< HEAD
	nfserr = nlm_do_fopen(rqstp, file, mode);
	if (nfserr)
		goto out_unlock;
=======
	/* Open the file. Note that this must not sleep for too long, else
	 * we would lock up lockd:-) So no NFS re-exports, folks.
	 *
	 * We have to make sure we have the right credential to open
	 * the file.
	 */
	if ((nfserr = nlmsvc_ops->fopen(rqstp, f, &file->f_file)) != 0) {
		dprintk("lockd: open failed (error %d)\n", nfserr);
		goto out_free;
	}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	nfserr = nlm_do_fopen(rqstp, file, mode);
	if (nfserr)
		goto out_unlock;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	hlist_add_head(&file->f_list, &nlm_files[hash]);

found:
	dprintk("lockd: found file %p (count %d)\n", file, file->f_count);
	*result = file;
	file->f_count++;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	nfserr = 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

out_unlock:
	mutex_unlock(&nlm_file_mutex);
	return nfserr;

out_free:
	kfree(file);
	goto out_unlock;
}

/*
 * Delete a file after having released all locks, blocks and shares
 */
static inline void
nlm_delete_file(struct nlm_file *file)
{
	nlm_debug_print_file("closing file", file);
	if (!hlist_unhashed(&file->f_list)) {
		hlist_del(&file->f_list);
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (file->f_file[O_RDONLY])
			nlmsvc_ops->fclose(file->f_file[O_RDONLY]);
		if (file->f_file[O_WRONLY])
			nlmsvc_ops->fclose(file->f_file[O_WRONLY]);
<<<<<<< HEAD
=======
		nlmsvc_ops->fclose(file->f_file);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		kfree(file);
	} else {
		printk(KERN_WARNING "lockd: attempt to release unknown file!\n");
	}
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int nlm_unlock_files(struct nlm_file *file)
{
	struct file_lock lock;
	struct file *f;

	lock.fl_type  = F_UNLCK;
	lock.fl_start = 0;
	lock.fl_end   = OFFSET_MAX;
	for (f = file->f_file[0]; f <= file->f_file[1]; f++) {
		if (f && vfs_lock_file(f, F_SETLK, &lock, NULL) < 0) {
			pr_warn("lockd: unlock failure in %s:%d\n",
				__FILE__, __LINE__);
			return 1;
		}
	}
	return 0;
}

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Loop over all locks on the given file and perform the specified
 * action.
 */
static int
nlm_traverse_locks(struct nlm_host *host, struct nlm_file *file,
			nlm_host_match_fn_t match)
{
	struct inode	 *inode = nlmsvc_file_inode(file);
	struct file_lock *fl;
	struct file_lock_context *flctx = inode->i_flctx;
	struct nlm_host	 *lockhost;

	if (!flctx || list_empty_careful(&flctx->flc_posix))
		return 0;
again:
	file->f_locks = 0;
	spin_lock(&flctx->flc_lock);
	list_for_each_entry(fl, &flctx->flc_posix, fl_list) {
		if (fl->fl_lmops != &nlmsvc_lock_operations)
			continue;

		/* update current lock count */
		file->f_locks++;

		lockhost = ((struct nlm_lockowner *)fl->fl_owner)->host;
		if (match(lockhost, host)) {
<<<<<<< HEAD
<<<<<<< HEAD

			spin_unlock(&flctx->flc_lock);
			if (nlm_unlock_files(file))
				return 1;
=======
			struct file_lock lock = *fl;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

			spin_unlock(&flctx->flc_lock);
			if (nlm_unlock_files(file))
				return 1;
<<<<<<< HEAD
			}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			goto again;
		}
	}
	spin_unlock(&flctx->flc_lock);

	return 0;
}

static int
nlmsvc_always_match(void *dummy1, struct nlm_host *dummy2)
{
	return 1;
}

/*
 * Inspect a single file
 */
static inline int
nlm_inspect_file(struct nlm_host *host, struct nlm_file *file, nlm_host_match_fn_t match)
{
	nlmsvc_traverse_blocks(host, file, match);
	nlmsvc_traverse_shares(host, file, match);
	return nlm_traverse_locks(host, file, match);
}

/*
 * Quick check whether there are still any locks, blocks or
 * shares on a given file.
 */
static inline int
nlm_file_inuse(struct nlm_file *file)
{
	struct inode	 *inode = nlmsvc_file_inode(file);
	struct file_lock *fl;
	struct file_lock_context *flctx = inode->i_flctx;

	if (file->f_count || !list_empty(&file->f_blocks) || file->f_shares)
		return 1;

	if (flctx && !list_empty_careful(&flctx->flc_posix)) {
		spin_lock(&flctx->flc_lock);
		list_for_each_entry(fl, &flctx->flc_posix, fl_list) {
			if (fl->fl_lmops == &nlmsvc_lock_operations) {
				spin_unlock(&flctx->flc_lock);
				return 1;
			}
		}
		spin_unlock(&flctx->flc_lock);
	}
	file->f_locks = 0;
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static void nlm_close_files(struct nlm_file *file)
{
	struct file *f;

	for (f = file->f_file[0]; f <= file->f_file[1]; f++)
		if (f)
			nlmsvc_ops->fclose(f);
}

<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/*
 * Loop over all files in the file table.
 */
static int
nlm_traverse_files(void *data, nlm_host_match_fn_t match,
		int (*is_failover_file)(void *data, struct nlm_file *file))
{
	struct hlist_node *next;
	struct nlm_file	*file;
	int i, ret = 0;

	mutex_lock(&nlm_file_mutex);
	for (i = 0; i < FILE_NRHASH; i++) {
		hlist_for_each_entry_safe(file, next, &nlm_files[i], f_list) {
			if (is_failover_file && !is_failover_file(data, file))
				continue;
			file->f_count++;
			mutex_unlock(&nlm_file_mutex);

			/* Traverse locks, blocks and shares of this file
			 * and update file->f_locks count */
			if (nlm_inspect_file(data, file, match))
				ret = 1;

			mutex_lock(&nlm_file_mutex);
			file->f_count--;
			/* No more references to this file. Let go of it. */
			if (list_empty(&file->f_blocks) && !file->f_locks
			 && !file->f_shares && !file->f_count) {
				hlist_del(&file->f_list);
<<<<<<< HEAD
<<<<<<< HEAD
				nlm_close_files(file);
=======
				nlmsvc_ops->fclose(file->f_file);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
				nlm_close_files(file);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
				kfree(file);
			}
		}
	}
	mutex_unlock(&nlm_file_mutex);
	return ret;
}

/*
 * Release file. If there are no more remote locks on this file,
 * close it and free the handle.
 *
 * Note that we can't do proper reference counting without major
 * contortions because the code in fs/locks.c creates, deletes and
 * splits locks without notification. Our only way is to walk the
 * entire lock list each time we remove a lock.
 */
void
nlm_release_file(struct nlm_file *file)
{
	dprintk("lockd: nlm_release_file(%p, ct = %d)\n",
				file, file->f_count);

	/* Lock file table */
	mutex_lock(&nlm_file_mutex);

	/* If there are no more locks etc, delete the file */
	if (--file->f_count == 0 && !nlm_file_inuse(file))
		nlm_delete_file(file);

	mutex_unlock(&nlm_file_mutex);
}

/*
 * Helpers function for resource traversal
 *
 * nlmsvc_mark_host:
 *	used by the garbage collector; simply sets h_inuse only for those
 *	hosts, which passed network check.
 *	Always returns 0.
 *
 * nlmsvc_same_host:
 *	returns 1 iff the two hosts match. Used to release
 *	all resources bound to a specific host.
 *
 * nlmsvc_is_client:
 *	returns 1 iff the host is a client.
 *	Used by nlmsvc_invalidate_all
 */

static int
nlmsvc_mark_host(void *data, struct nlm_host *hint)
{
	struct nlm_host *host = data;

	if ((hint->net == NULL) ||
	    (host->net == hint->net))
		host->h_inuse = 1;
	return 0;
}

static int
nlmsvc_same_host(void *data, struct nlm_host *other)
{
	struct nlm_host *host = data;

	return host == other;
}

static int
nlmsvc_is_client(void *data, struct nlm_host *dummy)
{
	struct nlm_host *host = data;

	if (host->h_server) {
		/* we are destroying locks even though the client
		 * hasn't asked us too, so don't unmonitor the
		 * client
		 */
		if (host->h_nsmhandle)
			host->h_nsmhandle->sm_sticky = 1;
		return 1;
	} else
		return 0;
}

/*
 * Mark all hosts that still hold resources
 */
void
nlmsvc_mark_resources(struct net *net)
{
	struct nlm_host hint;

	dprintk("lockd: %s for net %x\n", __func__, net ? net->ns.inum : 0);
	hint.net = net;
	nlm_traverse_files(&hint, nlmsvc_mark_host, NULL);
}

/*
 * Release all resources held by the given client
 */
void
nlmsvc_free_host_resources(struct nlm_host *host)
{
	dprintk("lockd: nlmsvc_free_host_resources\n");

	if (nlm_traverse_files(host, nlmsvc_same_host, NULL)) {
		printk(KERN_WARNING
			"lockd: couldn't remove all locks held by %s\n",
			host->h_name);
		BUG();
	}
}

/**
 * nlmsvc_invalidate_all - remove all locks held for clients
 *
 * Release all locks held by NFS clients.
 *
 */
void
nlmsvc_invalidate_all(void)
{
	/*
	 * Previously, the code would call
	 * nlmsvc_free_host_resources for each client in
	 * turn, which is about as inefficient as it gets.
	 * Now we just do it once in nlm_traverse_files.
	 */
	nlm_traverse_files(NULL, nlmsvc_is_client, NULL);
}

<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static int
nlmsvc_match_sb(void *datap, struct nlm_file *file)
{
	struct super_block *sb = datap;

<<<<<<< HEAD
<<<<<<< HEAD
	return sb == nlmsvc_file_inode(file)->i_sb;
=======
	return sb == locks_inode(file->f_file)->i_sb;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	return sb == nlmsvc_file_inode(file)->i_sb;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

/**
 * nlmsvc_unlock_all_by_sb - release locks held on this file system
 * @sb: super block
 *
 * Release all locks held by clients accessing this file system.
 */
int
nlmsvc_unlock_all_by_sb(struct super_block *sb)
{
	int ret;

	ret = nlm_traverse_files(sb, nlmsvc_always_match, nlmsvc_match_sb);
	return ret ? -EIO : 0;
}
EXPORT_SYMBOL_GPL(nlmsvc_unlock_all_by_sb);

static int
nlmsvc_match_ip(void *datap, struct nlm_host *host)
{
	return rpc_cmp_addr(nlm_srcaddr(host), datap);
}

/**
 * nlmsvc_unlock_all_by_ip - release local locks by IP address
 * @server_addr: server's IP address as seen by clients
 *
 * Release all locks held by clients accessing this host
 * via the passed in IP address.
 */
int
nlmsvc_unlock_all_by_ip(struct sockaddr *server_addr)
{
	int ret;

	ret = nlm_traverse_files(server_addr, nlmsvc_match_ip, NULL);
	return ret ? -EIO : 0;
}
EXPORT_SYMBOL_GPL(nlmsvc_unlock_all_by_ip);
