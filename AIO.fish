#!/usr/bin/fish

# a all-in-one script for fetch-data & build & benchmark

set files                                           # matrix-market testcase files
set mode            "Release"                       # build mode
set rounds          "20"                            # run $rounds times on each testcase
set max_threads     "30"                            # start at most $max_threads threads in parallel bfs
set seed            "19260817"                      # the random number generator seed
set output_serial   "/tmp/benchmark_serial"         # the file to store the benchmark result of serial-bfs
set output_parallel "/tmp/benchmark_parallel"       # the file to store the benchmark result of parallel-bfs

ulimit -s unlimited

echo '=== build ==='
cmake -D CMAKE_BUILD_TYPE=$mode -D NUM_THREADS=$max_threads -D NUM_ROUNDS=$rounds -D NUM_SEED=$seed .    >/dev/null 2>/dev/null
make -j8    >/dev/null 2>/dev/null


echo '=== fetch datasets ==='
cd data/
./prepare_data.fish
set files (ls | grep '.mm$')
cd ../


echo '=== benchmark (serial) ==='
tee $output_serial </dev/null
for file in $files
  echo "##### running on testcase ($file) #####" | tee -a $output_serial
  set testcase "data/$file"
  bin/serial     $testcase    >/dev/null 2>>$output_serial
end

for threads in (seq 1 1 $max_threads)
  echo '=== benchmark (parallel) ===' "$threads"
  cmake -D CMAKE_BUILD_TYPE=$mode -D NUM_THREADS=$threads -D NUM_ROUNDS=$rounds -D NUM_SEED=$seed .    >/dev/null 2>/dev/null
  make -j8    >/dev/null 2>/dev/null
  set output_parallel "/tmp/benchmark_parallel_$threads"
  tee $output_parallel </dev/null
  for file in $files
    echo "##### running on testcase ($file) #####" | tee -a $output_parallel
    set testcase "data/$file" 
    bin/parallel $testcase    >/dev/null 2>>$output_parallel
  end
end
