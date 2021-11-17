### SECTION compiling&linking options ###

add_compile_options(
	-Wall
	-Wextra
	-O2
	-std=c++14
)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_compile_definitions(DEBUG)
	add_compile_options(
		-g
		-fsanitize=undefined
	)
	add_link_options(
		-g
		-lubsan
	)
endif()



### SECTION libraries ###

if(${USE_STATIC_LIBRARY} STREQUAL "Yes")
	add_library(adjmat adjmat.cpp)
	add_library(ds data_structure.cpp)
	add_library(com common.cpp)
	link_libraries(adjmat ds com)
else()
	# to use inline functions, we have to get rid of static/dynamic linking
	# https://stackoverflow.com/questions/53114164/inlining-class-methods-inside-a-static-library
	set(lib adjmat.cpp adjmat.hpp data_structure.cpp data_structure.hpp common.cpp common.hpp)
endif()



### SECTION executables ###

add_executable(test test.cpp ${lib})
add_executable(serial serial-bfs.cpp ${lib})
add_executable(parallel parallel-bfs.cpp ${lib})
add_executable(io io_only.cpp ${lib})

# add OpenMP for parallel-bfs executable
find_library(omp libomp)
target_compile_options(parallel PRIVATE -fopenmp)
target_link_libraries(parallel omp)
