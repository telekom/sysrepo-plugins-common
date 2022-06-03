/**
 * @file change_tree.h
 * @brief API for creating a tree of changes instead of relying on the sysrepo change iterator API
 */
#ifndef SRPC_CHANGE_TREE_H
#define SRPC_CHANGE_TREE_H

#include "types.h"

/**
 * Create a new node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_change_node_t *srpc_change_node_new(const char *name);

/**
 * Set values pair for the node.
 *
 * @param node Node to use.
 * @param current_value Currently set value.
 * @param previous_value Previous node value.
 *
 * @return Error code - 0 on success.
 */
int srpc_change_node_set_value(srpc_change_node_t *node, const char *current_value, const char *previous_value);

/**
 * Set node operation to apply.
 *
 * @param node Node to use.
 * @param operation Applied operation on the node.
 *
 */
void srpc_change_node_set_operation(srpc_change_node_t *node, sr_change_oper_t operation);

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_change_node_t *srpc_change_node_add_child(srpc_change_node_t *node, const char *name);

/**
 * Return number of children a node has.
 *
 * @param node Node to use.
 *
 * @return Number of children a node has.
 */
size_t srpc_change_node_get_children_count(srpc_change_node_t *node);

/**
 * Return n'th child.
 *
 * @param node Node to use.
 * @param n Child index number.
 *
 * @return Child at n'th position.
 */
srpc_change_node_t *srpc_change_node_get_child(srpc_change_node_t *node, const size_t n);

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_change_node_free(srpc_change_node_t *node);

#endif // SRPC_CHANGE_TREE_H