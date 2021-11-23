#include "adjmat.hpp"
#include "common.hpp"
#include <cstdio>
void test_matrix(u32 argc, Cstr *argv) {
  for (u32 i = 1; i < argc; i++) {
    auto matrix = adjacent_matrix::parse_matrix_market(argv[i]);

    u32 source = 13;
    debug(std::cout) << "adj" << '[' << source << ']' << ' ' << "cnt=" << matrix.neighbours(source) << '\n';
    auto adj = matrix.adj(source);
    for (u32 i = 0; i < adj.size() && i < 10; i++) { debug(std::cout) << '\t' << adj[i] << '\n'; }
  }
}
void test_bitset() {
  bitset<u8> set{65};
  set.set(5), set.set(16), set.set(64);
  debug() << set.try_set(0) << '\n';
  debug() << set.try_set(0) << '\n';
  for (u32 i = 0; i < set.size(); i++) {
    if (i == 5 || i == 16 || i == 0 || i == 64) {
      REQUIRE(set.test(i) == true);
    } else {
      REQUIRE(set.test(i) == false);
    }
  }
}
void test_array() {
  u32 V = 1971281;
  array<u32> q{V};
  using tup2 = tuple2<u32, u32>;
  tuple2<array<tup2>, u32> sub[OMP_THREADS];
  for (u32 i = 0; i < OMP_THREADS; i++) sub[i].x.init(V), sub[i].y = 0;
  array<tup2> bfs_tree{V + 1};
}

void test_env() {
  debug() << "NUM_THREADS" << OMP_THREADS << '\n';
  debug() << "NUM_ROUNDS" << ROUNDS << '\n';
  debug() << "NUM_SEED" << RNG_SEED << '\n';
}
void test_omp_reduce() {
  int x = 10;
#pragma omp parallel for reduction(+ : x)
  for (int i = 0; i < 10; i++) { x += 1; }
#pragma omp parallel for reduction(+ : x)
  for (int i = 0; i < 10; i++) { x += 1; }
  debug() << x << '\n';
}

i32 main(i32 argc, Cstr *argv) {
  test_env();

  // test matrix
  test_matrix(argc, argv);

  // test bitset
  test_bitset();

  // test array
  test_array();

  return 0;
}
