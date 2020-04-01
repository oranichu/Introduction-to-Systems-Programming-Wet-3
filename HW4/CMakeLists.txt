cmake_minimum_required(VERSION 3.5)
project(World)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors ")

set(CMAKE_CXX_STANDARD 11)

add_executable(World  main.cpp Group.h Group.cpp Clan.h Clan.cpp MtmSet.h
        exceptions.h Area.h testMacros.h Area.cpp Plain.cpp Plain.h
        Mountain.cpp Mountain.h River.cpp River.h World.cpp)