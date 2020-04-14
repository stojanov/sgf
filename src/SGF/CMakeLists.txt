cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES *.cpp)

set(CMAKE_BUILD_TYPE Debug)
 
add_library(sgf ${SOURCES})

if (MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

include_directories("./")
find_package(SFML 2.5.1 REQUIRED graphics network audio system)
target_link_libraries(sgf sfml-graphics)

install(TARGETS sgf
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
