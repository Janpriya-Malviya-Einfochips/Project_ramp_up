#Specify the version being used as well as the language
cmake_minimum_required(VERSION 2.8)

#project name
project(ThreadSync_with_SharedObject)

#Set complier setting
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_C_COMPILER /usr/bin/gcc-4.8 CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/g++-4.8 CACHE PATH "" FORCE)

#include direcotry 
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

#Set sub modules setting
add_subdirectory(Shared_Object)
add_subdirectory(worker)

find_package (Shared_Object)
find_package (Worker_Object)

#Set main application
file(GLOB app_src "main_app/*.cpp")

#Set external package
find_package (Threads)

#Create Main binary 
add_executable(ramp_up_test_app ${app_src})
include_directories(${include_dir})
target_link_libraries (ramp_up_test_app Shared_Object)
target_link_libraries (ramp_up_test_app Worker_Object)
target_link_libraries (ramp_up_test_app pthread)

#Create Unit test
find_package (UnitTest++ REQUIRED)
file(GLOB unit_test_app_src "../UnitTest/*.cpp")
include_directories(${UTPP_INCLUDE_DIRS})
add_executable(unit_test_app ${unit_test_app_src})
target_link_libraries (unit_test_app UnitTest++)
target_link_libraries (unit_test_app Shared_Object)
target_link_libraries (unit_test_app Worker_Object)
target_link_libraries (unit_test_app pthread)
