#pragma once // include guard
#include "common.hpp"

template <typename T> struct queue {
  u32 l, r, n;
  T *data;
  queue(u32 cap) {
    l = 0, r = 0;
    data = new T[n = cap];
  }
  ~queue() { delete[] data; }
  inline u32 size() const { return r - l; }

  inline void push(const T &x) { data[r++] = x; }
  inline void pop() { l++; }
  inline const T &get() const { return data[l]; }
  inline void take(T &to) { to = data[l++]; }
};
template <u32 N, typename Word = u64> struct static_bitset {
  static const u32 S = sizeof(Word);
  static const u32 M = (N + S - 1) / sizeof(S);
  Word data[M];
  static_bitset() {
    for (u32 i = 0; i < M; i++) { data[i] = Word{0}; }
  }
  inline bool operator[](u32 i) const { return (data[i / S] >> (i % S)) & 1; }
  inline bool &operator[](u32 i) { return (data[i / S] >> (i % S)) & 1; }
};

template <typename Word = u64> struct bitset {
  static const u32 S = sizeof(Word);
  const u32 m;
  const Word *data;
  bitset(u32 n) : m((n + S - 1) / S), data(new Word[m]) {
    assert(data != nullptr);
    for (u32 i = 0; i < m; i++) { data[i] = Word{0}; }
  }
  inline bool operator[](u32 i) const { return (data[i / S] >> (i % S)) & 1; }
  inline bool &operator[](u32 i) { return (data[i / S] >> (i % S)) & 1; }
};
