/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2020 Intel Corporation
 */

#ifndef SELFTEST_ENGINE_HEARTBEAT_H
#define SELFTEST_ENGINE_HEARTBEAT_H

struct intel_engine_cs;

void st_engine_heartbeat_disable(struct intel_engine_cs *engine);
<<<<<<< HEAD
<<<<<<< HEAD
void st_engine_heartbeat_disable_no_pm(struct intel_engine_cs *engine);
void st_engine_heartbeat_enable(struct intel_engine_cs *engine);
void st_engine_heartbeat_enable_no_pm(struct intel_engine_cs *engine);
=======
void st_engine_heartbeat_enable(struct intel_engine_cs *engine);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void st_engine_heartbeat_disable_no_pm(struct intel_engine_cs *engine);
void st_engine_heartbeat_enable(struct intel_engine_cs *engine);
void st_engine_heartbeat_enable_no_pm(struct intel_engine_cs *engine);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

#endif /* SELFTEST_ENGINE_HEARTBEAT_H */
