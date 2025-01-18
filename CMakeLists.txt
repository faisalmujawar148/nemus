project(nemus)
set(TARGET nemus PROPERTY CXX_STANDARD 23)

add_executable(nemus src/main.cc)

set(PROJECT_INC_DIR "${CMAKE_SOURCE_DIR}/src/include")

add_subdirectory(src)
add_subdirectory(test)

target_include_directories(nemus PUBLIC ${PROJECT_INC_DIR})
target_link_libraries(nemus PUBLIC nemuseng fmt::fmt)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)
