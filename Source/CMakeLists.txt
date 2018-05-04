#Specify the version being used as well as the language
#cmake_minimum_required(VERSION 2.8)

#project name
#project(Thread_with_SharedObject)

#Add include director in  include_dir variable
#set(c_toolchain_path /usr/bin/gcc-4.8 CACHE INTERNAL "")
#set(cxx_toolchain_path /usr/bin/g++-4.8 CACHE INTERNAL "")
#set(cxx_flags "--std=c++11" CACHE INTERNAL "")

#set(CMAKE_C_COMPILER ${c_toolchain_path})
#set(CMAKE_CXX_COMPILER ${cxx_toolchain_path})
#set(CMAKE_CXX_FLAGS ${cxx_flags})

#Add main
#file(GLOB app_src "main_app/*.cpp")

#Add include director in  include_dir variable
#set(include_dir ${PROJECT_SOURCE_DIR}/main_app CACHE INTERNAL "")

#Add modules 
#add_subdirectory(Shared_Object)
#add_subdirectory(Shared_Object)

#Add include director 
#include_directories(${include_dir})

#add_executable(test_app ${app_src})
#target_link_libraries (test_app SharedObject)

