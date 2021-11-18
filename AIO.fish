#!/usr/bin/fish

# a all-in-one script for fetch-data & build & benchmark

set files                                           # matrix-market testcase files
set rounds "20"                                     # run $rounds times on each testcase
set rounds "2"                                     # run $rounds times on each testcase
set source                                          # randomly selected source for BFS tree
set output_serial   "/tmp/benchmark_serial"         # the file to store the benchmark result of serial-bfs
set output_parallel "/tmp/benchmark_parallel"       # the file to store the benchmark result of parallel-bfs



echo '=== fetch datasets ==='
cd data/
./prepare_data.fish
set files (ls | rg '.mm$')
cd ../



echo '=== build ==='
cmake -D CMAKE_BUILD_TYPE=Release -D INLINE_LIBRARY=ON .
make



echo '=== benchmark ==='
tee $output_serial $output_parallel </dev/null

for file in $files
  echo "##### running on testcase ($file) #####" | tee -a $output_serial $output_parallel

  set testcase "data/$file" 
  set sources (data/random_source.py $testcase $rounds)
  for source in $sources
    echo "source=$source" | tee -a $output_serial $output_parallel
    bin/serial   $testcase $source        >/dev/null 2>>$output_serial
    bin/parallel $testcase $source        >/dev/null 2>>$output_parallel
  end
end
