#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "adjmat.hpp"
#include "common.hpp"
#include "data_structure.hpp"

i32 main(i32 argc, Cstr *argv) {
  assert(argc == 3);
  auto matrix = adjacent_matrix::parse_matrix_market(argv[1]);
  u32 source = 0;
  sscanf(argv[2], "%u", &source);

  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();

  // bfs

  queue<output_row> bfs_tree{matrix.vertices()};
  u32 edges = 0;

  bitset<> vis{matrix.vertices()};
  queue<output_row> q{matrix.vertices()};
  vis.set(source);
  auto root = output_row{source, 0, source};
  bfs_tree.push(root), q.push(root);

  while (q.size() > 0) {
    auto row = q.get();
    auto [u, dis, par] = row;
    q.pop();
    dis++;

    auto adj = matrix.adj(u);
    edges += adj.size();
    for (u32 i = 0, v; i < adj.size(); i++) {
      v = adj[i];
      if (!vis.get(v)) {
        vis.set(v);
        auto row = output_row{v, dis, u};
        bfs_tree.push(row), q.push(row);
      }
    }
  }
  if (matrix.undirected()) { edges /= 2; }

  // timing end
  auto end_ts = high_resolution_clock::now();
  auto rt_dur = duration_cast<duration<double>>(end_ts - begin_ts);
  std::cerr << "time: " << rt_dur.count() << '\t' << "MTEPS: " << (edges / 1e6 / rt_dur.count()) << '\n';

  // output
  printf("%u %u\n", bfs_tree.size(), edges);
  while (bfs_tree.size() > 0) {
    auto [u, d, p] = bfs_tree.get();
    bfs_tree.pop();
    printf("%u %u %u\n", u, d, p);
  }

  return 0;
}
