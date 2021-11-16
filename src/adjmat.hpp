#pragma once // include guard
#include "common.hpp"
#include "data_structure.hpp"

// CSR sparse matrix representation
struct adjacent_matrix {
  u32 n, m;
  u32 *row_start, *row_cnt, *data;
  adjacent_matrix(u32 vertices, u32 edges);
  adjacent_matrix(const adjacent_matrix &matrix);
  ~adjacent_matrix();

  inline u32 vertices() const { return n; }
  inline u32 edges() const { return m; }
  inline u32 neighbours(u32 x) const { return row_cnt[x]; }
  inline u32 *adj(u32 x) const { return data + row_start[x]; }
  static adjacent_matrix parse_matrix_market(Cstr file_path);
};
