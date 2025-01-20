enable_testing()

SET(UNIT_TEST_SOURCES unit/try.cc unit/insns/asl.cc)
add_executable(
  unittests
  ${UNIT_TEST_SOURCES}
)

target_link_libraries(
  unittests
  GTest::gtest_main
  fmt::fmt
  nemuseng
)

target_include_directories(
	unittests PRIVATE ${PROJECT_INC_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GoogleTest)
gtest_discover_tests(unittests)
