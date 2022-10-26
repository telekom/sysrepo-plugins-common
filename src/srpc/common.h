/**
 * @file common.h
 * @brief Common found plugin functionalities which are used throughout the plugins.
 *
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef SRPC_COMMON_H
#define SRPC_COMMON_H

#include "types.h"

#include <stdbool.h>
#include <sysrepo_types.h>
#include <sysrepo.h>

// Library logger name.
#define SRPC_PLUGIN_NAME "srpc"

/**
 * Safely call a function and jump to an error point if and error occurs - checks for returned error code to be 0.
 *
 * @param err_var Int error code variable to be set to the function return.
 * @param func_call Written function call like printf("Hello World").
 * @param jump_point Where to jump using goto if an error occurs.
 *
 */
#define SRPC_SAFE_CALL_ERR(err_var, func_call, jump_point)                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((err_var = func_call) != 0)                                                                                \
        {                                                                                                              \
            SRPLG_LOG_ERR(SRPC_PLUGIN_NAME, "%s:%d %s error (%d)", __FILE__, __LINE__, #func_call, err_var);           \
            goto jump_point;                                                                                           \
        }                                                                                                              \
    } while (0)

/**
 * Safely call a function and jump to an error point if and error occurs - checks for returned error code to be 0.
 *
 * @param err_var Int error code variable to be set to the function return.
 * @param cond Error condition.
 * @param func_call Written function call like printf("Hello World").
 * @param jump_point Where to jump using goto if an error occurs.
 *
 */
#define SRPC_SAFE_CALL_ERR_COND(err_var, cond, func_call, jump_point)                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        err_var = func_call;                                                                                           \
        if (cond)                                                                                                      \
        {                                                                                                              \
            SRPLG_LOG_ERR(SRPC_PLUGIN_NAME, "%s:%d %s error (%d)", __FILE__, __LINE__, #func_call, err_var);           \
            goto jump_point;                                                                                           \
        }                                                                                                              \
    } while (0)

/**
 * Safely call a function and jump to an error point if and error occurs - checks for returned pointer to be NULL.
 *
 * @param ptr_var Pointer variable to be set to the function return.
 * @param func_call Written function call like printf("Hello World").
 * @param jump_point Where to jump using goto if an error occurs.
 *
 */
#define SRPC_SAFE_CALL_PTR(ptr_var, func_call, jump_point)                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((ptr_var = func_call) == NULL)                                                                             \
        {                                                                                                              \
            SRPLG_LOG_ERR(SRPC_PLUGIN_NAME, "%s:%d %s error (NULL)", __FILE__, __LINE__, #func_call);                  \
            goto jump_point;                                                                                           \
        }                                                                                                              \
    } while (0)

/**
 * Check wether the datastore contains any data or not based on the provided path to check.
 *
 * @param session Sysrepo session to the datastore to check.
 * @param path Path to the data for checking.
 * @param empty Boolean value to set.
 *
 * @return Error code - 0 on success.
 */
int srpc_check_empty_datastore(sr_session_ctx_t *session, const char *path, bool *empty);

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
                         srpc_change_init_cb init_cb, srpc_change_free_cb free_cb);

/**
 * Copy file from source to destination.
 *
 * @param source Source file path.
 * @param destination Destination file path.
 *
 * @return Error code - 0 on success.
 */
int srpc_copy_file(const char *source, const char *destination);

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
int srpc_extract_xpath_key_value(const char *xpath, const char *list, const char *key, char *buffer,
                                 size_t buffer_size);

#endif // SRPC_COMMON_H