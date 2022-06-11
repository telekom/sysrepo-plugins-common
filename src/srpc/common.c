#include <srpc/common.h>
#include <sysrepo.h>

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
 *
 * @return Error code - 0 on success.
 */
int srpc_iterate_changes(void *priv, sr_session_ctx_t *session, const char *xpath, srpc_change_cb cb)
{
    int error = 0;

    // sysrepo
    sr_change_iter_t *changes_iterator = NULL;
    sr_change_oper_t operation = SR_OP_CREATED;
    const char *prev_value = NULL, *prev_list = NULL;
    int prev_default;

    srpc_change_ctx_t change_ctx;

    // libyang
    const struct lyd_node *node = NULL;

    error = sr_get_changes_iter(session, xpath, &changes_iterator);
    if (error != SR_ERR_OK)
    {
        return -1;
    }

    int counter = 2;

    while (sr_get_change_tree_next(session, changes_iterator, &change_ctx.operation, &change_ctx.node,
                                   &change_ctx.previous_value, &change_ctx.previous_list,
                                   &change_ctx.previous_default) == SR_ERR_OK)
    {
        error = cb(priv, session, &change_ctx);
        if (error)
        {
            // return number of invalid callback
            return -counter;
        }
        ++counter;
    }

    return 0;
}