set(SOURCES lib/cpu.cc)

add_library(nemuseng SHARED ${SOURCES})

target_include_directories(nemuseng PUBLIC ${PROJECT_INC_DIR})
target_link_libraries(nemuseng fmt::fmt)
