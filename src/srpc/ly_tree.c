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