/**
 * @file feature_status.h
 * @brief API for working with feature status hash data structure.
 *
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef SRPC_FEATURE_STATUS_H
#define SRPC_FEATURE_STATUS_H

#include "sysrepo_types.h"
#include "types.h"

/**
 * Create a brand new feature status hash.
 *
 * @return New feature status hash data structure.
 */
srpc_feature_status_hash_t *srpc_feature_status_hash_new(void);

/**
 * Load feature status values for each feature found in the provided session and needed module.
 *
 * @param fs_hash Initialized feature status hash data structure.
 * @param session Sysrepo session.
 * @param module Module to use for feature extraction.
 *
 * @return Error code - 0 on success.
 */
int srpc_feature_status_hash_load(srpc_feature_status_hash_t **fs_hash, sr_session_ctx_t *session, const char *module);

/**
 * Get feature value - enabled or disabled.
 *
 * @param fs_hash Feature status hash.
 * @param feature Feature to check.
 *
 * @return Wether the feature is enabled (1) or disabled/not found (0).
 */
uint8_t srpc_feature_status_hash_check(const srpc_feature_status_hash_t *fs_hash, const char *feature);

/**
 * Free all hash data.
 *
 * @param fs_hash Feature status hash data structure.
 *
 */
void srpc_feature_status_hash_free(srpc_feature_status_hash_t **fs_hash);

#endif // SRPC_FEATURE_STATUS_H