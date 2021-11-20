#include "adjmat.hpp"
#include "common.hpp"
#include <cstdio>
void test_matrix(i32 argc, Cstr *argv) {
  REQUIRE(argc == 3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);

  debug(std::cout) << "adj" << '[' << source << ']' << ' ' << "cnt=" << matrix.neighbours(source) << '\n';
  auto adj = matrix.adj(source);
  for (u32 i = 0; i < adj.size() && i < 10; i++) { debug(std::cout) << '\t' << adj[i] << '\n'; }
}
void test_bitset() {
  bitset<u8> set{65};
  set.set(5), set.set(16), set.set(0), set.set(64);
  for (u32 i = 0; i < set.size(); i++) { debug() << i << ": " << set.get(i) << '\n'; }
}
void test_array() {
  u32 V = 1971281;
  array<u32> q{V};
  using tup2 = tuple2<u32, u32>;
  tuple2<array<tup2>, u32> sub[OMP_THREADS];
  for (u32 i = 0; i < OMP_THREADS; i++) sub[i].x.init(V), sub[i].y = 0;
  array<tup2> bfs_tree{V + 1};
}

i32 main() {
  debug() << "NUM_THREADS" << OMP_THREADS << '\n';

  // test matrix
  Cstr argv[] = {"bin/test", "data/web-Stanford.txt.mm", "1"};
  test_matrix(3, argv);

  // test bitset
  test_bitset();

  // test array
  test_array();

  return 0;
}
