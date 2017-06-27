cmake_minimum_required(VERSION 3.7)
project(CCourseWork)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c gameBorad.c gameBorad.h inputReadHandlers.c inputReadHandlers.h linkedListHelper.c linkedListHelper.h)
add_executable(CCourseWork ${SOURCE_FILES})
target_link_libraries(CCourseWork m)