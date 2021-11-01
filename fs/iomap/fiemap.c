// SPDX-License-Identifier: GPL-2.0
/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright (c) 2016-2021 Christoph Hellwig.
=======
 * Copyright (c) 2016-2018 Christoph Hellwig.
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
 * Copyright (c) 2016-2021 Christoph Hellwig.
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
 */
#include <linux/module.h>
#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/iomap.h>
#include <linux/fiemap.h>

<<<<<<< HEAD
<<<<<<< HEAD
static int iomap_to_fiemap(struct fiemap_extent_info *fi,
		const struct iomap *iomap, u32 flags)
=======
struct fiemap_ctx {
	struct fiemap_extent_info *fi;
	struct iomap prev;
};

static int iomap_to_fiemap(struct fiemap_extent_info *fi,
		struct iomap *iomap, u32 flags)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int iomap_to_fiemap(struct fiemap_extent_info *fi,
		const struct iomap *iomap, u32 flags)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	switch (iomap->type) {
	case IOMAP_HOLE:
		/* skip holes */
		return 0;
	case IOMAP_DELALLOC:
		flags |= FIEMAP_EXTENT_DELALLOC | FIEMAP_EXTENT_UNKNOWN;
		break;
	case IOMAP_MAPPED:
		break;
	case IOMAP_UNWRITTEN:
		flags |= FIEMAP_EXTENT_UNWRITTEN;
		break;
	case IOMAP_INLINE:
		flags |= FIEMAP_EXTENT_DATA_INLINE;
		break;
	}

	if (iomap->flags & IOMAP_F_MERGED)
		flags |= FIEMAP_EXTENT_MERGED;
	if (iomap->flags & IOMAP_F_SHARED)
		flags |= FIEMAP_EXTENT_SHARED;

	return fiemap_fill_next_extent(fi, iomap->offset,
			iomap->addr != IOMAP_NULL_ADDR ? iomap->addr : 0,
			iomap->length, flags);
}

<<<<<<< HEAD
<<<<<<< HEAD
static loff_t iomap_fiemap_iter(const struct iomap_iter *iter,
		struct fiemap_extent_info *fi, struct iomap *prev)
{
	int ret;

	if (iter->iomap.type == IOMAP_HOLE)
		return iomap_length(iter);

	ret = iomap_to_fiemap(fi, prev, 0);
	*prev = iter->iomap;
	switch (ret) {
	case 0:		/* success */
		return iomap_length(iter);
	case 1:		/* extent array full */
		return 0;
	default:	/* error */
=======
static loff_t
iomap_fiemap_actor(struct inode *inode, loff_t pos, loff_t length, void *data,
		struct iomap *iomap, struct iomap *srcmap)
=======
static loff_t iomap_fiemap_iter(const struct iomap_iter *iter,
		struct fiemap_extent_info *fi, struct iomap *prev)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int ret;

	if (iter->iomap.type == IOMAP_HOLE)
		return iomap_length(iter);

	ret = iomap_to_fiemap(fi, prev, 0);
	*prev = iter->iomap;
	switch (ret) {
	case 0:		/* success */
		return iomap_length(iter);
	case 1:		/* extent array full */
		return 0;
<<<<<<< HEAD
	default:
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	default:	/* error */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return ret;
	}
}

int iomap_fiemap(struct inode *inode, struct fiemap_extent_info *fi,
		u64 start, u64 len, const struct iomap_ops *ops)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct iomap_iter iter = {
		.inode		= inode,
		.pos		= start,
		.len		= len,
		.flags		= IOMAP_REPORT,
	};
	struct iomap prev = {
		.type		= IOMAP_HOLE,
	};
	int ret;
<<<<<<< HEAD

	ret = fiemap_prep(inode, fi, start, &iter.len, 0);
	if (ret)
		return ret;

	while ((ret = iomap_iter(&iter, ops)) > 0)
		iter.processed = iomap_fiemap_iter(&iter, fi, &prev);

	if (prev.type != IOMAP_HOLE) {
		ret = iomap_to_fiemap(fi, &prev, FIEMAP_EXTENT_LAST);
=======
	struct fiemap_ctx ctx;
	loff_t ret;

	memset(&ctx, 0, sizeof(ctx));
	ctx.fi = fi;
	ctx.prev.type = IOMAP_HOLE;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	ret = fiemap_prep(inode, fi, start, &iter.len, 0);
	if (ret)
		return ret;

	while ((ret = iomap_iter(&iter, ops)) > 0)
		iter.processed = iomap_fiemap_iter(&iter, fi, &prev);

<<<<<<< HEAD
	if (ctx.prev.type != IOMAP_HOLE) {
		ret = iomap_to_fiemap(fi, &ctx.prev, FIEMAP_EXTENT_LAST);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (prev.type != IOMAP_HOLE) {
		ret = iomap_to_fiemap(fi, &prev, FIEMAP_EXTENT_LAST);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		if (ret < 0)
			return ret;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	/* inode with no (attribute) mapping will give ENOENT */
	if (ret < 0 && ret != -ENOENT)
		return ret;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	/* inode with no (attribute) mapping will give ENOENT */
	if (ret < 0 && ret != -ENOENT)
		return ret;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	return 0;
}
EXPORT_SYMBOL_GPL(iomap_fiemap);

<<<<<<< HEAD
<<<<<<< HEAD
=======
static loff_t
iomap_bmap_actor(struct inode *inode, loff_t pos, loff_t length,
		void *data, struct iomap *iomap, struct iomap *srcmap)
{
	sector_t *bno = data, addr;

	if (iomap->type == IOMAP_MAPPED) {
		addr = (pos - iomap->offset + iomap->addr) >> inode->i_blkbits;
		*bno = addr;
	}
	return 0;
}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
/* legacy ->bmap interface.  0 is the error return (!) */
sector_t
iomap_bmap(struct address_space *mapping, sector_t bno,
		const struct iomap_ops *ops)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct iomap_iter iter = {
		.inode	= mapping->host,
		.pos	= (loff_t)bno << mapping->host->i_blkbits,
		.len	= i_blocksize(mapping->host),
		.flags	= IOMAP_REPORT,
	};
	const unsigned int blkshift = mapping->host->i_blkbits - SECTOR_SHIFT;
<<<<<<< HEAD
=======
	struct inode *inode = mapping->host;
	loff_t pos = bno << inode->i_blkbits;
	unsigned blocksize = i_blocksize(inode);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	int ret;

	if (filemap_write_and_wait(mapping))
		return 0;

	bno = 0;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	while ((ret = iomap_iter(&iter, ops)) > 0) {
		if (iter.iomap.type == IOMAP_MAPPED)
			bno = iomap_sector(&iter.iomap, iter.pos) >> blkshift;
		/* leave iter.processed unset to abort loop */
	}
<<<<<<< HEAD
	if (ret)
		return 0;

=======
	ret = iomap_apply(inode, pos, blocksize, 0, ops, &bno,
			  iomap_bmap_actor);
	if (ret)
		return 0;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	if (ret)
		return 0;

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	return bno;
}
EXPORT_SYMBOL_GPL(iomap_bmap);
