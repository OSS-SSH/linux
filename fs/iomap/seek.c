// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2017 Red Hat, Inc.
<<<<<<< HEAD
 * Copyright (c) 2018-2021 Christoph Hellwig.
=======
 * Copyright (c) 2018 Christoph Hellwig.
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
 */
#include <linux/module.h>
#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/iomap.h>
#include <linux/pagemap.h>
#include <linux/pagevec.h>

<<<<<<< HEAD
static loff_t iomap_seek_hole_iter(const struct iomap_iter *iter,
		loff_t *hole_pos)
{
	loff_t length = iomap_length(iter);

	switch (iter->iomap.type) {
	case IOMAP_UNWRITTEN:
		*hole_pos = mapping_seek_hole_data(iter->inode->i_mapping,
				iter->pos, iter->pos + length, SEEK_HOLE);
		if (*hole_pos == iter->pos + length)
			return length;
		return 0;
	case IOMAP_HOLE:
		*hole_pos = iter->pos;
=======
static loff_t
iomap_seek_hole_actor(struct inode *inode, loff_t start, loff_t length,
		      void *data, struct iomap *iomap, struct iomap *srcmap)
{
	loff_t offset = start;

	switch (iomap->type) {
	case IOMAP_UNWRITTEN:
		offset = mapping_seek_hole_data(inode->i_mapping, start,
				start + length, SEEK_HOLE);
		if (offset == start + length)
			return length;
		fallthrough;
	case IOMAP_HOLE:
		*(loff_t *)data = offset;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		return 0;
	default:
		return length;
	}
}

loff_t
<<<<<<< HEAD
iomap_seek_hole(struct inode *inode, loff_t pos, const struct iomap_ops *ops)
{
	loff_t size = i_size_read(inode);
	struct iomap_iter iter = {
		.inode	= inode,
		.pos	= pos,
		.flags	= IOMAP_REPORT,
	};
	int ret;

	/* Nothing to be found before or beyond the end of the file. */
	if (pos < 0 || pos >= size)
		return -ENXIO;

	iter.len = size - pos;
	while ((ret = iomap_iter(&iter, ops)) > 0)
		iter.processed = iomap_seek_hole_iter(&iter, &pos);
	if (ret < 0)
		return ret;
	if (iter.len) /* found hole before EOF */
		return pos;
	return size;
}
EXPORT_SYMBOL_GPL(iomap_seek_hole);

static loff_t iomap_seek_data_iter(const struct iomap_iter *iter,
		loff_t *hole_pos)
{
	loff_t length = iomap_length(iter);

	switch (iter->iomap.type) {
	case IOMAP_HOLE:
		return length;
	case IOMAP_UNWRITTEN:
		*hole_pos = mapping_seek_hole_data(iter->inode->i_mapping,
				iter->pos, iter->pos + length, SEEK_DATA);
		if (*hole_pos < 0)
			return length;
		return 0;
	default:
		*hole_pos = iter->pos;
=======
iomap_seek_hole(struct inode *inode, loff_t offset, const struct iomap_ops *ops)
{
	loff_t size = i_size_read(inode);
	loff_t length = size - offset;
	loff_t ret;

	/* Nothing to be found before or beyond the end of the file. */
	if (offset < 0 || offset >= size)
		return -ENXIO;

	while (length > 0) {
		ret = iomap_apply(inode, offset, length, IOMAP_REPORT, ops,
				  &offset, iomap_seek_hole_actor);
		if (ret < 0)
			return ret;
		if (ret == 0)
			break;

		offset += ret;
		length -= ret;
	}

	return offset;
}
EXPORT_SYMBOL_GPL(iomap_seek_hole);

static loff_t
iomap_seek_data_actor(struct inode *inode, loff_t start, loff_t length,
		      void *data, struct iomap *iomap, struct iomap *srcmap)
{
	loff_t offset = start;

	switch (iomap->type) {
	case IOMAP_HOLE:
		return length;
	case IOMAP_UNWRITTEN:
		offset = mapping_seek_hole_data(inode->i_mapping, start,
				start + length, SEEK_DATA);
		if (offset < 0)
			return length;
		fallthrough;
	default:
		*(loff_t *)data = offset;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
		return 0;
	}
}

loff_t
<<<<<<< HEAD
iomap_seek_data(struct inode *inode, loff_t pos, const struct iomap_ops *ops)
{
	loff_t size = i_size_read(inode);
	struct iomap_iter iter = {
		.inode	= inode,
		.pos	= pos,
		.flags	= IOMAP_REPORT,
	};
	int ret;

	/* Nothing to be found before or beyond the end of the file. */
	if (pos < 0 || pos >= size)
		return -ENXIO;

	iter.len = size - pos;
	while ((ret = iomap_iter(&iter, ops)) > 0)
		iter.processed = iomap_seek_data_iter(&iter, &pos);
	if (ret < 0)
		return ret;
	if (iter.len) /* found data before EOF */
		return pos;
	/* We've reached the end of the file without finding data */
	return -ENXIO;
=======
iomap_seek_data(struct inode *inode, loff_t offset, const struct iomap_ops *ops)
{
	loff_t size = i_size_read(inode);
	loff_t length = size - offset;
	loff_t ret;

	/* Nothing to be found before or beyond the end of the file. */
	if (offset < 0 || offset >= size)
		return -ENXIO;

	while (length > 0) {
		ret = iomap_apply(inode, offset, length, IOMAP_REPORT, ops,
				  &offset, iomap_seek_data_actor);
		if (ret < 0)
			return ret;
		if (ret == 0)
			break;

		offset += ret;
		length -= ret;
	}

	if (length <= 0)
		return -ENXIO;
	return offset;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
EXPORT_SYMBOL_GPL(iomap_seek_data);
