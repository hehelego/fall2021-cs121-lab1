#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include "adjmat.hpp"
#include "common.hpp"

i32 main(i32 argc, Cstr *argv) {
  assert(argc==3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);

#pragma omp parallel num_threads(16)
  {
#pragma omp master
    { printf("I am master threads=%d\n", omp_get_num_threads()); }

#pragma omp critical
    { printf("thread num %d\n", omp_get_thread_num()); }
  }
  printf("%.3f\n", std::acos(-1.0));
  return 0;
}
