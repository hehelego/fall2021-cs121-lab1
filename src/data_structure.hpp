#pragma once // include guard
#include "common.hpp"

template <typename T> struct Queue {
  u32 l, r, n;
  T *data;
  Queue(u32 cap) {
    l = 0, r = 0;
    data = new T[n = cap];
  }
  ~Queue() { delete[] data; }
  inline u32 size() const { return r - l; }

  inline void push(const T &x) { data[r++] = x; }
  inline void pop() { l++; }
  inline const T &get() const { return data[l]; }
  inline void take(T &to) { to = data[l++]; }
};
