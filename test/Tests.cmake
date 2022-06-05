add_executable(
	test_change_tree

    test/test_change_tree.c
)

target_link_libraries(
    test_change_tree

	${CMOCKA_LIBRARIES}
	${SYSREPO_LIBRARIES}
	${LIBYANG_LIBRARIES}
	${CMAKE_PROJECT_NAME}
)

add_test(NAME test_change_tree COMMAND test_change_tree)