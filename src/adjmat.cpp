#include "adjmat.hpp"
#include <chrono>

adjacent_matrix::adjacent_matrix(u32 vertices, u32 edges)
    : n(vertices), m(edges), row_start(n + 1, 0), row_cnt(n + 1, 0), data(m * 2, 0) {}

adjacent_matrix adjacent_matrix::parse_matrix_market(Cstr file_path) {
  // IO timing begin
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();
  // IO timing begin

  FILE *f = fopen(file_path, "r");
  char line[512];

  // skip the comments, lines starts with '%'
  do { fgets(line, sizeof(line), f); } while (line[0] == '%');

  // matrix shape line
  u32 n, m, l;
  sscanf(line, "%u%u%u", &n, &m, &l);
  REQUIRE(n == m);
  debug() << "parse_matrix_market("
          << "vertices=" << n << ", "
          << "edges=" << l << ")\n";

  // read matrix elements
  adjacent_matrix matrix(n, l);
  struct pair {
    u32 x, y;
  } *pairs = new pair[l];
  for (u32 i = 0, x, y; i < l; i++) {
    fgets(line, sizeof(line), f);
    sscanf(line, "%u%u", &x, &y);
    pairs[i].x = x, pairs[i].y = y;
    matrix.row_cnt[x]++;
    if (x != y) { matrix.row_cnt[y]++; }
  }
  for (u32 i = 0; i < n; i++) { matrix.row_start[i + 1] = matrix.row_start[i] + matrix.row_cnt[i]; }
  matrix.row_cnt.set_all(0);
  for (u32 i = 0, x, y; i < l; i++) {
    x = pairs[i].x, y = pairs[i].y;
    matrix.adj(x)[matrix.row_cnt[x]++] = y;
    if (x != y) { matrix.adj(y)[matrix.row_cnt[y]++] = x; }
  }
  for (u32 i = 1; i <= n; i++) REQUIRE(matrix.row_cnt[i] <= n);

  delete[] pairs;
  fclose(f);

  // IO timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  debug() << "IO time: " << rt_dur.count() << '\n';
  // IO timing end

  return matrix;
}
