#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "adjmat.hpp"
#include "common.hpp"
#include "data_structure.hpp"

i32 main(i32 argc, Cstr *argv) {
  REQUIRE(argc == 3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);

  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();

  // bfs
  u32 edges_in_block = 0;

  edges_in_block /= 2;

  // timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  std::cerr << "time: " << rt_dur.count() << '\t' << "MTEPS: " << (edges_in_block / 1e6 / rt_dur.count())
            << '\n';

  // output

  return 0;
}
