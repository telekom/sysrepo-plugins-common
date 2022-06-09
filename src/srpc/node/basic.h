/**
 * @file basic.h
 * @brief API for creating a tree of basic nodes with string values.
 */
#ifndef SRPC_NODE_BASIC_H
#define SRPC_NODE_BASIC_H

#include <srpc/types.h>

/**
 * Create a new basic node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_basic_node_new(const char *name);

/**
 * Set node string value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 * @return Error code - 0 on success.
 */
int srpc_basic_node_set_value(srpc_node_t *node, const char *value);

/**
 * Get node value.
 *
 * @param node Node to use.
 *
 * @return Node value.
 */
const char *srpc_basic_node_get_value(const srpc_node_t *node);

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_basic_node_add_child(srpc_node_t *node, const char *name);

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_node_t *srpc_basic_node_get_child_by_value(const srpc_node_t *node, const char *name, const char *value);

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 *
 */
void srpc_basic_node_print(const srpc_node_t *node, FILE *file);

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_basic_node_free(srpc_node_t *node);

#endif // SRPC_NODE_BASIC_H