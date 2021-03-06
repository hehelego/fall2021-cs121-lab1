#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#include "adjmat.hpp"
#include "bitset.hpp"
#include "common.hpp"

struct frontier {
private:
  std::vector<u32> vert, degr;
  u32 len;

public:
  frontier(u32 n = 0) : vert(n), degr(n), len(0) {}
  inline u32 size() const { return len; }
  inline void resize(u32 l) { len = l; }
  // get/set vertex
  inline u32 operator[](u32 i) const { return vert[i]; }
  inline u32 &operator[](u32 i) { return vert[i]; }
  // get/set vertex degree
  inline u32 operator()(u32 i) const { return degr[i]; }
  inline u32 &operator()(u32 i) { return degr[i]; }

  // prefix sum on degree array
  u32 scan_degree() {
    if (len == 0) { return 0; }
    static std::array<u32, OMP_THREADS> blocks;
#pragma omp parallel
    {
      u32 id = omp_get_thread_num();
      u32 part = 0;
#pragma omp for schedule(static) nowait
      for (u32 i = 0; i < len; i++) {
        part += (*this)(i);
        (*this)(i) = part;
      }
      blocks[id] = part;
#pragma omp barrier
      u32 prev_blk = 0;
      for (u32 i = 0; i < id; i++) { prev_blk += blocks[i]; }
#pragma omp for schedule(static)
      for (u32 i = 0; i < len; i++) { (*this)(i) += prev_blk; }
    }
    return (*this)(len - 1);
  }
  // (exculsive) prefix sum on vertex
  u32 scan_vertex(u32 V) {
    if (len == 0) { return 0; }
    static std::array<u32, OMP_THREADS> blocks;
#pragma omp parallel
    {
      u32 id = omp_get_thread_num();
      u32 part = 0;
#pragma omp for schedule(static) nowait
      for (u32 i = 0; i < len; i++) {
        (*this)(i) = part;
        part += ((*this)[i] <= V);
      }
      blocks[id] = part;
#pragma omp barrier
      u32 prev_blk = 0;
      for (u32 i = 0; i < id; i++) { prev_blk += blocks[i]; }
#pragma omp for schedule(static)
      for (u32 i = 0; i < len; i++) { (*this)(i) += prev_blk; }
    }
    return ((*this)[len - 1] <= V) + (*this)(len - 1);
  }
};

void once(const adjacent_matrix &matrix, u32 source, bool ouput) {
  // timing start
  using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration;
  auto begin_ts = high_resolution_clock::now();
  // timing start

  auto V = matrix.vertices(), E = matrix.edges();
  (void)E;

  frontier cur_frontier(V), next_frontier(2 * E);
  bitset_atomic<> vis(V + 1);
  std::vector<std::pair<u32, u32>> bfs_tree(V + 1, std::make_pair(0, 0));
  u32 edges_in_block = 0, nodes_in_block = 0;

  u32 level = 0;
  vis.set(source), bfs_tree[source] = std::make_pair(source, level);
  cur_frontier.resize(1), cur_frontier[0] = source;

  while (cur_frontier.size() > 0) {
    level++;

    u32 cur_level_nodes = cur_frontier.size();
    nodes_in_block += cur_level_nodes;
#pragma omp parallel for schedule(static) reduction(+ : edges_in_block)
    for (u32 i = 0; i < cur_level_nodes; i++) {
      u32 u = cur_frontier[i], deg = matrix.deg(u);
      cur_frontier(i) = deg, edges_in_block += deg;
    }
    auto frontier_neighbours = cur_frontier.scan_degree();
    next_frontier.resize(frontier_neighbours);
#pragma omp parallel for schedule(guided)
    for (u32 i = 0; i < cur_level_nodes; i++) {
      auto u = cur_frontier[i], head = matrix.row_head(u), deg = matrix.deg(u);
      auto startpos = i > 0 ? cur_frontier(i - 1) : 0;
      for (u32 j = 0; j < deg; j++) {
        auto v = matrix[head + j];
        next_frontier[startpos + j] = V + 1;
        // atomically test and set, eliminate race condition
        if (!vis.try_set(v)) {
          next_frontier[startpos + j] = v;
          bfs_tree[v] = std::make_pair(u, level);
        }
      }
    }
    cur_frontier.resize(next_frontier.scan_vertex(V));
#pragma omp parallel for schedule(static)
    for (u32 i = 0; i < frontier_neighbours; i++) {
      auto v = next_frontier[i];
      if (v <= V) { cur_frontier[next_frontier(i)] = v; }
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
  if (ouput) {
    printf("%u %u\n", nodes_in_block, edges_in_block);
    for (u32 i = 1; i <= V; i++) {
      auto [p, d] = bfs_tree[i];
      if (p == 0) { continue; }
      printf("%u %u %u\n", i, d, p);
    }
  }
}

// usage:
//   run ROUNDS bfs from random sources:  bin/parallel-bfs graph.mm
//   run one bfs from the source:         bin/parallel-bfs graph.mm source
i32 main(i32 argc, Cstr *argv) {
  REQUIRE(argc == 2 || argc == 3);

  srand(RNG_SEED);
  omp_set_num_threads(OMP_THREADS);

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
