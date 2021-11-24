#pragma once // include guard
#include "common.hpp"
#include <atomic>
#include <limits>

template <typename T> struct view {
private:
  T *const data;
  u32 start, len;

public:
  view(T *const data, u32 start, u32 len) : data(data), start(start), len(len) {}
  inline u32 size() const { return len; }
  inline T &operator[](u32 i) { return data[start + i]; }
  inline const T &operator[](u32 i) const { return data[start + i]; }
};
template <typename T> struct array {
private:
  u32 n;
  T *data;

public:
  ~array() { delete[] data; }
  array(u32 n = 0) : n(n), data(new T[n]) {}
  array(u32 n, const T &val) : n(n), data(new T[n]) { set_all(val); }
  array(const array &a) : n(a.n), data(new T[n]) {
    for (u32 i = 0; i < n; i++) data[i] = a[i];
  }
  inline void init(u32 m) {
    delete[] data;
    data = new T[n = m];
  }
  inline void init(u32 m, const T &val) {
    init(m);
    set_all(val);
  }

  inline u32 size() const { return n; }
  inline T &operator[](u32 i) { return data[i]; }
  inline const T &operator[](u32 i) const { return data[i]; }
  inline void set_all(const T &val) {
    for (u32 i = 0; i < n; i++) data[i] = val;
  }
  inline view<T> slice(u32 start, u32 len) const { return view<T>(data, start, len); }
};

template <typename Word = u64> struct bitset {
private:
  static const u32 S = sizeof(Word) * 8;
  const u32 n, m;
  array<std::atomic<Word>> data;

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
