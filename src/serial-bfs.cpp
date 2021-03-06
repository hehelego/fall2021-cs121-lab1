#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "adjmat.hpp"
#include "bitset.hpp"
#include "common.hpp"

void once(const adjacent_matrix &matrix, u32 source, bool output) {
  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();
  // timing start

  auto V = matrix.vertices(), E = matrix.edges();
  (void)E;

  bitset_normal<> vis{V + 1};
  std::vector<u32> q(V);
  u32 ql = 0, qr = 0;
  std::vector<std::pair<u32, u32>> bfs_tree(V + 1, std::make_pair(0, 0));
  u32 edges_in_block = 0, nodes_in_block = 0;

  bfs_tree[source] = std::make_pair(source, 0), q[qr++] = source;
  vis.set(source);

  while (ql < qr) {
    auto u = q[ql++], dis = bfs_tree[u].second + 1;
    auto head = matrix.row_head(u), deg = matrix.deg(u);
    edges_in_block += deg, nodes_in_block++;
    for (u32 i = 0, v; i < deg; i++) {
      v = matrix[head + i];
      if (!vis.try_set(v)) { vis.set(v), bfs_tree[v] = std::make_pair(u, dis), q[qr++] = v; }
    }
  }
  edges_in_block /= 2;

  // timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  std::cerr << "source: " << source << ' ' << "time: " << rt_dur.count() << ' '
            << "MTEPS: " << (edges_in_block / 1e6 / rt_dur.count()) << '\n';
  // timing end

  // output
  if (output) {
    printf("%u %u\n", nodes_in_block, edges_in_block);
    for (u32 i = 1; i <= V; i++) {
      auto [p, d] = bfs_tree[i];
      if (p == 0) { continue; }
      printf("%u %u %u\n", i, d, p);
    }
  }
}

// usage:
//   run ROUNDS bfs from random sources:  bin/serial-bfs graph.mm
//   run one bfs from the source:         bin/serial-bfs graph.mm source
i32 main(i32 argc, Cstr *argv) {
  REQUIRE(argc == 2 || argc == 3);

  srand(RNG_SEED);

  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  auto V = matrix.vertices();
  if (argc == 2) {
    for (u32 i = 0; i < ROUNDS; i++) { once(matrix, rand() % V + 1, false); }
  } else {
    u32 source = 0;
    sscanf(argv[2], "%u", &source);
    once(matrix, source, true);
  }
  return 0;
}
