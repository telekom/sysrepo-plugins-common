#include "srpc/change_tree.h"
#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#include <srpc.h>

static void test_change_tree_creation(void **state);
static void test_change_tree_children_correct(void **state);
static void test_change_tree_children_incorrect(void **state);

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_change_tree_creation),
        cmocka_unit_test(test_change_tree_children_correct),
        cmocka_unit_test(test_change_tree_children_incorrect),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

static void test_change_tree_creation(void **state)
{
    (void)state;

    srpc_change_node_t *node = NULL;

    // create node
    node = srpc_change_node_new("test");

    // assert set name
    assert_non_null(node);
    assert_string_equal(srpc_change_node_get_name(node), "test");

    // free the node
    srpc_change_node_free(node);
}

static void test_change_tree_children_correct(void **state)
{
    (void)state;

    srpc_change_node_t *node = NULL, *child = NULL;
    const srpc_change_node_t *found = NULL;
    char name_buffer[10] = {0};

    // create node
    node = srpc_change_node_new("test");

    for (int i = 0; i < 10; i++)
    {
        snprintf(name_buffer, sizeof(name_buffer), "child%02d", i);

        child = srpc_change_node_add_child(node, name_buffer);
        assert_non_null(child);
    }

    // assert all children are created
    assert_int_equal(srpc_change_node_get_children_count(node), 10);

    for (int i = 0; i < 10; i++)
    {
        snprintf(name_buffer, sizeof(name_buffer), "child%02d", i);

        // assert child get API
        found = srpc_change_node_get_child_by_name(node, name_buffer);

        assert_non_null(found);
        assert_string_equal(srpc_change_node_get_name(found), name_buffer);
    }

    // free the node
    srpc_change_node_free(node);
}

static void test_change_tree_children_incorrect(void **state)
{
    (void)state;
}