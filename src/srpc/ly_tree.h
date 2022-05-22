/**
 * @file ly_tree.h
 * @brief libyang tree creation API
 */
#ifndef SRPC_LY_TREE_H
#define SRPC_LY_TREE_H

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