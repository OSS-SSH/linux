/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef INTEL_ENGINE_HEARTBEAT_H
#define INTEL_ENGINE_HEARTBEAT_H

struct intel_engine_cs;
<<<<<<< HEAD
struct intel_gt;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554

void intel_engine_init_heartbeat(struct intel_engine_cs *engine);

int intel_engine_set_heartbeat(struct intel_engine_cs *engine,
			       unsigned long delay);

void intel_engine_park_heartbeat(struct intel_engine_cs *engine);
void intel_engine_unpark_heartbeat(struct intel_engine_cs *engine);

<<<<<<< HEAD
void intel_gt_park_heartbeats(struct intel_gt *gt);
void intel_gt_unpark_heartbeats(struct intel_gt *gt);

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
int intel_engine_pulse(struct intel_engine_cs *engine);
int intel_engine_flush_barriers(struct intel_engine_cs *engine);

#endif /* INTEL_ENGINE_HEARTBEAT_H */
