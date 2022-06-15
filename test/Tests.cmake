add_executable(
	test_ly_tree

	test/test_ly_tree.c
)

target_link_libraries(
	test_ly_tree

	${CMOCKA_LIBRARIES}
	${SYSREPO_LIBRARIES}
	${LIBYANG_LIBRARIES}
	${CMAKE_PROJECT_NAME}
)

add_test(NAME test_ly_tree COMMAND test_ly_tree)