#pragma once // include guard
#include "common.hpp"

template <typename T> struct FixedArray {
  u32 sz;
  T *data;
  ~FixedArray() { delete[] data; }
  FixedArray(u32 n) {
    data = new T[sz = n];
    assert(data != nullptr);
  }
  FixedArray(const FixedArray &rhs) {
    sz = rhs.sz;
    data = new T[sz = rhs.sz];
    assert(data != nullptr);
    for (u32 i = 0; i < sz; i++) {
      data[i] = rhs.data[i];
    }
  }
  inline void operator=(const FixedArray &rhs) {
    sz = rhs.sz;
    data = new T[sz = rhs.sz];
    assert(data != nullptr);
    for (u32 i = 0; i < sz; i++) {
      data[i] = rhs.data[i];
    }
  }

  inline u32 size() const { return sz; }
  inline T &operator[](u32 i) { return data[i]; }
  inline const T &operator[](u32 i) const { return data[i]; }
};
template <typename T> struct FixedQueue {
  u32 l, r;
  FixedArray<T> data;
  FixedQueue(int n) : data(n) { l = 0, r = 0; }
  inline u32 size() const { return r - l; }

  inline void push(const T &x) { data[r++] = x; }
  inline void pop() { l++; }
  inline const T &get() const { return data[l]; }
  inline void take(T &to) { to = data[l++]; }
};
