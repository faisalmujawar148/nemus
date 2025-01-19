enable_testing()

SET(UNIT_TEST_SOURCES unit/try.cc)
add_executable(
  unittests
  ${UNIT_TEST_SOURCES}
)

target_link_libraries(
  unittests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittests)
