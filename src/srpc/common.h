/**
 * @file common.h
 * @brief Common found plugin functionalities which are used throughout the plugins.
 */
#ifndef SRPC_COMMON_H
#define SRPC_COMMON_H

#include <stdbool.h>
#include <sysrepo_types.h>

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

#endif // SRPC_COMMON_H