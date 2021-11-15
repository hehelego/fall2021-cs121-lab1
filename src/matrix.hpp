#include "common.hpp"

namespace sparse_matrix {
class csr {
  u32 n, m;
  u32 *start_ptr;
  struct element {
    u32 col, val;
  } * elements;
};
class coo {
  u32 n, m;
  struct element {
    u32 row, col, val;
  } * elements;
};
class matrix_market {
  u32 n, m;
};
} // namespace sparse_matrix
