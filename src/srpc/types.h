/**
 * @file types.h
 * @brief Common found types used in the plugins.
 *
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef SRPC_TYPES_H
#define SRPC_TYPES_H

#include <libyang/libyang.h>
#include <sysrepo_types.h>

typedef struct srpc_module_change_s srpc_module_change_t;
typedef struct srpc_operational_s srpc_operational_t;
typedef struct srpc_rpc_s srpc_rpc_t;
typedef struct srpc_startup_load_s srpc_startup_load_t;
typedef struct srpc_startup_store_s srpc_startup_store_t;
typedef struct srpc_node_s srpc_node_t;
typedef struct srpc_change_ctx_s srpc_change_ctx_t;
typedef struct srpc_key_value_pair_s srpc_key_value_pair_t;
typedef struct srpc_feature_status_hash_s srpc_feature_status_hash_t;
typedef enum srpc_check_status_e srpc_check_status_t;
typedef enum srpc_any_node_kind_e srpc_any_node_kind_t;

/**
 * Struct used to gather all module change callbacks based on a path.
 */
struct srpc_module_change_s
{
    const char *path;       ///< Path to which the callback will be applied.
    sr_module_change_cb cb; ///< Module change callback.
};

/**
 * Struct used to gather all operational callbacks based on a path.
 */
struct srpc_operational_s
{
    const char *module;      ///< Module to which to apply the callback to.
    const char *path;        ///< Path to which the callback will be applied.
    sr_oper_get_items_cb cb; ///< Operational callback.
};

/**
 * Struct used to gather all RPC callbacks based on a path.
 */
struct srpc_rpc_s
{
    const char *path; ///< Path to which the callback will be applied.
    sr_rpc_cb cb;     ///< RPC callback.
};

/** Callback type for loading startup data into parent_node. Setup an array of callbacks and use them on the needed
 * node. */
typedef int (*srpc_startup_load_cb)(void *priv, sr_session_ctx_t *session, const struct ly_ctx *ly_ctx,
                                    struct lyd_node *parent_node);

/** Callback type for storing values from provided parent node. Setup an array of callbacks and use them on the needed
 * node. */
typedef int (*srpc_startup_store_cb)(void *priv, const struct lyd_node *parent_node);

/** Callback type for initializing changes callback data before iterating changes. */
typedef int (*srpc_change_init_cb)(void *priv);

/** Callback type for freeing changes callback data after iterating changes. */
typedef void (*srpc_change_free_cb)(void *priv);

/** Callback type for applying changes when using sr_get_change_tree_next() functionality. */
typedef int (*srpc_change_cb)(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);

/** Callback used to allocate data for the new node. */
typedef void *(*srpc_node_data_alloc_cb)(void);

/** Callback used for node data comparison. */
typedef int (*srpc_node_data_cmp_cb)(const void *n1, const void *n2);

/** Callback used to free the node data. */
typedef void (*srpc_node_data_dealloc_cb)(void **value);

/** Callback used to print node data. */
typedef void (*srpc_node_data_print_cb)(const char *node_name, const void *data, FILE *file);

/**
 * Used mostly for error messages with the provided callback.
 */
struct srpc_startup_store_s
{
    const char *name;         ///< Name of the value for which the callback is being called.
    srpc_startup_store_cb cb; ///< Store callback.
};

/**
 * Used mostly for error messages with the provided callback.
 */
struct srpc_startup_load_s
{
    const char *name;        ///< Name of the value for which the callback is being called.
    srpc_startup_load_cb cb; ///< Load callback.
};

/**
 * Change context - operation, previous value etc.
 */
struct srpc_change_ctx_s
{
    const struct lyd_node *node; ///< Current changed libyang node.
    const char *previous_value;  ///< Previous node value.
    const char *previous_list;   ///< Previous list keys predicate.
    int previous_default;        ///< Previous value default flag.
    sr_change_oper_t operation;  ///< Operation being applied on the node.
};

/**
 * List key/value pair - used for creating list elements.
 */
struct srpc_key_value_pair_s
{
    const char *key;   ///< List key.
    const char *value; ///< Value for the list key.
};

/**
 * Used as return codes of the check API for particular YANG values (leafs, leaf-list or list).
 * The enum value is returned from a function which checks wether the value/values exist/exists on the system or not.
 */
enum srpc_check_status_e
{
    srpc_check_status_none = 0,     ///< Default value - means nothing.
    srpc_check_status_error,        ///< Error with comparing values.
    srpc_check_status_non_existant, ///< The values don't exist on the system at all.
    srpc_check_status_equal,        ///< The values exist and they are all equal to the compared values.
    srpc_check_status_partial,      ///< The values are partially equal - some exist and some don't.
};

/**
 * Kind/type of the "any" node.
 */
enum srpc_any_node_kind_e
{
    srpc_any_node_kind_none = 0, ///< No set kind for the node.
    srpc_any_node_kind_s8,       ///< int8_t
    srpc_any_node_kind_u8,       ///< uint8_t
    srpc_any_node_kind_s16,      ///< int16_t
    srpc_any_node_kind_u16,      ///< uint16_t
    srpc_any_node_kind_s32,      ///< int32_t
    srpc_any_node_kind_u32,      ///< uint32_t
    srpc_any_node_kind_s64,      ///< int64_t
    srpc_any_node_kind_u64,      ///< uint64_t
    srpc_any_node_kind_float,    ///< float
    srpc_any_node_kind_double,   ///< double
    srpc_any_node_kind_str,      ///< const char *
    srpc_any_node_kind_mem,      ///< void *
};

#endif // SRPC_TYPES_H
