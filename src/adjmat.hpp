#pragma once // include guard
#include "common.hpp"
#include "data_structure.hpp"

// CSR sparse matrix representation
// **NOTE** undirected graph
struct adjacent_matrix {
  u32 n, m;
  array<u32> row_start, row_cnt, data;
  adjacent_matrix(u32 vertices, u32 edges);

  inline u32 vertices() const { return n; }
  inline u32 edges() const { return m; }
  inline u32 neighbours(u32 x) const { return row_cnt[x]; }
  inline view<u32> adj(u32 x) const { return data.slice(row_start[x], row_cnt[x]); }
  static adjacent_matrix parse_matrix_market(Cstr file_path);
};
