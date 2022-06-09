#include "node.h"

/**
 * SRPC node.
 */
struct srpc_node_s
{
    const char *name;   ///< Node name.
    srpc_node_t *child; ///< First child of the current node.
    srpc_node_t *next;  ///< Next sibling of the current node.
    void *data;         ///< Private data which the user can allocate and use.
};

/**
 * Debug function to print tree contents to the provided file - indented version.
 *
 * @param node Node to use.
 * @param file File to print to.
 * @param print Print callback for node data.
 * @param indent Indent of the node.
 *
 */
void srpc_node_print_indent(const srpc_node_t *node, FILE *file, srpc_node_data_print_cb print, int indent);

/**
 * Create a new node with the given name.
 *
 * @param name Name of the node.
 * @param alloc Callback used to allocate data.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_node_new(const char *name, srpc_node_data_alloc_cb alloc)
{
    srpc_node_t *new_node = malloc(sizeof(srpc_node_t));

    if (!new_node)
    {
        return NULL;
    }

    // setup node to null values
    new_node->next = NULL;
    new_node->child = NULL;

    // set name
    new_node->name = strdup(name);
    if (!new_node->name)
    {
        free(new_node);
        return NULL;
    }

    // set value
    new_node->data = alloc();
    if (!new_node->data)
    {
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
const char *srpc_node_get_name(const srpc_node_t *node)
{
    return node->name;
}

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 * @param alloc Callback used to allocate data.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_node_add_child(srpc_node_t *node, const char *name, srpc_node_data_alloc_cb alloc)
{
    srpc_node_t *new_child = NULL, *ch_iter = NULL, *prev = NULL;

    new_child = srpc_node_new(name, alloc);
    if (!new_child)
    {
        return NULL;
    }

    // setup child pointer
    prev = NULL;
    ch_iter = node->child;

    while (ch_iter)
    {
        prev = ch_iter;
        ch_iter = ch_iter->next;
    }

    if (!prev)
    {
        node->child = new_child;
    }
    else
    {
        prev->next = new_child;
    }

    return new_child;
}

/**
 * Set the next pointer for the given node.
 *
 * @param node Node to use.
 * @param next Next node.
 *
 */
void srpc_node_set_next(srpc_node_t *node, const srpc_node_t *next)
{
    node->next = (srpc_node_t *)next;
}

/**
 * Get the next node of the current node.
 *
 * @param node Node to use.
 *
 * @return Next node of the current node, NULL if one doesn't exist.
 */
const srpc_node_t *srpc_node_get_next(const srpc_node_t *node)
{
    return node->next;
}

/**
 * Return first child of the provided node.
 *
 * @param node Node to use.
 *
 * @return First found child, NULL if one doesn't exist.
 */
const srpc_node_t *srpc_node_get_child(const srpc_node_t *node)
{
    return node->child;
}

/**
 * Return child with the provided name.
 *
 * @param node Node to use.
 * @param name Child name.
 *
 * @return First found child with the provided name, NULL if not found.
 */
const srpc_node_t *srpc_node_get_child_by_name(const srpc_node_t *node, const char *name)
{
    const srpc_node_t *iter = NULL;

    SRPC_NODE_ITER_CHILDREN(node, iter)
    {
        if (!strcmp(iter->name, name))
        {
            return iter;
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
 * @param cmp Comparator function for two data pointers.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_node_t *srpc_node_get_child_by_value(const srpc_node_t *node, const char *name, const void *value,
                                                srpc_node_data_cmp_cb cmp)
{
    const srpc_node_t *iter = NULL;

    SRPC_NODE_ITER_CHILDREN(node, iter)
    {
        if (!strcmp(iter->name, name) && !cmp(value, iter->data))
        {
            return iter;
        }
    }

    return NULL;
}

/**
 * Return data pointer of the node.
 *
 * @param node Node to use.
 *
 * @return Allocated node data.
 */
void *srpc_node_get_data(const srpc_node_t *node)
{
    return node->data;
}

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 * @param print Print callback for node data.
 *
 */
void srpc_node_print(const srpc_node_t *node, FILE *file, srpc_node_data_print_cb print)
{
    srpc_node_print_indent(node, file, print, 0);
}

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 * @param dealloc Callback to free data.
 *
 */
void srpc_node_free(srpc_node_t *node, srpc_node_data_dealloc_cb dealloc)
{
    if (!node)
    {
        return;
    }

    // free children
    srpc_node_free(node->child, dealloc);

    // free next node
    srpc_node_free(node->next, dealloc);

    // free name
    free((void *)node->name);

    // free data
    dealloc(&node->data);

    // free node allocated pointer
    free(node);
}

void srpc_node_print_indent(const srpc_node_t *node, FILE *file, srpc_node_data_print_cb print, int indent)
{
    const srpc_node_t *iter = NULL;

    if (!node)
    {
        return;
    }

    // print indent
    for (int i = 0; i < indent; i++)
    {
        fprintf(file, "  ");
    }

    // print node info on one line
    print(node->name, node->data, file);

    // add newline
    fprintf(file, "\n");

    // print children info
    srpc_node_print_indent(node->child, file, print, indent + 1);

    // print next node
    srpc_node_print_indent(node->next, file, print, indent);
}