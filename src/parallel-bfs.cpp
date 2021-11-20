#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include "adjmat.hpp"
#include "common.hpp"
#include "data_structure.hpp"

i32 main(i32 argc, Cstr *argv) {
  REQUIRE(argc == 3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);
  auto V = matrix.vertices(), E = matrix.edges();
  (void)E;

  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();

  // bfs
  using tup2 = tuple2<u32, u32>;
  omp_set_num_threads(OMP_THREADS);

  array<u32> q{V};
  u32 ptr = 0;
  tuple2<array<tup2>, u32> sub[OMP_THREADS];
  for (u32 i = 0; i < OMP_THREADS; i++) sub[i].x.init(V), sub[i].y = 0;
  array<tup2> bfs_tree{V + 1};
  u32 edges_in_block = matrix.adj(source).size(), nodes_in_block = 1;

  u32 level = 0;
  bfs_tree.set_all(tup2{V + 1, V + 1});
  bfs_tree[source] = tup2{source, level};
  q[ptr++] = source;

  while (ptr > 0) {
    level++;
#pragma omp parallel for schedule(static)
    for (u32 i = 0; i < ptr; i++) {
      auto &[sub_q, sub_ptr] = sub[omp_get_thread_num()];
      auto u = q[i];
      auto adj = matrix.adj(u);
      for (u32 j = 0, v = 0; j < adj.size(); j++) {
        v = adj[j];
        if (bfs_tree[v].x > V) {
          assert(sub_ptr < sub_q.size());
          sub_q[sub_ptr++] = tup2{v, u};
        }
      }
    }

    ptr = 0;
    for (u32 i = 0; i < OMP_THREADS; i++) {
      auto &[sub_q, sub_ptr] = sub[i];
      for (u32 j = 0; j < sub_ptr; j++) {
        auto [v, p] = sub_q[j];
        if (bfs_tree[v].x > V) {
          bfs_tree[v] = tup2{p, level};
          q[ptr++] = v;
          edges_in_block += matrix.adj(v).size();
          nodes_in_block++;
        }
      }
      sub_ptr = 0;
    }
  }

  edges_in_block /= 2;

  // timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  std::cerr << "time: " << rt_dur.count() << '\t' << "MTEPS: " << (edges_in_block / 1e6 / rt_dur.count())
            << '\n';

  // output
  printf("%u %u\n", nodes_in_block, edges_in_block);
  for (u32 i = 1; i <= V; i++) {
    auto [p, d] = bfs_tree[i];
    if (d > V) { continue; }
    // printf("%u %u %u\n", i, d, p);
    printf("%u %u\n", i, d);
    // uncomment this line and compare the output with networkx-bfs output to verify correctness.
  }

  return 0;
}
