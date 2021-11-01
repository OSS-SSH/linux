// SPDX-License-Identifier: GPL-2.0-only
#ifndef __MEMALLOC_LOCAL_H
#define __MEMALLOC_LOCAL_H

struct snd_malloc_ops {
<<<<<<< HEAD
<<<<<<< HEAD
	void *(*alloc)(struct snd_dma_buffer *dmab, size_t size);
=======
	int (*alloc)(struct snd_dma_buffer *dmab, size_t size);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	void *(*alloc)(struct snd_dma_buffer *dmab, size_t size);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	void (*free)(struct snd_dma_buffer *dmab);
	dma_addr_t (*get_addr)(struct snd_dma_buffer *dmab, size_t offset);
	struct page *(*get_page)(struct snd_dma_buffer *dmab, size_t offset);
	unsigned int (*get_chunk_size)(struct snd_dma_buffer *dmab,
				       unsigned int ofs, unsigned int size);
	int (*mmap)(struct snd_dma_buffer *dmab, struct vm_area_struct *area);
};

#ifdef CONFIG_SND_DMA_SGBUF
extern const struct snd_malloc_ops snd_dma_sg_ops;
#endif

#endif /* __MEMALLOC_LOCAL_H */
