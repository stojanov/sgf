cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(app ${SOURCES})

if (MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src/SGF)
target_link_libraries(app sgf)

install(TARGETS app RUNTIME DESTINATION bin)