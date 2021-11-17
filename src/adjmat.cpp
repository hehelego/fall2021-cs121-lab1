#include "adjmat.hpp"
#include <cstdio>
#include <cstring>

adjacent_matrix::adjacent_matrix(u32 vertices, u32 edges, bool undirected)
    : n(vertices), m(edges), sym(undirected), row_start(n+1, 0), row_cnt(n+1, 0), data(m, 0) {}

adjacent_matrix adjacent_matrix::parse_matrix_market(Cstr file_path) {
  FILE *f = fopen(file_path, "r");
  assert(f != nullptr);
  char line[512];

  // header line
  fgets(line, sizeof(line), f);
  bool sym = (strstr(line, "symmetric") != nullptr);

  // skip the comments, lines starts with '%'
  do { fgets(line, sizeof(line), f); } while (line[0] == '%');

  // matrix shape line
  u32 n, m, l, edges = 0;
  sscanf(line, "%u%u%u", &n, &m, &l);
  assert(n == m);
  edges = sym ? l * 2 : l;
  debug() << "parse_matrix_market:" << '\n'
          << '\t' << "sym=" << sym << '\n'
          << '\t' << "vertices=" << n << '\n'
          << '\t' << "edges=" << edges << '\n';

  // read matrix elements
  adjacent_matrix matrix(n, edges, sym);
  struct pair {
    u32 x, y;
  } *pairs = new pair[l];
  for (u32 i = 0, x, y; i < l; i++) {
    fgets(line, sizeof(line), f);
    sscanf(line, "%u%u", &x, &y);
    pairs[i].x = x, pairs[i].y = y;
    matrix.row_cnt[x]++;
    if (sym && x != y) { matrix.row_cnt[y]++; }
  }
  for (u32 i = 0; i < n; i++) { matrix.row_start[i + 1] = matrix.row_start[i] + matrix.row_cnt[i]; }
  matrix.row_cnt.set_all(0);
  for (u32 i = 0, x, y; i < l; i++) {
    x = pairs[i].x, y = pairs[i].y;
    matrix.adj(x)[matrix.row_cnt[x]++] = y;
    if (sym && x != y) { matrix.adj(y)[matrix.row_cnt[y]++] = x; }
  }

  delete[] pairs;
  fclose(f);

  return matrix;
}
