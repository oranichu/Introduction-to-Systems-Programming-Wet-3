cmake_minimum_required(VERSION 3.5)
project(mtm3Full C)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")
set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c grade.c grade.h course.c course.h
        semester.c semester.h student.c student.h courseManager.c courseManager.h)

link_directories(.)
add_executable(mtm3Full main.c grade.c grade.h course.c course.h
        semester.c semester.h student.c student.h course_manager.c course_manager.h)
target_link_libraries(mtm3Full libmtm.a)