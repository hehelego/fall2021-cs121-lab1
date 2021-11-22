#!/usr/bin/fish

# a all-in-one script for fetch-data & build & benchmark

set files                                           # matrix-market testcase files
set mode    "release"                               # build mode
set rounds  "20"                                    # run $rounds times on each testcase
set threads "20"                                    # start $threads threads in parallel bfs
set seed    "19260817"                              # the random number generator seed
set source                                          # randomly selected source for BFS tree
set output_serial   "/tmp/benchmark_serial"         # the file to store the benchmark result of serial-bfs
set output_parallel "/tmp/benchmark_parallel"       # the file to store the benchmark result of parallel-bfs

ulimit -s unlimited

echo '=== build ==='
cmake -D BUILD_TYPE=$mode -D CMAKE_BUILD_TYPE=$mode -D NUM_THREADS=$threads -D NUM_ROUNDS=$rounds -D NUM_SEED=$seed .
make


echo '=== fetch datasets ==='
cd data/
./prepare_data.fish
set files (ls | grep '.mm$')
cd ../


echo '=== benchmark ==='
tee $output_serial $output_parallel </dev/null

for file in $files
  echo "##### running on testcase ($file) #####" | tee -a $output_serial $output_parallel

  set testcase "data/$file" 
  bin/serial   $testcase >/dev/null 2>>$output_serial
  bin/parallel $testcase >/dev/null 2>>$output_parallel
end
