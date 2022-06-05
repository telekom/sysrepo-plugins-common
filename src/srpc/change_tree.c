#include "change_tree.h"

#include <assert.h>

/**
 * Change tree node.
 */
struct srpc_change_node_s
{
    struct
    {
        const char *name; ///< Name of the libyang node.
        struct
        {
            char *previous;         ///< Previous value.
            char *current;          ///< Currently set value.
        } value;                    ///< Value of the node.
        sr_change_oper_t operation; ///< Operation for the current node.
    } data;
    srpc_change_node_t **children; ///< Children of the current node.
    size_t children_count;         ///< Number of children for the node.
};

/**
 * Create a new node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_change_node_t *srpc_change_node_new(const char *name)
{
    srpc_change_node_t *new_node = malloc(sizeof(srpc_change_node_t));

    if (!new_node)
    {
        return NULL;
    }

    // setup node to null values
    new_node->children_count = 0;
    new_node->children = NULL;

    // set values + operation
    new_node->data.operation = 0;
    new_node->data.value.current = NULL;
    new_node->data.value.previous = NULL;

    // set name
    new_node->data.name = strdup(name);
    if (!new_node->data.name)
    {
        free(new_node);
        return NULL;
    }

    return new_node;
}

/**
 * Get name of the node.
 *
 * @param node Node to use.
 *
 * @return Node name.
 */
const char *srpc_change_node_get_name(const srpc_change_node_t *node)
{
    return node->data.name;
}

/**
 * Set values pair for the node.
 *
 * @param node Node to use.
 * @param current_value Currently set value.
 * @param previous_value Previous node value.
 *
 * @return Error code - 0 on success.
 */
int srpc_change_node_set_value(srpc_change_node_t *node, const char *current_value, const char *previous_value)
{
    if (current_value)
    {
        node->data.value.current = strdup(current_value);
        if (node->data.value.current == NULL)
        {
            return -1;
        }
    }
    else
    {
        node->data.value.current = NULL;
    }

    if (previous_value)
    {
        node->data.value.previous = strdup(previous_value);
        if (node->data.value.previous == NULL)
        {
            return -2;
        }
    }
    else
    {
        node->data.value.previous = NULL;
    }

    return 0;
}

/**
 * Get current value of the node.
 *
 * @param node Node to use.
 *
 * @return Currently set value of the node.
 */
const char *srpc_change_node_get_current_value(const srpc_change_node_t *node)
{
    return node->data.value.current;
}

/**
 * Get previous value of the node.
 *
 * @param node Node to use.
 *
 * @return Previous set value of the node.
 */
const char *srpc_change_node_get_previous_value(const srpc_change_node_t *node)
{
    return node->data.value.previous;
}

/**
 * Set node operation to apply.
 *
 * @param node Node to use.
 * @param operation Applied operation on the node.
 *
 */
void srpc_change_node_set_operation(srpc_change_node_t *node, sr_change_oper_t operation)
{
    node->data.operation = operation;
}

/**
 * Get node operation.
 *
 * @param node Node to use.
 *
 * @return Operation on the node.
 */
sr_change_oper_t srpc_change_node_get_operation(const srpc_change_node_t *node)
{
    return node->data.operation;
}

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_change_node_t *srpc_change_node_add_child(srpc_change_node_t *node, const char *name)
{
    srpc_change_node_t *new_child = NULL, **new_children = NULL;

    new_child = srpc_change_node_new(name);
    if (!new_child)
    {
        return NULL;
    }

    new_children = realloc(node->children, sizeof(srpc_change_node_t *) * (node->children_count + 1));
    if (!new_children)
    {
        // invalid realloc
        return NULL;
    }

    // add new child to the list
    node->children = new_children;
    node->children[node->children_count] = new_child;
    node->children_count++;

    return new_child;
}

/**
 * Return number of children a node has.
 *
 * @param node Node to use.
 *
 * @return Number of children a node has.
 */
size_t srpc_change_node_get_children_count(const srpc_change_node_t *node)
{
    return node->children_count;
}

/**
 * Return n'th child.
 *
 * @param node Node to use.
 * @param n Child index number.
 *
 * @return Child at n'th position.
 */
const srpc_change_node_t *srpc_change_node_get_child(const srpc_change_node_t *node, const size_t n)
{
    // index has to be passed from the loop which iterates over indexes
    assert(n < node->children_count);
    return node->children[n];
}

/**
 * Return child with the provided name.
 *
 * @param node Node to use.
 * @param name Child name.
 *
 * @return First found child with the provided name, NULL if not found.
 */
const srpc_change_node_t *srpc_change_node_get_child_by_name(const srpc_change_node_t *node, const char *name)
{
    for (size_t i = 0; i < node->children_count; i++)
    {
        const srpc_change_node_t *ch = node->children[i];
        if (!strcmp(ch->data.name, name))
        {
            return ch;
        }
    }
    return NULL;
}

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child current value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_change_node_t *srpc_change_node_get_child_by_current_value(const srpc_change_node_t *node, const char *name,
                                                                      const char *value)
{
    for (size_t i = 0; i < node->children_count; i++)
    {
        const srpc_change_node_t *ch = node->children[i];
        if (!strcmp(ch->data.name, name) && !strcmp(ch->data.value.current, value))
        {
            return ch;
        }
    }
    return NULL;
}

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child previous value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_change_node_t *srpc_change_node_get_child_by_previous_value(const srpc_change_node_t *node, const char *name,
                                                                       const char *value)
{
    for (size_t i = 0; i < node->children_count; i++)
    {
        const srpc_change_node_t *ch = node->children[i];
        if (!strcmp(ch->data.name, name) && !strcmp(ch->data.value.previous, value))
        {
            return ch;
        }
    }
    return NULL;
}

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_change_node_free(srpc_change_node_t *node)
{
    // free recursively
    if (!node)
    {
        return;
    }

    for (size_t i = 0; i < node->children_count; i++)
    {
        srpc_change_node_free(node->children[i]);
    }

    // free children pointer
    free(node->children);

    // free name and values
    free((void *)node->data.name);

    if (node->data.value.current)
    {
        free(node->data.value.current);
    }
    if (node->data.value.previous)
    {
        free(node->data.value.previous);
    }

    // free node allocated pointer
    free(node);
}