#include "adjmat.hpp"
#include <cstdio>

adjacent_matrix::adjacent_matrix(u32 vertices, u32 edges) {
  n = vertices, m = edges;
  row_start = new u32[n + 1], row_cnt = new u32[n + 1], data = new u32[m];
  assert(row_start != nullptr), assert(row_cnt != nullptr), assert(data != nullptr);
}
adjacent_matrix::adjacent_matrix(const adjacent_matrix &matrix) {
  n = matrix.n, m = matrix.m;
  row_start = new u32[n + 1], row_cnt = new u32[n + 1], data = new u32[m];
  assert(row_start != nullptr), assert(row_cnt != nullptr), assert(data != nullptr);
  for (u32 i = 0; i <= n; i++) { row_start[i] = matrix.row_start[i], row_cnt[i] = matrix.row_cnt[i]; }
  for (u32 i = 0; i < m; i++) { data[i] = matrix.data[i]; }
}
adjacent_matrix::~adjacent_matrix() { delete[] row_start, delete[] data; }

adjacent_matrix adjacent_matrix::parse_matrix_market(Cstr file_path) {
  // skip the comments, lines starts with '%'
  // read the line for matrix shape
  // read matrix elements
  FILE *f = fopen(file_path, "r");
  assert(f != nullptr);

  char line[512];
  do { fgets(line, sizeof(line), f); } while (line[0] == '%' || line[0] == '#');
  u32 n, m, l;
  sscanf(line, "%u%u%u", &n, &m, &l);
  assert(n == m);

  adjacent_matrix matrix(n, l);
  struct pair {
    u32 x, y;
  } *pairs = new pair[l];

  for (u32 i = 0, x, y; i < l; i++) {
    fgets(line, sizeof(line), f);
    sscanf(line, "%u%u", &x, &y);
    pairs[i].x = x, pairs[i].y = y;
    matrix.row_cnt[x]++;
  }
  matrix.row_start[0] = 0;
  for (u32 i = 0; i < n; i++) { matrix.row_start[i + 1] = matrix.row_start[i] + matrix.row_cnt[i]; }

  delete[] pairs;
  fclose(f);

  return matrix;
}
