cmake_minimum_required(VERSION 3.10)
project(env-spy)

find_package(Curses REQUIRED)

set(SOURCES
    src/main.c
    src/windows.c
    src/filter.c
    src/env_logic.c
    src/pages.c
    src/log.c
)

add_executable(envspy.out ${SOURCES})
target_link_libraries(envspy.out PRIVATE ${CURSES_LIBRARIES})

# Enable DEBUG macro automatically for Debug builds
target_compile_definitions(envspy.out PRIVATE $<$<CONFIG:Debug>:DEBUG>)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Add convenient pseudo-targets for building Debug/Release
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -B ${CMAKE_BINARY_DIR} -S ${CMAKE_SOURCE_DIR} -DCMAKE_BUILD_TYPE=Debug
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
)

add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -B ${CMAKE_BINARY_DIR} -S ${CMAKE_SOURCE_DIR} -DCMAKE_BUILD_TYPE=Release
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
)

