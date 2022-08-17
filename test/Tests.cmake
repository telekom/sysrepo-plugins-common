# ly_tree
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

# feature_status
add_executable(
	test_feature_status

	test/test_feature_status.c
)

target_link_libraries(
	test_feature_status

	${CMOCKA_LIBRARIES}
	${SYSREPO_LIBRARIES}
	${LIBYANG_LIBRARIES}
	${CMAKE_PROJECT_NAME}
)

add_test(NAME test_feature_status COMMAND test_feature_status)