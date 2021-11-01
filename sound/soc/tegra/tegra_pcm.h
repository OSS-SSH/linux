/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * tegra_pcm.h - Definitions for Tegra PCM driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * Copyright (c) 2009-2010, NVIDIA Corporation.
 * Scott Peterson <speterson@nvidia.com>
 *
 * Copyright (C) 2010 Google, Inc.
 * Iliyan Malchev <malchev@google.com>
 */

#ifndef __TEGRA_PCM_H__
#define __TEGRA_PCM_H__

#include <sound/dmaengine_pcm.h>
#include <sound/asound.h>

int tegra_pcm_construct(struct snd_soc_component *component,
			struct snd_soc_pcm_runtime *rtd);
<<<<<<< HEAD
<<<<<<< HEAD
=======
void tegra_pcm_destruct(struct snd_soc_component *component,
			struct snd_pcm *pcm);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int tegra_pcm_open(struct snd_soc_component *component,
		   struct snd_pcm_substream *substream);
int tegra_pcm_close(struct snd_soc_component *component,
		    struct snd_pcm_substream *substream);
int tegra_pcm_hw_params(struct snd_soc_component *component,
			struct snd_pcm_substream *substream,
			struct snd_pcm_hw_params *params);
<<<<<<< HEAD
<<<<<<< HEAD
=======
int tegra_pcm_hw_free(struct snd_soc_component *component,
		      struct snd_pcm_substream *substream);
int tegra_pcm_mmap(struct snd_soc_component *component,
		   struct snd_pcm_substream *substream,
		   struct vm_area_struct *vma);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
snd_pcm_uframes_t tegra_pcm_pointer(struct snd_soc_component *component,
				    struct snd_pcm_substream *substream);
int tegra_pcm_platform_register(struct device *dev);
int tegra_pcm_platform_register_with_chan_names(struct device *dev,
				struct snd_dmaengine_pcm_config *config,
				char *txdmachan, char *rxdmachan);
void tegra_pcm_platform_unregister(struct device *dev);

#endif
