project(nemus)
set(TARGET nemus PROPERTY CXX_STANDARD 23)

add_executable(nemus src/main.cc)

set(PROJECT_INC_DIR "${CMAKE_SOURCE_DIR}/src/include")

add_subdirectory(src)
add_subdirectory(test)

target_include_directories(nemus PUBLIC ${PROJECT_INC_DIR})
target_link_libraries(nemus PUBLIC nemuseng)


