#include "common.hpp"
#include <cstdio>
#include <utility>
#include <vector>

int main() {
  char buf[512];
  u32 n = 0, m = 0, x, y;
  std::vector<std::pair<u32, u32>> edges;
  while (!feof(stdin)) {
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] == '#') continue;
    sscanf(buf, "%u%u", &x, &y);
    x++, y++;
    n = std::max(n, x), n = std::max(n, y);
    edges.emplace_back(x, y), m++;
  }

  printf("%%%%MatrixMarket matrix coordinate real symmetric\n%u %u %u\n", n, n, m);
  for (auto [x, y] : edges) { printf("%u %u 1\n", x, y); }
  return 0;
}
