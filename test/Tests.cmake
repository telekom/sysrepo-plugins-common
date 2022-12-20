#
# Copyright (c) 2022 Deutsche Telekom AG.
#
# This source code is licensed under BSD 3-Clause License (the "License").
# You may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
# SPDX-FileContributor: Sartura Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#

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