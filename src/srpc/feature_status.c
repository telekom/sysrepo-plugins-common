/**
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 *
 * SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
 * SPDX-FileContributor: Sartura Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "feature_status.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>
#include <uthash.h>

#include <sysrepo.h>
#include <libyang/libyang.h>

/**
 * Single feature status hash element.
 */
struct srpc_feature_status_hash_s
{
    const char *id;    ///< Key - feature name.
    uint8_t enabled;   ///< Value of the feature - enabled or disabled.
    UT_hash_handle hh; ///< UTHash reserved data.
};

/**
 * Create a brand new feature status hash.
 *
 * @return New feature status hash data structure.
 */
srpc_feature_status_hash_t *srpc_feature_status_hash_new(void)
{
    // must first be initialized to NULL
    return NULL;
}

/**
 * Load feature status values for each feature found in the provided session and needed module.
 *
 * @param fs_hash Initialized feature status hash data structure.
 * @param session Sysrepo session.
 * @param module Module to use for feature extraction.
 *
 * @return Error code - 0 on success.
 */
int srpc_feature_status_hash_load(srpc_feature_status_hash_t **fs_hash, sr_session_ctx_t *session, const char *module)
{
    int error = 0;
    sr_conn_ctx_t *conn_ctx;
    const struct ly_ctx *ly_ctx = NULL;
    const struct lys_module *ly_mod = NULL;
    const struct lysp_module *pmod = NULL;
    struct lysp_feature *feature_iter = NULL;

    uint32_t idx = 0;

    conn_ctx = sr_session_get_connection(session);
    if (!conn_ctx)
    {
        goto error_out;
    }

    ly_ctx = sr_acquire_context(conn_ctx);
    if (!ly_ctx)
    {
        goto error_out;
    }

    ly_mod = ly_ctx_get_module_latest(ly_ctx, module);
    if (!ly_mod)
    {
        goto error_out;
    }

    pmod = ly_mod->parsed;
    feature_iter = lysp_feature_next(NULL, pmod, &idx);
    while (feature_iter)
    {
        const char *feature = feature_iter->name;

        srpc_feature_status_hash_t *new_fs = malloc(sizeof(srpc_feature_status_hash_t));
        if (!new_fs)
        {
            goto error_out;
        }

        new_fs->id = strdup(feature);
        if (!new_fs->id)
        {
            goto error_out;
        }

        if (lys_feature_value(ly_mod, feature) == LY_SUCCESS)
        {
            // add hash node - enabled
            new_fs->enabled = 1;
        }
        else
        {
            // add hash node - disabled
            new_fs->enabled = 0;
        }

        // add hash
        HASH_ADD_STR(*fs_hash, id, new_fs);

        feature_iter = lysp_feature_next(feature_iter, pmod, &idx);
    }

    goto out;

error_out:
    error = -1;

out:
    if (conn_ctx)
    {
        sr_release_context(conn_ctx);
    }

    return error;
}

/**
 * Reload already allocated feature status hash.
 *
 * @param fs_hash Initialized and loaded feature status hash data structure.
 * @param session Sysrepo session.
 * @param module Module to use for feature extraction.
 *
 * @return Error code - 0 on success.
 */
int srpc_feature_status_hash_reload(srpc_feature_status_hash_t **fs_hash, sr_session_ctx_t *session, const char *module)
{
    // free already allocated hash
    srpc_feature_status_hash_free(fs_hash);

    // allocate new hash
    *fs_hash = srpc_feature_status_hash_new();

    return srpc_feature_status_hash_load(fs_hash, session, module);
}

/**
 * Get feature value - enabled or disabled.
 *
 * @param fs_hash Feature status hash.
 * @param feature Feature to check.
 *
 * @return Wether the feature is enabled (1) or disabled/not found (0).
 */
uint8_t srpc_feature_status_hash_check(const srpc_feature_status_hash_t *fs_hash, const char *feature)
{
    srpc_feature_status_hash_t *fs = NULL;

    HASH_FIND_STR(fs_hash, feature, fs);

    if (fs)
    {
        return fs->enabled;
    }

    return 0;
}

/**
 * Free all hash data.
 *
 * @param fs_hash Feature status hash data structure.
 *
 */
void srpc_feature_status_hash_free(srpc_feature_status_hash_t **fs_hash)
{
    srpc_feature_status_hash_t *current = NULL, *tmp = NULL;

    HASH_ITER(hh, *fs_hash, current, tmp)
    {
        HASH_DEL(*fs_hash, current);

        // free data
        free((char *)current->id);

        // free allocated struct
        free(current);
    }
}