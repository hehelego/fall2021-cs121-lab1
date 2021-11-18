#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "adjmat.hpp"
#include "common.hpp"
#include "data_structure.hpp"

i32 main(i32 argc, Cstr *argv) {
  REQUIRE(argc == 3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);
  auto V = matrix.vertices(), E = matrix.edges();

  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();

  // bfs
  using tup2 = tuple2<u32, u32>;

  queue<tup2> q{V};
  bitset<> vis{V + 1};
  array<tup2> bfs_tree{V + 1};
  u32 edges_in_block = 0;

  bfs_tree[0] = tup2{source, 0}, q.push(tup2{source, 0}), vis.set(source);

  while (q.size() > 0) {
    auto row = q.get();
    auto [u, dis] = row;
    q.pop();
    dis++;

    auto adj = matrix.adj(u);
    edges_in_block += adj.size();
    for (u32 i = 0, v; i < adj.size(); i++) {
      v = adj[i];
      if (!vis.get(v)) { bfs_tree[v] = tup2{u, dis}, q.push(tup2{v, dis}), vis.set(v); }
    }
  }
  edges_in_block /= 2;

  // timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  std::cerr << "time: " << rt_dur.count() << '\t' << "MTEPS: " << (edges_in_block / 1e6 / rt_dur.count())
            << '\n';

  // output
  printf("%u %u\n", bfs_tree.size(), edges_in_block);
  for (u32 i = 0; i < V; i++) {
    if (vis.get(i)) {
      auto [p, d] = bfs_tree[i];
      printf("%u %u %u\n", i, d, p);
      // printf("%u %u\n", u, d); // uncomment this line and compare the output with networkx-bfs output to
      // verify correctness.
    }
  }

  return 0;
}
