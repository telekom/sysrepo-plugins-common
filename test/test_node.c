#include "srpc/node.h"
#include "srpc/node/basic.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <srpc.h>

static void test_basic_node_new(void **state);
static void test_basic_node_find(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_basic_node_new),
        cmocka_unit_test(test_basic_node_find),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

static void test_basic_node_new(void **state)
{
    (void)state;
    int rc = 0;
    srpc_node_t *root = NULL;
    srpc_node_t *child = NULL;
    const srpc_node_t *iter = NULL;
    char name_buffer[15] = {0};

    root = srpc_basic_node_new("servers");

    for (int i = 0; i < 10; i++)
    {
        snprintf(name_buffer, sizeof(name_buffer), "server%d", i);
        child = srpc_basic_node_add_child(root, name_buffer);

        rc = srpc_basic_node_set_value(child, "127.0.0.1");

        assert_int_equal(rc, 0);

        // make sure the child is added
        assert_non_null(child);
    }

    // test all children created
    int count = 0;
    SRPC_NODE_ITER_CHILDREN(root, iter)
    {
        ++count;
    }
    assert_int_equal(count, 10);

    // free memory
    srpc_basic_node_free(root);
}

static void test_basic_node_find(void **state)
{
    (void)state;
    int rc = 0;
    srpc_node_t *root = NULL;
    srpc_node_t *child = NULL;
    const srpc_node_t *found = NULL;
    char name_buffer[15] = {0};
    char value_buffer[100] = {0};

    root = srpc_basic_node_new("servers");

    for (int i = 0; i < 10; i++)
    {
        snprintf(name_buffer, sizeof(name_buffer), "server");
        snprintf(value_buffer, sizeof(value_buffer), "127.0.0.%d", i + 1);

        child = srpc_basic_node_add_child(root, name_buffer);
        assert_non_null(child);

        rc = srpc_basic_node_set_value(child, value_buffer);
        assert_int_equal(rc, 0);
    }

    // test find by name
    found = srpc_node_get_child_by_name(root, "server");
    assert_non_null(found);
    assert_string_equal(srpc_node_get_name(found), "server");

    // first found should be 127.0.0.1
    assert_string_equal(srpc_basic_node_get_value(found), "127.0.0.1");

    // test find by value
    found = srpc_basic_node_get_child_by_value(root, "server", "127.0.0.1");
    assert_non_null(found);
    assert_string_equal(srpc_node_get_name(found), "server");
    assert_string_equal(srpc_basic_node_get_value(found), "127.0.0.1");

    // test unknown name
    found = srpc_node_get_child_by_name(root, "server-list-element");
    assert_null(found);

    // free memory
    srpc_basic_node_free(root);
}