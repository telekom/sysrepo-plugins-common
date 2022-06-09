#include "basic.h"
#include <srpc/node.h>

typedef struct srpc_basic_data_s srpc_basic_data_t;

/**
 * Data to be allocated with the basic node.
 */
struct srpc_basic_data_s
{
    const char *value; ///< String value of the node.
};

void *srpc_basic_node_data_alloc();
int srpc_basic_node_data_value_cmp(const void *n1, const void *n2);
void srpc_basic_node_data_print(const char *node_name, const void *data, FILE *file);
void srpc_basic_node_data_dealloc(void **data);

/**
 * Create a new basic node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_basic_node_new(const char *name)
{
    return srpc_node_new(name, srpc_basic_node_data_alloc);
}

/**
 * Set node string value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 * @return Error code - 0 on success.
 */
int srpc_basic_node_set_value(srpc_node_t *node, const char *value)
{
    srpc_basic_data_t *data = srpc_node_get_data(node);

    if (value)
    {
        data->value = strdup(value);
        if (!data->value)
        {
            return -1;
        }
    }
    else
    {
        data->value = NULL;
    }

    return 0;
}

/**
 * Get node value.
 *
 * @param node Node to use.
 *
 * @return Node value.
 */
const char *srpc_basic_node_get_value(const srpc_node_t *node)
{
    const srpc_basic_data_t *data = srpc_node_get_data(node);
    return data->value;
}

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_basic_node_add_child(srpc_node_t *node, const char *name)
{
    return srpc_node_add_child(node, name, srpc_basic_node_data_alloc);
}

/**
 * Return child with the provided name and value.
 *
 * @param node Node to use.
 * @param name Child name.
 * @param value Child value.
 *
 * @return First found child with the provided name and value, NULL if not found.
 */
const srpc_node_t *srpc_basic_node_get_child_by_value(const srpc_node_t *node, const char *name, const char *value)
{
    srpc_basic_data_t data = {
        .value = value,
    };

    return srpc_node_get_child_by_value(node, name, &data, srpc_basic_node_data_value_cmp);
}

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 *
 */
void srpc_basic_node_print(const srpc_node_t *node, FILE *file)
{
    srpc_node_print(node, file, srpc_basic_node_data_print);
}

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_basic_node_free(srpc_node_t *node)
{
    srpc_node_free(node, srpc_basic_node_data_dealloc);
}

void *srpc_basic_node_data_alloc()
{
    srpc_basic_data_t *data = malloc(sizeof(srpc_basic_data_t));
    if (!data)
    {
        return NULL;
    }

    // initialize memory to NULL
    *data = (srpc_basic_data_t){0};

    return data;
}

int srpc_basic_node_data_value_cmp(const void *n1, const void *n2)
{
    const srpc_basic_data_t *d1 = n1;
    const srpc_basic_data_t *d2 = n2;

    return strcmp(d1->value, d2->value);
}

void srpc_basic_node_data_print(const char *node_name, const void *data, FILE *file)
{
    const srpc_basic_data_t *d2 = data;

    fprintf(file, "%s = %s", node_name, d2->value);
}

void srpc_basic_node_data_dealloc(void **data)
{
    srpc_basic_data_t *basic_data = *data;

    if (basic_data->value)
    {
        free((void *)basic_data->value);
    }

    free(basic_data);
    *data = NULL;
}
