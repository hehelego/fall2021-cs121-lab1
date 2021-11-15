#pragma once // include guard
#include "common.hpp"
#include "data_structure.hpp"

namespace sparse_matrix {
struct csr {
  u32 n, m;
  FixedArray<u32> start_pos;
  struct element {
    u32 col, val;
  } * elements;
};
struct coo {
  u32 n, m;
  struct element {
    u32 row, col, val;
  } * elements;
};
struct matrix_market {
  u32 n, m;
};
} // namespace sparse_matrix
