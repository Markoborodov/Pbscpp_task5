cmake_minimum_required(VERSION 3.10)
project(Pbscpp_task5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

add_executable(exercise_1 exercise_1.cpp)
add_executable(exercise_2 exercise_2.cpp)
add_executable(exercise_3 exercise_3.cpp)
target_link_libraries(exercise_3 gtest pthread)
