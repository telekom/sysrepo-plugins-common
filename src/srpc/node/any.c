#include "any.h"

#include <srpc/node.h>
#include <assert.h>

typedef struct srpc_any_data_s srpc_any_data_t;
typedef union srpc_any_data_value_u srpc_any_data_value_t;
typedef struct srpc_any_data_memory_s srpc_any_data_memory_t;

/**
 * Memory type of the node - contains memory pointer and size in bytes.
 */
struct srpc_any_data_memory_s
{
    void *memory; ///< Allocated memory.
    size_t bytes; ///< Size of the allocated memory.
};

/**
 * All possible values of the node.
 */
union srpc_any_data_value_u {
    int8_t s8;
    uint8_t u8;
    int16_t s16;
    uint16_t u16;
    int32_t s32;
    uint32_t u32;
    int64_t s64;
    uint64_t u64;
    float f;
    double d;
    const char *str;
    srpc_any_data_memory_t mem;
};

/**
 * Data to be allocated with the basic node.
 */
struct srpc_any_data_s
{
    srpc_any_node_kind_t kind;   ///< Type of the node.
    srpc_any_data_value_t value; ///< Value of the node.
};

void *srpc_any_node_data_alloc();
int srpc_any_node_data_value_cmp(const void *n1, const void *n2);
void srpc_any_node_data_print(const char *node_name, const void *data, FILE *file);
void srpc_any_node_data_dealloc(void **data);

/**
 * Create a new basic node with the given name.
 *
 * @param name Name of the node.
 *
 * @return New node - NULL when unable to create one.
 */
srpc_node_t *srpc_any_node_new(const char *name)
{
    return srpc_node_new(name, srpc_any_node_data_alloc);
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s8(srpc_node_t *node, int8_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_s8;
    data->value.s8 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u8(srpc_node_t *node, uint8_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_u8;
    data->value.u8 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s16(srpc_node_t *node, int16_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_s16;
    data->value.s16 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u16(srpc_node_t *node, uint16_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_u16;
    data->value.u16 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s32(srpc_node_t *node, int32_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_s32;
    data->value.s32 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u32(srpc_node_t *node, uint32_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_u32;
    data->value.u32 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_s64(srpc_node_t *node, int64_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_s64;
    data->value.s64 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_u64(srpc_node_t *node, uint64_t value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_u64;
    data->value.u64 = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_float(srpc_node_t *node, float value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_float;
    data->value.f = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 */
void srpc_any_node_set_value_double(srpc_node_t *node, double value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->kind = srpc_any_node_kind_double;
    data->value.d = value;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 *
 * @return Error code - 0 on success.
 */
int srpc_any_node_set_value_str(srpc_node_t *node, const char *value)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->value.str = strdup(value);

    if (!data->value.str)
    {
        return -1;
    }

    data->kind = srpc_any_node_kind_str;
    return 0;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param value Value to set.
 * @param bytes Number of bytes to copy.
 *
 * @return Error code - 0 on success.
 */
int srpc_any_node_set_value_mem(srpc_node_t *node, const void *value, const size_t bytes)
{
    srpc_any_data_t *data = srpc_node_get_data(node);
    data->value.mem.memory = malloc(bytes);

    if (!data->value.mem.memory)
    {
        return -1;
    }

    // copy data
    memcpy(data->value.mem.memory, value, bytes);

    data->kind = srpc_any_node_kind_mem;
    return 0;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int8_t srpc_any_node_get_value_s8(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_s8);
    return data->value.s8;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint8_t srpc_any_node_get_value_u8(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_u8);
    return data->value.u8;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int16_t srpc_any_node_get_value_s16(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_s16);
    return data->value.s16;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint16_t srpc_any_node_get_value_u16(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_u16);
    return data->value.u16;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int32_t srpc_any_node_get_value_s32(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_s32);
    return data->value.s32;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint32_t srpc_any_node_get_value_u32(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_u32);
    return data->value.u32;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
int64_t srpc_any_node_get_value_s64(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_s64);
    return data->value.s64;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
uint64_t srpc_any_node_get_value_u64(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_u64);
    return data->value.u64;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
float srpc_any_node_get_value_float(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_float);
    return data->value.f;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
double srpc_any_node_get_value_double(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_double);
    return data->value.d;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 *
 * @return Value of the node.
 */
const char *srpc_any_node_get_value_str(const srpc_node_t *node)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_str);
    return data->value.str;
}

/**
 * Set node value.
 *
 * @param node Node to use.
 * @param bytes Space to write number of bytes to.
 *
 * @return Value of the node.
 */
const void *srpc_any_node_get_value_mem(const srpc_node_t *node, size_t *bytes)
{
    const srpc_any_data_t *data = srpc_node_get_data(node);
    assert(data->kind == srpc_any_node_kind_mem);
    *bytes = data->value.mem.bytes;
    return data->value.mem.memory;
}

/**
 * Create a child and append it to the list of children for the given node.
 *
 * @param node Node to use.
 * @param name Child node name.
 *
 * @return New child node - NULL when unable to create one.
 */
srpc_node_t *srpc_any_node_add_child(srpc_node_t *node, const char *name)
{
    return srpc_node_add_child(node, name, srpc_any_node_data_alloc);
}

/**
 * Debug function to print tree contents to the provided file.
 *
 * @param node Node to use.
 * @param file File to print to.
 *
 */
void srpc_any_node_print(const srpc_node_t *node, FILE *file)
{
    srpc_node_print(node, file, srpc_any_node_data_print);
}

/**
 * Free the whole tree starting from the given node.
 *
 * @param node Node to free.
 *
 */
void srpc_any_node_free(srpc_node_t *node)
{
    srpc_node_free(node, srpc_any_node_data_dealloc);
}

void *srpc_any_node_data_alloc()
{
    srpc_any_data_t *data = malloc(sizeof(srpc_any_data_t));
    if (!data)
    {
        return NULL;
    }

    // initialize memory to NULL
    *data = (srpc_any_data_t){
        .kind = srpc_any_node_kind_none,
        .value = {0},
    };

    return data;
}

int srpc_any_node_data_value_cmp(const void *n1, const void *n2)
{
    const srpc_any_data_t *d1 = n1;
    const srpc_any_data_t *d2 = n2;
    uint8_t same = 0;

    switch (d1->kind)
    {
    case srpc_any_node_kind_none:
        return -2;
        break;
    case srpc_any_node_kind_s8:
        same = d1->value.s8 == d2->value.s8;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.s8 < d2->value.s8 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_u8:
        same = d1->value.u8 == d2->value.u8;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.u8 < d2->value.u8 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_s16:
        same = d1->value.s16 == d2->value.s16;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.s16 < d2->value.s16 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_u16:
        same = d1->value.u16 == d2->value.u16;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.u16 < d2->value.u16 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_s32:
        same = d1->value.s32 == d2->value.s32;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.s32 < d2->value.s32 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_u32:
        same = d1->value.u32 == d2->value.u32;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.u32 < d2->value.u32 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_s64:
        same = d1->value.s64 == d2->value.s64;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.s64 < d2->value.s64 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_u64:
        same = d1->value.u64 == d2->value.u64;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.u64 < d2->value.u64 ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_float:
        same = d1->value.f == d2->value.f;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.f < d2->value.f ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_double:
        same = d1->value.d == d2->value.d;
        if (same)
        {
            return 0;
        }
        else
        {
            return d1->value.d < d2->value.d ? -1 : 1;
        }
        break;
    case srpc_any_node_kind_str:
        if (d1->value.str != NULL && d2->value.str)
        {
            return strcmp(d1->value.str, d2->value.str);
        }
        else
        {
            return -2;
        }
        break;
    case srpc_any_node_kind_mem:
        // TODO: implement
        return -2;
        break;
    }
}

void srpc_any_node_data_print(const char *node_name, const void *data, FILE *file)
{
    const srpc_any_data_t *any_data = data;

    fprintf(file, "%s = ", node_name);

    switch (any_data->kind)
    {
    case srpc_any_node_kind_none:
        fprintf(file, "[NONE]");
        break;
    case srpc_any_node_kind_s8:
        fprintf(file, "%d", any_data->value.s8);
        break;
    case srpc_any_node_kind_u8:
        fprintf(file, "%u", any_data->value.u8);
        break;
    case srpc_any_node_kind_s16:
        fprintf(file, "%d", any_data->value.s16);
        break;
    case srpc_any_node_kind_u16:
        fprintf(file, "%u", any_data->value.u16);
        break;
    case srpc_any_node_kind_s32:
        fprintf(file, "%d", any_data->value.s32);
        break;
    case srpc_any_node_kind_u32:
        fprintf(file, "%u", any_data->value.u32);
        break;
    case srpc_any_node_kind_s64:
        fprintf(file, "%ld", any_data->value.s64);
        break;
    case srpc_any_node_kind_u64:
        fprintf(file, "%lu", any_data->value.u64);
        break;
    case srpc_any_node_kind_float:
        fprintf(file, "%f", any_data->value.f);
        break;
    case srpc_any_node_kind_double:
        fprintf(file, "%lf", any_data->value.d);
        break;
    case srpc_any_node_kind_str:
        fprintf(file, "\"%s\"", any_data->value.str);
        break;
    case srpc_any_node_kind_mem:
        fprintf(file, "%p", any_data->value.mem.memory);
        break;
    }
}

void srpc_any_node_data_dealloc(void **data)
{
    srpc_any_data_t *any_data = *data;

    if (any_data->kind == srpc_any_node_kind_str && any_data->value.str != NULL)
    {
        free((void *)any_data->value.str);
    }
    else if (any_data->kind == srpc_any_node_kind_mem && any_data->value.mem.memory != NULL)
    {
        free((void *)any_data->value.mem.memory);
    }

    free(any_data);
    *data = NULL;
}
