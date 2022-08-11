/**
 * @file ly_tree.h
 * @brief libyang tree creation API
 *
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef SRPC_LY_TREE_H
#define SRPC_LY_TREE_H

#include "types.h"
#include <libyang/libyang.h>

/**
 * Create a container node inside of the parent node using the provided path.
 *
 * @param ly_ctx libyang context to use.
 * @param parent Parent node to add the child container to.
 * @param store  Variable to which the created container will be stored.
 * @param path Path of the node to create.
 *
 * @return Error code - 0 on success.
 */
int srpc_ly_tree_create_container(const struct ly_ctx *ly_ctx, struct lyd_node *parent, struct lyd_node **store,
                                  const char *path);

/**
 * Generic child search.
 *
 * @param node Node to search.
 * @param node_type Schema node type - LYS_CONTAINER, LYS_LIST etc.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child(const struct lyd_node *node, uint16_t node_type, const char *name);

/**
 * Container node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_container(const struct lyd_node *node, const char *name);

/**
 * List node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_list(const struct lyd_node *node, const char *name);

/**
 * Leaf list node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_leaf_list(const struct lyd_node *node, const char *name);

/**
 * Leaf node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_leaf(const struct lyd_node *node, const char *name);

/**
 * Get next list element.
 *
 * @param node Current list element.
 *
 * @return Next list node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_list_next(const struct lyd_node *node);

/**
 * Get next leaf list element.
 *
 * @param node Current leaf list element.
 *
 * @return Next list node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_leaf_list_next(const struct lyd_node *node);

/**
 * Choice node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_choice(const struct lyd_node *node, const char *name);

/**
 * Create a list node inside of the parent node using the provided path, key and its value.
 *
 * @param ly_ctx libyang context to use.
 * @param parent Parent node to add the child container to.
 * @param store  Variable to which the created container will be stored.
 * @param path Path of the node to create.
 * @param key Key of the list to set.
 * @param key_value Value of the key.
 *
 * @return Error code - 0 on success.
 */
int srpc_ly_tree_create_list(const struct ly_ctx *ly_ctx, struct lyd_node *parent, struct lyd_node **store,
                             const char *path, const char *key, const char *key_value);

/**
 * Create a list node based on all key value pairs.
 *
 * @param ly_ctx libyang context to use.
 * @param parent Parent node to add the child container to.
 * @param store  Variable to which the created container will be stored.
 * @param path Path of the node to create.
 * @param kv_pairs Key/value pairs.
 * @param keys_count Number of passed key/value pairs.
 *
 * @return Error code - 0 on success.
 */
int srpc_ly_tree_create_list_full(const struct ly_ctx *ly_ctx, struct lyd_node *parent, struct lyd_node **store,
                                  const char *path, const srpc_key_value_pair_t kv_pairs[], const size_t keys_count);

/**
 * Create a leaf node inside of the parent node using the provided path and value.
 *
 * @param ly_ctx libyang context to use.
 * @param parent Parent node to add the child container to.
 * @param store  Variable to which the created container will be stored.
 * @param path Path of the node to create.
 * @param value Value of the leaf node.
 *
 * @return Error code - 0 on success.
 */
int srpc_ly_tree_create_leaf(const struct ly_ctx *ly_ctx, struct lyd_node *parent, struct lyd_node **store,
                             const char *path, const char *value);

/**
 * Add a value to the leaf list using a provided path.
 * If no leaf list yet exitst, one is created.
 *
 * @param ly_ctx libyang context to use.
 * @param parent Parent node to add the child container to.
 * @param store  Variable to which the created container will be stored.
 * @param path Path of the node to create.
 * @param value Value of the leaf list node to append.
 *
 * @return Error code - 0 on success.
 */
int srpc_ly_tree_append_leaf_list(const struct ly_ctx *ly_ctx, struct lyd_node *parent, struct lyd_node **store,
                                  const char *path, const char *value);

#endif // SRPC_LY_TREE_H