#include "adjmat.hpp"
#include "common.hpp"
#include <cstdio>
void test_matrix(u32 argc, Cstr *argv) {
  for (u32 i = 1; i < argc; i += 2) {
    auto matrix = adjacent_matrix::parse_matrix_market(argv[i]);

    u32 source = 0;
    sscanf(argv[i + 1], "%u", &source);
    debug(std::cout) << "adj" << '[' << source << ']' << ' ' << "cnt=" << matrix.deg(source) << '\n';
    for (u32 i = 0; i < matrix.deg(source) && i < 10; i++) {
      debug(std::cout) << '\t' << matrix(source, i) << '\n';
    }
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

  test_matrix(argc, argv);

  test_bitset();

  test_omp_reduce();

  return 0;
}
