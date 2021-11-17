#include "adjmat.hpp"
#include "common.hpp"
#include <cstdio>

i32 main(i32 argc, Cstr *argv) {
  assert(argc == 3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);

  {
    u32 i = source;

    debug(std::cout) << "adj" << '[' << i << ']' << ' ' << "cnt=" << matrix.neighbours(i) << '\n';
    for (u32 *head = matrix.adj(i), j = 0, r = matrix.neighbours(i); j < r; j++) {
      debug(std::cout) << '\t' << head[j] << '\n';
    }
  }

  return 0;
}
