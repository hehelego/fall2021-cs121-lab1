#include "common.hpp"
#include <cctype>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <utility>
#include <vector>

using pu32 = std::pair<u32, u32>;
const u32 LINE_LEN = 61;
const u32 MAXN_EDGES = u32(1e9) + 10;

pu32 parse_pair(const char *p) {
  u32 x = 0, y = 0;
  while (isdigit(*p)) { x = x * 10 + *(p++) - '0'; }
  p++;
  while (isdigit(*p)) { y = y * 10 + *(p++) - '0'; }
  return std::make_pair(x, y);
}
inline void clear(char *const buf, u32 len) { memset(buf, 0, sizeof(char) * len); }

int main(int argc, char **argv) {
  REQUIRE(argc == 3);
  FILE *fin = fopen(argv[1], "r"), *fout = fopen(argv[2], "w");
  // find the optimal buffer length
  struct stat in_stat, out_stat;
  fstat(fileno(fin), &in_stat), fstat(fileno(fout), &out_stat);
  auto in_bl = in_stat.st_blksize, out_bl = out_stat.st_blksize;
  auto in_buf = new char[in_bl], out_buf = new char[out_bl];
  clear(in_buf, in_bl), clear(out_buf, out_bl);
  setvbuf(fin, in_buf, _IOFBF, in_bl), setvbuf(fout, out_buf, _IOFBF, out_bl);

  u32 n = 0, m = 0;
  auto line = new char[LINE_LEN];
  auto edges = (std::pair<u32, u32> *)::operator new(sizeof(pu32) * MAXN_EDGES);
  while (fgets(line, sizeof(line), fin)) {
    if (!isdigit(line[0])) continue;
    auto [x, y] = parse_pair(line);
    x++, y++;
    n = std::max(n, x), n = std::max(n, y);
    edges[m++] = std::make_pair(x, y);
  }

  fprintf(fout, "%%%%MatrixMarket matrix coordinate real symmetric\n%u %u %u\n", n, n, m);
  for (u32 i = 0; i < m; i++) {
    auto [x, y] = edges[i];
    fprintf(fout, "%u %u 1\n", x, y);
  }

  fclose(fin), fclose(fout);

  return 0;
}
