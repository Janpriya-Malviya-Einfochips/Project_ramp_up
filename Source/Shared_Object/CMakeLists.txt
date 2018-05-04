#Shared object 

#Add include director current lib
#include_directories(include)

#Add soruce files for compilation
#FILE(GLOB Shared_object_src src/*.cpp)

#Set compilation flags
#message("c_toolchain_path -> ${c_toolchain_path}")
#message("cxx_toolchain_path -> ${cxx_toolchain_path}")
#message("cxx_flags -> ${cxx_flags}")
#set(CMAKE_C_COMPILER ${c_toolchain_path})
#set(CMAKE_CXX_COMPILER ${cxx_toolchain_path})
#set(CMAKE_CXX_FLAGS ${cxx_flags})

#set(include_dir ${include_dir} ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL  "")

#add_library(Shared_object STATIC ${Shared_object_src})
#install(TARGETS Shared_object DESTINATION ${CMAKE_BINARY_DIR}/lib)
