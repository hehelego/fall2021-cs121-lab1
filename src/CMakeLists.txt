### SECTION compiling&linking options ###

option(NUM_THREADS "number of spawned thread for OpenMP" 8)
option(BUILD_TYPE "build type, release or debug" release)

add_compile_definitions(NUM_THREADS=${NUM_THREADS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
	-Wall
	-Wextra
)

if(${BUILD_TYPE} STREQUAL "debug")
	add_compile_definitions(DEBUG)
	add_compile_options(
		-g
		-fsanitize=undefined
	)
	add_link_options(
		-g
		-lubsan
	)
else()
	add_compile_options(-O2)
endif()



### SECTION libraries ###

option(INLINE_LIBRARY "disable static library linking to allow inline memeber function" ON)

if(INLINE_LIBRARY)
	set(inline_lib adjmat.cpp adjmat.hpp data_structure.cpp data_structure.hpp common.cpp common.hpp)
	# to use inline functions, we have to get rid of static/dynamic linking
	# https://stackoverflow.com/questions/53114164/inlining-class-methods-inside-a-static-library
else()
	set(inline_lib)
	add_library(adjmat adjmat.cpp)
	add_library(ds data_structure.cpp)
	add_library(com common.cpp)
	link_libraries(adjmat ds com)
endif()



### SECTION executables ###

add_executable(test test.cpp ${inline_lib})
add_executable(snap_to_mm snap_to_mm.cpp ${inline_lib})
add_executable(serial serial-bfs.cpp ${inline_lib})
add_executable(parallel parallel-bfs.cpp ${inline_lib})

# add OpenMP for parallel-bfs executable
find_package(OpenMP)
target_compile_options(parallel PRIVATE -fopenmp)
target_link_options(parallel PRIVATE -fopenmp)
