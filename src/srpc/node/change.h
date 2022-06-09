/**
 * @file change.h
 * @brief API for creating a tree of change nodes.
 */
#ifndef SRPC_NODE_CHANGE_H
#define SRPC_NODE_CHANGE_H

#include <sysrepo_types.h>
#include <srpc/types.h>

/**
 * Create a new node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_change_node_new(const char *name);

/**
 * Set node operation.
 *
 * @param node Node to use.
 * @param operation Operation for the given node.
 *
 */
void srpc_change_node_set_operation(srpc_node_t *node, sr_change_oper_t operation);

/**
 * Get node operation.
 *
 * @param node Node to use.
 *
 * @return Operation of the node.
 */
sr_change_oper_t srpc_change_node_get_operation(const srpc_node_t *node);

/**
 * Set change values - current and previous value.
 *
 * @param node Node to use.
 * @param current_value Current node value.
 * @param previous_value Previous node value.
 *
 * @return Error code - 0 on success.
 */
int srpc_change_node_set_value(srpc_node_t *node, const char *current_value, const char *previous_value);

/**
 * Get current node value.
 *
 * @param node Node to use.
 *
 * @return Current node value.
 */
const char *srpc_change_node_get_current_value(const srpc_node_t *node);

/**
 * Get previous node value.
 *
 * @param node Node to use.
 *
 * @return Previous node value.
 */
const char *srpc_change_node_get_previous_value(const srpc_node_t *node);

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_change_node_add_child(srpc_node_t *node, const char *name);

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child current value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_node_t *srpc_change_node_get_child_by_current_value(const srpc_node_t *node, const char *name,
                                                               const char *value);

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child previous value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_node_t *srpc_change_node_get_child_by_previous_value(const srpc_node_t *node, const char *name,
                                                                const char *value);

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 *
 */
void srpc_change_node_print(const srpc_node_t *node, FILE *file);

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_change_node_free(srpc_node_t *node);

#endif // SRPC_NODE_CHANGE_H