#pragma once // include guard
#include "common.hpp"
#include "data_structure.hpp"

// CSR sparse matrix representation
// **NOTE** undirected graph
struct adjacent_matrix {
  u32 n, m;
  std::vector<u32> row_start, row_cnt, data;
  adjacent_matrix(u32 vertices, u32 edges);

  inline u32 vertices() const { return n; }
  inline u32 edges() const { return m; }
  inline u32 operator[](u32 i) const { return data[i]; }
  inline u32 &operator[](u32 i) { return data[i]; }
  inline u32 row_head(u32 x) const { return row_start[x]; }
  inline u32 deg(u32 x) const { return row_cnt[x]; }
  static adjacent_matrix parse_matrix_market(Cstr file_path);
};
  // inline u32 operator()(u32 x, u32 i) const { return data[row_start[x] + i]; }
  // inline u32 &operator()(u32 x, u32 i) { return data[row_start[x] + i]; }
