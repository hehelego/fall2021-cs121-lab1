add_compile_options(
	-Wall
	-Wextra
	-O2
	-fopenmp
	)

add_link_options(
	-fopenmp
	)

add_executable(serial serial-bfs.cpp)
add_executable(parallel parallel-bfs.cpp)
