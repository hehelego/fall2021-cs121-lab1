#include "adjmat.hpp"
#include <chrono>

adjacent_matrix::adjacent_matrix(u32 vertices, u32 edges)
    : n(vertices), m(edges), data(m, 0), row_ptr(n + 1, 0) {}

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
  std::vector<std::pair<u32, u32>> pairs(l);
  std::vector<u32> row_pre(n + 1, 0);
  for (u32 i = 0, x, y; i < l; i++) {
    fgets(line, sizeof(line), f);
    sscanf(line, "%u%u", &x, &y);
    pairs[i] = std::make_pair(x, y);
    row_pre[x]++;
  }
  for (u32 i = 1; i <= n; i++) { row_pre[i] += row_pre[i - 1]; }
  for (u32 i = 0; i < l; i++) {
    auto [x, y] = pairs[i];
    matrix[row_pre[x - 1] + matrix.row_ptr[x]++] = y;
  }
  for (u32 i = 0; i <= n; i++) { matrix.row_ptr[i] = row_pre[i]; }

  fclose(f);

  // IO timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  debug() << "IO time: " << rt_dur.count() << '\n';
  // IO timing end

  return matrix;
}
