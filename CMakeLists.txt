cmake_minimum_required(VERSION 3.15)
project(tiny-c VERSION 0.1.0 LANGUAGES C)

add_compile_options("-std=c11" "-Wall" "-pedantic")

add_executable(greetings src/greetings.c)
add_executable(local_greet src/local_greet.c)
add_executable(time src/time.c)
add_executable(moon_phase src/moon_phase.c)
add_executable(pithy src/pithy.c)

# This project can use C11, but will gracefully decay down to C89.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_definitions(-std=c_std_11)

target_compile_features(pithy PRIVATE c_std_11)