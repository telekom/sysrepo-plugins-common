/**
 * @file any.h
 * @brief API for creating a tree of nodes with any (int, string, float) values.
 */
#ifndef SRPC_NODE_ANY_H
#define SRPC_NODE_ANY_H

#include <srpc/types.h>

/**
 * Create a new basic node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_any_node_new(const char *name);

/**
 * Get node type.
 *
 * @param node Node to use.
 *
 * @return Current node type.
 */
srpc_any_node_kind_t srpc_any_node_get_kind(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s8(srpc_node_t *node, int8_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u8(srpc_node_t *node, uint8_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s16(srpc_node_t *node, int16_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u16(srpc_node_t *node, uint16_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s32(srpc_node_t *node, int32_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u32(srpc_node_t *node, uint32_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s64(srpc_node_t *node, int64_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u64(srpc_node_t *node, uint64_t value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_float(srpc_node_t *node, float value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_double(srpc_node_t *node, double value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 * @return Error code - 0 on success.
 */
int srpc_any_node_set_value_str(srpc_node_t *node, const char *value);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 * @param bytes Number of bytes to copy.
 *
 * @return Error code - 0 on success.
 */
int srpc_any_node_set_value_mem(srpc_node_t *node, const void *value, const size_t bytes);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int8_t srpc_any_node_get_value_s8(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint8_t srpc_any_node_get_value_u8(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int16_t srpc_any_node_get_value_s16(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint16_t srpc_any_node_get_value_u16(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int32_t srpc_any_node_get_value_s32(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint32_t srpc_any_node_get_value_u32(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int64_t srpc_any_node_get_value_s64(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint64_t srpc_any_node_get_value_u64(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
float srpc_any_node_get_value_float(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
double srpc_any_node_get_value_double(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
const char *srpc_any_node_get_value_str(const srpc_node_t *node);

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param bytes Space to write number of bytes to.
 *
 * @return Value of the node.
 */
const void *srpc_any_node_get_value_mem(const srpc_node_t *node, size_t *bytes);

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_any_node_add_child(srpc_node_t *node, const char *name);

/**
 * Remove provided child from the node children list while iterating children.
 *
 * @param node Node to use.
 * @param child Child pointer to remove.
 * @param iter Iterator being used. Can be set to NULL if not needed.
 *
 */
void srpc_any_node_remove_child(srpc_node_t *node, srpc_node_t *child, srpc_node_t **iter);

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 *
 */
void srpc_any_node_print(const srpc_node_t *node, FILE *file);

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_any_node_free(srpc_node_t *node);

#endif // SRPC_NODE_ANY_H