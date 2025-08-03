cmake_minimum_required(VERSION 3.10)
project(env-spy)

find_package(Curses REQUIRED)

add_executable(envspy.out 
		src/main.c
		src/windows.c
		src/filter.c
		src/env_logic.c
)

target_link_libraries(envspy.out PRIVATE ${CURSES_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
