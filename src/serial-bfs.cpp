#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include "matrix.hpp"
#include "common.hpp"

int main() {
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
