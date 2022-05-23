/**
 * @file types.h
 * @brief Common found types used in the plugins.
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

/** Callback type for applying changes when using sr_get_change_tree_next() functionality. */
typedef int (*srpc_change_cb)(void *priv, sr_session_ctx_t *session, const char *prev_value,
                              const struct lyd_node *node, sr_change_oper_t operation);

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

#endif // SRPC_TYPES_H
