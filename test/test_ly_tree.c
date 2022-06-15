#include "srpc/node.h"
#include "srpc/node/any.h"
#include "srpc/node/basic.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <srpc.h>

static void test_ly_tree(void **state);

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ly_tree),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

static void test_ly_tree(void **state)
{
    (void)state;
}