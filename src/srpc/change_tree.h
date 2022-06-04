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
 * Get name of the node.
 *
 * @param node Node to use.
 *
 * @return Node name.
 */
const char *srpc_change_node_get_name(srpc_change_node_t *node);

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
 * Get current value of the node.
 *
 * @param node Node to use.
 *
 * @return Currently set value of the node.
 */
const char *srpc_change_node_get_current_value(srpc_change_node_t *node);

/**
 * Get previous value of the node.
 *
 * @param node Node to use.
 *
 * @return Previous set value of the node.
 */
const char *srpc_change_node_get_previous_value(srpc_change_node_t *node);

/**
 * Set node operation to apply.
 *
 * @param node Node to use.
 * @param operation Applied operation on the node.
 *
 */
void srpc_change_node_set_operation(srpc_change_node_t *node, sr_change_oper_t operation);

/**
 * Get node operation.
 *
 * @param node Node to use.
 *
 * @return Operation on the node.
 */
sr_change_oper_t srpc_change_node_get_operation(srpc_change_node_t *node);

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
 * @return Child node at the n'th position.
 */
const srpc_change_node_t *srpc_change_node_get_child(srpc_change_node_t *node, const size_t n);

/**
 * Return child with the provided name.
 *
 * @param node Node to use.
 * @param name Child name.
 *
 * @return First found child with the provided name, NULL if not found.
 */
const srpc_change_node_t *srpc_change_node_get_child_by_name(srpc_change_node_t *node, const char *name);

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child current value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_change_node_t *srpc_change_node_get_child_by_current_value(srpc_change_node_t *node, const char *name,
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
const srpc_change_node_t *srpc_change_node_get_child_by_previous_value(srpc_change_node_t *node, const char *name,
                                                                       const char *value);

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_change_node_free(srpc_change_node_t *node);

#endif // SRPC_CHANGE_TREE_H