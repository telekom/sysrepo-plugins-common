/**
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#include <srpc/common.h>
#include <sysrepo.h>
#include <sysrepo/xpath.h>

#include <fcntl.h>
#include <sys/sendfile.h>

/**
 * Check wether the datastore contains any data or not based on the provided path to check.
 *
 * @param session Sysrepo session to the datastore to check.
 * @param path Path to the data for checking.
 * @param empty Boolean value to set.
 *
 * @return Error code - 0 on success.
 */
int srpc_check_empty_datastore(sr_session_ctx_t *session, const char *path, bool *empty)
{
    int error = 0;
    bool is_empty = true;
    sr_val_t *values = NULL;
    size_t value_cnt = 0;

    error = sr_get_items(session, path, 0, SR_OPER_DEFAULT, &values, &value_cnt);
    if (error)
    {
        goto error_out;
    }

    if (value_cnt > 0)
    {
        is_empty = false;

        // free recieved values
        sr_free_values(values, value_cnt);
    }

    *empty = is_empty;

    goto out;

error_out:
    error = -1;

out:
    return error;
}

/**
 * Iterate changes for the provided xpath and use callback on each change.
 *
 * @param priv Private user data - pass plugin context.
 * @param session Sysrepo session to use for iteration.
 * @param xpath XPath for the changes iterator.
 * @param cb Callback to call on each change.
 * @param init_cb Callback for changes data initialization - can be NULL if no data is needed.
 * @param free_cb Callback for freeing changes data - can be NULL if no data is allocated during init.
 *
 * @return Error code - 0 on success.
 */
int srpc_iterate_changes(void *priv, sr_session_ctx_t *session, const char *xpath, srpc_change_cb cb,
                         srpc_change_init_cb init_cb, srpc_change_free_cb free_cb)
{
    int error = 0;

    // sysrepo
    sr_change_iter_t *changes_iterator = NULL;

    srpc_change_ctx_t change_ctx;

    // initialize changes data
    if (init_cb)
    {
        error = init_cb(priv);
        if (error)
        {
            error = 1;
            goto out;
        }
    }

    error = sr_get_changes_iter(session, xpath, &changes_iterator);
    if (error != SR_ERR_OK)
    {
        error = 2;
        goto out;
    }

    int counter = 1;

    while (sr_get_change_tree_next(session, changes_iterator, &change_ctx.operation, &change_ctx.node,
                                   &change_ctx.previous_value, &change_ctx.previous_list,
                                   &change_ctx.previous_default) == SR_ERR_OK)
    {
        error = cb(priv, session, &change_ctx);
        if (error)
        {
            // return number of invalid callback
            error = -counter;
            goto out;
        }
        ++counter;
    }

out:
    // free allocated changes data
    if (free_cb)
    {
        free_cb(priv);
    }

    // free iterator data
    sr_free_change_iter(changes_iterator);

    return error;
}

/**
 * Copy file from source to destination.
 *
 * @param source Source file path.
 * @param destination Destination file path.
 *
 * @return Error code - 0 on success.
 */
int srpc_copy_file(const char *source, const char *destination)
{
    int error = 0;
    int read_fd = -1;
    int write_fd = -1;
    struct stat stat_buf = {0};
    off_t offset = 0;

    read_fd = open(source, O_RDONLY);
    if (read_fd == -1)
    {
        goto error_out;
    }

    if (fstat(read_fd, &stat_buf) != 0)
    {
        goto error_out;
    }

    write_fd = open(destination, O_CREAT | O_WRONLY | O_TRUNC, stat_buf.st_mode);
    if (write_fd == -1)
    {
        goto error_out;
    }

    if (sendfile(write_fd, read_fd, &offset, (size_t)stat_buf.st_size) == -1)
    {
        goto error_out;
    }

    goto out;

error_out:
    error = -1;

out:
    if (read_fd != -1)
    {
        close(read_fd);
    }

    if (write_fd != -1)
    {
        close(write_fd);
    }

    return error;
}

/**
 * Extract a key value from the given xpath and write it to the buffer.
 *
 * @param xpath XPath of the node.
 * @param list List name.
 * @param key Key name.
 * @param buffer Buffer to which the key value will be written.
 * @param buffer_size Size of the provided buffer.
 *
 * @return Error code - 0 on success.
 */
int srpc_extract_xpath_key_value(const char *xpath, const char *list, const char *key, char *buffer, size_t buffer_size)
{
    int error = 0;

    const char *name = NULL;
    char *xpath_copy = NULL;

    sr_xpath_ctx_t xpath_ctx = {0};

    // copy xpath due to changing it when using xpath_ctx from sysrepo
    SRPC_SAFE_CALL_PTR(xpath_copy, strdup(xpath), error_out);

    // extract key
    SRPC_SAFE_CALL_PTR(name, sr_xpath_key_value(xpath_copy, list, key, &xpath_ctx), error_out);

    // store to buffer
    SRPC_SAFE_CALL_ERR_COND(error, error < 0, snprintf(buffer, buffer_size, "%s", name), error_out);

    error = 0;
    goto out;

error_out:
    error = -1;

out:
    if (xpath_copy)
    {
        free(xpath_copy);
    }

    return error;
}

/**
 * Get information about a feature from the current session.
 *
 * @param session Sysrepo session.
 * @param module YANG module to use.
 * @param feature Feature in the YANG module.
 * @param enabled Set wether the feature is enabled or not.
 *
 * @return Error code - 0 on success.
 */
int srpc_check_feature_status(sr_session_ctx_t *session, const char *module, const char *feature, bool *enabled)
{
    int error = 0;
    const struct ly_ctx *ly_ctx = NULL;
    const struct lys_module *ly_mod = NULL;
    sr_conn_ctx_t *conn_ctx;

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

    if (lys_feature_value(ly_mod, feature) == LY_SUCCESS)
    {
        *enabled = true;
    }
    else
    {
        *enabled = false;
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