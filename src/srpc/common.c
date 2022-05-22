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