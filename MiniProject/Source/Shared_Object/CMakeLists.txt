#Add include files 
include_directories(include)

#set compilaer option 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11")

#set source files 
FILE(GLOB Shared_Object_SRC src/*.cpp)

#add include directory for main application 
set(include_dir ${include_dir} ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")

#create static .a  
add_library(Shared_Object STATIC ${Shared_Object_SRC})
install(TARGETS Shared_Object DESTINATION ${CMAKE_BINARY_DIR}/lib)
