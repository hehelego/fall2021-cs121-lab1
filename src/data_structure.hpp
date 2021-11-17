#pragma once // include guard
#include "common.hpp"

template <typename T> struct view {
  T *const data;
  u32 start, len;
  view(T *const data, u32 start, u32 len) : data(data), start(start), len(len) {}
  inline u32 size() const { return len; }
  inline T &operator[](u32 i) { return data[start + i]; }
  inline const T &operator[](u32 i) const { return data[start + i]; }
};
template <typename T> struct array {
  u32 n;
  T *const data;
  array(u32 n) : n(n), data(new T[n]) { assert(data != nullptr); }
  array(u32 n, const T &val) : n(n), data(new T[n]) {
    assert(data != nullptr);
    set_all(val);
  }
  array(const array &a) : n(a.n), data(new T[n]) {
    assert(data != nullptr);
    for (u32 i = 0; i < n; i++) data[i] = a[i];
  }
  ~array() { delete[] data; }

  inline u32 size() const { return n; }
  inline T &operator[](u32 i) { return data[i]; }
  inline const T &operator[](u32 i) const { return data[i]; }
  void set_all(const T &val) {
    for (u32 i = 0; i < n; i++) data[i] = val;
  }

  view<T> slice(u32 start, u32 len) const {
    assert(start + len <= n);
    return view<T>(data, start, len);
  }
};

template <typename T> struct queue {
  u32 l, r;
  array<T> data;
  queue(u32 n) : l(0), r(0), data(n) {}
  inline u32 size() const { return r - l; }

  inline void push(const T &x) { data[r++] = x; }
  inline void pop() { l++; }
  inline const T &get() const { return data[l]; }
  inline void take(T &to) { to = data[l++]; }
};

template <typename Word = u64> struct bitset {
  static const u32 S = sizeof(Word) * 8;
  const u32 n, m;
  array<Word> data;
  bitset(u32 n) : n(n), m((n + S - 1) / S), data(m, 0) {}

  inline u32 size() const { return n; }

  inline bool get(u32 i) const { return (data[i / S] >> (i % S)) & 1; }
  inline void set(u32 i) { data[i / S] |= (Word{1} << (i % S)); }
  inline void filp(u32 i) { data[i / S] ^= (Word{1} << (i % S)); }
};
