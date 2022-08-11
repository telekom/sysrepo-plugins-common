/**
 * Copyright (c) 2022 Deutsche Telekom AG.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#include <srpc/ly_tree.h>

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
                                  const char *path)
{
    LY_ERR ly_error = LY_SUCCESS;

    ly_error = lyd_new_path(parent, ly_ctx, path, NULL, 0, store);
    if (ly_error != LY_SUCCESS)
    {
        return -1;
    }

    return 0;
}

/**
 * Generic child search.
 *
 * @param node Node to search.
 * @param node_type Schema node type - LYS_CONTAINER, LYS_LIST etc.
 * @param name Name of the node to search for.
 *
 * @return Error code - 0 on success.
 */
struct lyd_node *srpc_ly_tree_get_child(const struct lyd_node *node, uint16_t node_type, const char *name)
{
    struct lyd_node *ch = lyd_child(node);

    while (ch)
    {
        if (strcmp(LYD_NAME(ch), name) == 0 && ch->schema->nodetype == node_type)
        {
            return ch;
        }
        ch = ch->next;
    }

    return NULL;
}

/**
 * Container node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_container(const struct lyd_node *node, const char *name)
{
    return srpc_ly_tree_get_child(node, LYS_CONTAINER, name);
}

/**
 * List node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_list(const struct lyd_node *node, const char *name)
{
    return srpc_ly_tree_get_child(node, LYS_LIST, name);
}

/**
 * Leaf list node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_leaf_list(const struct lyd_node *node, const char *name)
{
    return srpc_ly_tree_get_child(node, LYS_LEAFLIST, name);
}

/**
 * Leaf node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_leaf(const struct lyd_node *node, const char *name)
{
    return srpc_ly_tree_get_child(node, LYS_LEAF, name);
}

/**
 * Get next list element.
 *
 * @param node Current list element.
 *
 * @return Next list node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_list_next(const struct lyd_node *node)
{
    const char *name = LYD_NAME(node);
    struct lyd_node *iter = node->next;

    while (iter)
    {
        if (iter->schema->nodetype == LYS_LIST && !strcmp(LYD_NAME(iter), name))
        {
            return iter;
        }

        iter = iter->next;
    }

    return NULL;
}

/**
 * Get next leaf list element.
 *
 * @param node Current leaf list element.
 *
 * @return Next list node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_leaf_list_next(const struct lyd_node *node)
{
    const char *name = LYD_NAME(node);
    struct lyd_node *iter = node->next;

    while (iter)
    {
        if (iter->schema->nodetype == LYS_LEAFLIST && !strcmp(LYD_NAME(iter), name))
        {
            return iter;
        }

        iter = iter->next;
    }

    return NULL;
}

/**
 * Choice node search.
 *
 * @param node Node to search.
 * @param name Name of the node to search for.
 *
 * @return Child node, NULL if not found.
 */
struct lyd_node *srpc_ly_tree_get_child_choice(const struct lyd_node *node, const char *name)
{
    return srpc_ly_tree_get_child(node, LYS_CHOICE, name);
}

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
                             const char *path, const char *key, const char *key_value)
{
    LY_ERR ly_error = LY_SUCCESS;
    char path_buffer[PATH_MAX] = {0};

    if (snprintf(path_buffer, sizeof(path_buffer), "%s[%s=\"%s\"]", path, key, key_value) < 0)
    {
        return -1;
    }

    ly_error = lyd_new_path(parent, ly_ctx, path_buffer, key_value, 0, store);
    if (ly_error != LY_SUCCESS)
    {
        return -2;
    }

    return 0;
}

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
                                  const char *path, const srpc_key_value_pair_t kv_pairs[], const size_t keys_count)
{
    LY_ERR ly_error = LY_SUCCESS;
    char path_buffer[PATH_MAX] = {0};
    char *next_ptr = NULL;
    int rc = 0;

    rc = snprintf(path_buffer, sizeof(path_buffer), "%s", path);

    for (int i = 0; i < keys_count; i++)
    {
        next_ptr = path_buffer + rc;
        rc = snprintf(next_ptr, sizeof(path_buffer) - (next_ptr - path_buffer), "[%s=\"%s\"]", kv_pairs[i].key,
                      kv_pairs[i].value);
        if (rc < 0)
        {
            return i;
        }
    }

    ly_error = lyd_new_path(parent, ly_ctx, path_buffer, NULL, 0, store);
    if (ly_error != LY_SUCCESS)
    {
        return -1;
    }

    return 0;
}

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
                             const char *path, const char *value)
{
    LY_ERR ly_error = LY_SUCCESS;

    ly_error = lyd_new_path(parent, ly_ctx, path, value, 0, store);
    if (ly_error != LY_SUCCESS)
    {
        return -1;
    }

    return 0;
}

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
                                  const char *path, const char *value)
{
    LY_ERR ly_error = LY_SUCCESS;

    ly_error = lyd_new_path(parent, ly_ctx, path, value, 0, store);
    if (ly_error != LY_SUCCESS)
    {
        return -1;
    }

    return 0;
}