#pragma once // include guard
#include "common.hpp"
#include <atomic>
#include <limits>

template <typename Word = u64> struct bitset {
private:
  static const u32 S = sizeof(Word) * 8;
  const u32 n, m;
  std::vector<std::atomic<Word>> data;

public:
  bitset(u32 n) : n(n), m((n + S - 1) / S), data(m) { clear(); }

  inline u32 size() const { return n; }
  inline bool test(u32 i) const { return (data[i / S] >> (i % S)) & 1; }
  inline void set(u32 i) { data[i / S] |= (Word{1} << (i % S)); }
  inline bool try_set(u32 i) { return (data[i / S].fetch_or(Word{1} << (i % S)) >> (i % S)) & 1; }
  inline void clear() {
    for (u32 i = 0; i < m; i++) { data[i] = Word{0}; }
  }
  inline void combine(const bitset &rhs) {
    for (u32 i = 0; i < m; i++) { data[i] |= rhs[i]; }
  }
};
