project(nemus)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(NEMUS_ENABLE_TESTS "Build tests for nemus" OFF)

add_executable(nemus src/main.cc)

set(PROJECT_INC_DIR "${CMAKE_SOURCE_DIR}/src/include")

add_subdirectory(src)
target_include_directories(nemus PUBLIC ${PROJECT_INC_DIR})
target_link_libraries(nemus PUBLIC nemuseng fmt::fmt)

include(FetchContent)

message(STATUS "Downloading fmt library.")
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281
) # 10.2.1
FetchContent_MakeAvailable(fmt)

if (NEMUS_ENABLE_TESTS)
message(STATUS "Testing enabled! Downloading GTest.")

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG b514bdc898e2951020cbdca1304b75f5950d1f59
) # 1.52.2
FetchContent_MakeAvailable(googletest)

add_subdirectory(test)
endif()

