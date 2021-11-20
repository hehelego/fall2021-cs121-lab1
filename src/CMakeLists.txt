### SECTION compiling&linking options ###

set(NUM_THREADS 8 CACHE STRING "number of spawned threads")
set(BUILD_TYPE release CACHE STRING "release/debug mode")

message("[log] using ${NUM_THREADS} threads for OpenMP parallel bfs")
message("[log] build ${BUILD_TYPE} mode")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
	-Wall
	-Wextra
	-D NUM_THREADS=${NUM_THREADS}
)

if(${BUILD_TYPE} STREQUAL "debug")
	add_compile_definitions(DEBUG)
	add_compile_options(
		-g
		-fsanitize=undefined
		-fsanitize=address
		-fsanitize=leak
	)
	add_link_options(
		-g
		-fsanitize=undefined
		-fsanitize=address
		-fsanitize=leak
	)
else()
	add_compile_options(-O2)
endif()



### SECTION libraries ###


add_library(adjmat adjmat.cpp)
add_library(ds data_structure.cpp)
add_library(com common.cpp)
link_libraries(adjmat ds com)



### SECTION executables ###

add_executable(test test.cpp)
add_executable(snap_to_mm snap_to_mm.cpp)
add_executable(serial serial-bfs.cpp)
add_executable(parallel parallel-bfs.cpp)

# add OpenMP for parallel-bfs executable
find_package(OpenMP)
target_compile_options(parallel PRIVATE -fopenmp)
target_link_options(parallel PRIVATE -fopenmp)
