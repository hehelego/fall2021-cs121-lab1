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
  for (u32 i = 0; i < adj.size(); i++) { debug(std::cout) << '\t' << adj[i] << '\n'; }

  for(u32 i=0;i<matrix.vertices();i++){
    matrix.adj(i);
  }
}
void test_bitset() {
  bitset<u8> set{100};
  set.set(5), set.set(16), set.set(0), set.set(99);
  for (u32 i = 0; i < set.size(); i++) { debug() << i << ": " << set.get(i) << '\n'; }
}

i32 main() {
  Cstr argv[] = {"bin/test", "data/web-Stanford.txt.mm", "1"};
  test_matrix(3, argv);
  //
  // test_bitset();


  return 0;
}
