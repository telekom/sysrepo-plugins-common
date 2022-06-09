/**
 * @file node.h
 * @brief API for creating a tree instead of using lists, arrays etc.
 */
#ifndef SRPC_NODE_H
#define SRPC_NODE_H

#include "types.h"

/**
 * Macro for iterating node siblings.
 *
 * @param name Root/start node.
 * @param iter Iterator variable name.
 *
 */
#define SRPC_NODE_ITER(node, iter) for ((iter) = (node); (iter) != NULL; (iter) = srpc_node_get_next(iter))

/**
 * Macro for iterating node children.
 *
 * @param name Root/start node.
 * @param iter Iterator variable name.
 *
 */
#define SRPC_NODE_ITER_CHILDREN(node, iter)                                                                            \
    for ((iter) = srpc_node_get_child((node)); (iter) != NULL; (iter) = srpc_node_get_next(iter))

/**
 * Create a new node with the given name.
 *
 * @param name Name of the node.
 * @param alloc Callback used to allocate data.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_node_new(const char *name, srpc_node_data_alloc_cb alloc);

/**
 * Get name of the node.
 *
 * @param node Node to use.
 *
 * @return Node name.
 */
const char *srpc_node_get_name(const srpc_node_t *node);

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 * @param alloc Callback used to allocate data.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_node_add_child(srpc_node_t *node, const char *name, srpc_node_data_alloc_cb alloc);

/**
 * Set the next pointer for the given node.
 *
 * @param node Node to use.
 * @param next Next node.
 *
 */
void srpc_node_set_next(srpc_node_t *node, const srpc_node_t *next);

/**
 * Get the next node of the current node.
 *
 * @param node Node to use.
 *
 * @return Next node of the current node, NULL if one doesn't exist.
 */
const srpc_node_t *srpc_node_get_next(const srpc_node_t *node);

/**
 * Return first child of the provided node.
 *
 * @param node Node to use.
 *
 * @return First found child, NULL if one doesn't exist.
 */
const srpc_node_t *srpc_node_get_child(const srpc_node_t *node);

/**
 * Return child with the provided name.
 *
 * @param node Node to use.
 * @param name Child name.
 *
 * @return First found child with the provided name, NULL if not found.
 */
const srpc_node_t *srpc_node_get_child_by_name(const srpc_node_t *node, const char *name);

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child current value.
 * @param cmp Comparator function for two data pointers.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_node_t *srpc_node_get_child_by_value(const srpc_node_t *node, const char *name, const void *value,
                                                srpc_node_data_cmp_cb cmp);

/**
 * Return data pointer of the node.
 *
 * @param node Node to use.
 *
 * @return Allocated node data.
 */
void *srpc_node_get_data(const srpc_node_t *node);

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 * @param print Print callback for node data.
 *
 */
void srpc_node_print(const srpc_node_t *node, FILE *file, srpc_node_data_print_cb print);

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 * @param dealloc Callback to free data.
 *
 */
void srpc_node_free(srpc_node_t *node, srpc_node_data_dealloc_cb dealloc);

#endif // SRPC_NODE_H