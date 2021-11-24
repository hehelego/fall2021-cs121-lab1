#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "adjmat.hpp"
#include "common.hpp"
#include "data_structure.hpp"

void once(const adjacent_matrix &matrix, u32 source, bool output) {
  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();
  // timing start

  auto V = matrix.vertices(), E = matrix.edges();
  (void)E;

  using tup2 = tuple2<u32, u32>;
  array<tup2> q{V};
  u32 ql = 0, qr = 0;
  array<tup2> bfs_tree{V + 1};
  u32 edges_in_block = 0, nodes_in_block = 0;

  bfs_tree.set_all(tup2{V + 1, V + 1});
  bfs_tree[source] = tup2{source, 0}, q[qr++] = tup2{source, 0};

  while (ql < qr) {
    auto [u, dis] = q[ql++];
    auto adj = matrix.adj(u);
    auto deg = matrix.deg(u);
    edges_in_block += deg, nodes_in_block++;
    dis++;
    for (u32 i = 0, v; i < deg; i++) {
      v = adj[i];
      if (bfs_tree[v].y > V) { bfs_tree[v] = tup2{u, dis}, q[qr++] = tup2{v, dis}; }
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
      if (d > V) { continue; }
      printf("%u %u %u\n", i, d, p);

      // printf("%u %u\n", i, d);
      // uncomment this line and compare the output with networkx-bfs output to verify correctness.
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
