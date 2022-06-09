add_executable(
	test_node

    test/test_node.c
)

target_link_libraries(
    test_node

	${CMOCKA_LIBRARIES}
	${SYSREPO_LIBRARIES}
	${LIBYANG_LIBRARIES}
	${CMAKE_PROJECT_NAME}
)

add_test(NAME test_node COMMAND test_node)