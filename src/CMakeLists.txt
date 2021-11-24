### SECTION compiling&linking options ###
# set(CMAKE_C_COMPILER /usr/bin/clang)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(PROFILE       OFF       CACHE BOOL   "enable/disable profiling")
set(SANITIZE      OFF       CACHE BOOL   "enable/disable sanitizer")
set(NUM_THREADS   16        CACHE STRING "number of spawned threads")
set(NUM_ROUNDS    20        CACHE STRING "number of bfs on one graph")
set(NUM_SEED      19260817  CACHE STRING "seed for random number generator")

message("[log] build ${CMAKE_BUILD_TYPE} mode")
message("[log] profiling ${PROFILE}")
message("[log] using ${NUM_THREADS} threads for OpenMP parallel bfs")
message("[log] run ${NUM_ROUNDS} bfs on one graph")
message("[log] the seed for RNG is ${NUM_SEED}")

add_compile_definitions(
	NUM_THREADS=${NUM_THREADS}
	NUM_ROUNDS=${NUM_ROUNDS}
	NUM_SEED=${NUM_SEED}
)
add_compile_options(
	-Wall
	-Wextra
)

if(${PROFILE})
	add_compile_options(
		-lprofiler
		-fno-omit-frame-pointer
	)
	add_link_options(
		-lprofiler
	)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_compile_definitions(DEBUG)
	add_compile_options(
		-O0
		-g
	)
	add_link_options(
		-g
	)
	if(${SANITIZE})
		message("[log] sanitizer enabled")
		add_compile_options(
			-fsanitize=undefined
			-fsanitize=address
			-fsanitize=leak
		)
		add_link_options(
			-fsanitize=undefined
			-fsanitize=address
			-fsanitize=leak
		)
	endif()
else()
	add_compile_options(-O3)
endif()



### SECTION libraries ###

find_package(OpenMP)
add_compile_options(-fopenmp)
add_link_options(-fopenmp)

add_library(adj adjmat.cpp)
add_library(bs bitset.cpp)
add_library(com common.cpp)
link_libraries(adj bs com)


### SECTION executables ###

add_executable(test test.cpp)
add_executable(snap_to_mm snap_to_mm.cpp)
add_executable(serial serial-bfs.cpp)
add_executable(parallel parallel-bfs.cpp)

