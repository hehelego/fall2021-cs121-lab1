add_compile_options(
	-Wall
	-Wextra
	-O2
	-std=c++14
	)


add_executable(serial serial-bfs.cpp)


add_executable(parallel parallel-bfs.cpp)
find_library(omp libomp)
target_compile_options(parallel PRIVATE -fopenmp)
target_link_libraries(parallel omp)
