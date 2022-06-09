#include "change.h"
#include <srpc/node.h>

typedef struct srpc_change_data_s srpc_change_data_t;

/**
 * Data to be allocated with the change node.
 */
struct srpc_change_data_s
{
    struct srpc_change_value
    {
        const char *current;  ///< Current node value - the one being set.
        const char *previous; ///< Previously set node value.
    } value;
    sr_change_oper_t operation; ///< Operation being applied on the given node.
};

void *srpc_change_node_data_alloc();
int srpc_change_node_data_current_value_cmp(const void *n1, const void *n2);
int srpc_change_node_data_previous_value_cmp(const void *n1, const void *n2);
void srpc_change_node_data_print(const char *node_name, const void *data, FILE *file);
void srpc_change_node_data_dealloc(void **data);

/**
 * Create a new node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_change_node_new(const char *name)
{
    return srpc_node_new(name, srpc_change_node_data_alloc);
}

/**
 * Set node operation.
 *
 * @param node Node to use.
 * @param operation Operation for the given node.
 *
 */
void srpc_change_node_set_operation(srpc_node_t *node, sr_change_oper_t operation)
{
    srpc_change_data_t *data = srpc_node_get_data(node);
    data->operation = operation;
}

/**
 * Get node operation.
 *
 * @param node Node to use.
 *
 * @return Operation of the node.
 */
sr_change_oper_t srpc_change_node_get_operation(const srpc_node_t *node)
{
    const srpc_change_data_t *data = srpc_node_get_data(node);
    return data->operation;
}

/**
 * Set change values - current and previous value.
 *
 * @param node Node to use.
 * @param current_value Current node value.
 * @param previous_value Previous node value.
 *
 * @return Error code - 0 on success.
 */
int srpc_change_node_set_value(srpc_node_t *node, const char *current_value, const char *previous_value)
{
    srpc_change_data_t *data = srpc_node_get_data(node);

    if (current_value)
    {
        data->value.current = strdup(current_value);
        if (data->value.current == NULL)
        {
            return -1;
        }
    }
    else
    {
        data->value.current = NULL;
    }

    if (previous_value)
    {
        data->value.previous = strdup(previous_value);
        if (data->value.previous == NULL)
        {
            return -2;
        }
    }
    else
    {
        data->value.previous = NULL;
    }

    return 0;
}

/**
 * Get current node value.
 *
 * @param node Node to use.
 *
 * @return Current node value.
 */
const char *srpc_change_node_get_current_value(const srpc_node_t *node)
{
    const srpc_change_data_t *data = srpc_node_get_data(node);
    return data->value.current;
}

/**
 * Get previous node value.
 *
 * @param node Node to use.
 *
 * @return Previous node value.
 */
const char *srpc_change_node_get_previous_value(const srpc_node_t *node)
{
    const srpc_change_data_t *data = srpc_node_get_data(node);
    return data->value.previous;
}

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_change_node_add_child(srpc_node_t *node, const char *name)
{
    return srpc_node_add_child(node, name, srpc_change_node_data_alloc);
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
const srpc_node_t *srpc_change_node_get_child_by_current_value(const srpc_node_t *node, const char *name,
                                                               const char *value)
{
    srpc_change_data_t data = {
        .value =
            {
                .current = value,
            },
    };

    return srpc_node_get_child_by_value(node, name, &data, srpc_change_node_data_current_value_cmp);
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
const srpc_node_t *srpc_change_node_get_child_by_previous_value(const srpc_node_t *node, const char *name,
                                                                const char *value)
{
    srpc_change_data_t data = {
        .value =
            {
                .previous = value,
            },
    };

    return srpc_node_get_child_by_value(node, name, &data, srpc_change_node_data_previous_value_cmp);
}

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 *
 */
void srpc_change_node_print(const srpc_node_t *node, FILE *file)
{
    srpc_node_print(node, file, srpc_change_node_data_print);
}

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_change_node_free(srpc_node_t *node)
{
    srpc_node_free(node, srpc_change_node_data_dealloc);
}

void *srpc_change_node_data_alloc()
{
    srpc_change_data_t *data = malloc(sizeof(srpc_change_data_t));
    if (!data)
    {
        return NULL;
    }

    // initialize memory to NULL
    *data = (srpc_change_data_t){0};

    return data;
}

int srpc_change_node_data_current_value_cmp(const void *n1, const void *n2)
{
    const srpc_change_data_t *d1 = n1;
    const srpc_change_data_t *d2 = n2;

    return strcmp(d1->value.current, d2->value.current);
}

int srpc_change_node_data_previous_value_cmp(const void *n1, const void *n2)
{
    const srpc_change_data_t *d1 = n1;
    const srpc_change_data_t *d2 = n2;

    return strcmp(d1->value.previous, d2->value.previous);
}

void srpc_change_node_data_print(const char *node_name, const void *data, FILE *file)
{
    const srpc_change_data_t *change_data = data;

    fprintf(file, "%s {operation: %d, value.current: %s, value.previous: %s}", node_name, change_data->operation,
            change_data->value.current, change_data->value.previous);
}

void srpc_change_node_data_dealloc(void **data)
{
    srpc_change_data_t *change_data = *data;

    if (change_data->value.current)
    {
        free((void *)change_data->value.current);
    }

    if (change_data->value.previous)
    {
        free((void *)change_data->value.previous);
    }

    free(change_data);
    *data = NULL;
}
