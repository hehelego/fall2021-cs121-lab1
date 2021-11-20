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
  T *data;
  ~array() { delete[] data; }
  array(u32 n=0) : n(n), data(new T[n]) {}
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
  void set_all(const T &val) {
    for (u32 i = 0; i < n; i++) data[i] = val;
  }

  inline view<T> slice(u32 start, u32 len) const {
    assert(start + len <= n);
    return view<T>(data, start, len);
  }
};
template <typename T> struct list {
  struct list_node {
    T val;
    list_node *next;
    list_node(const T &v) : val(v), next(nullptr) {}
  } * h, *t;
  struct iterator {
    list_node *ptr;
    void operator++() { ptr = ptr->next; }
    inline operator bool() const { return ptr; }
  };
  list() : h(nullptr), t(nullptr) {}
  ~list() {
    while (!empty()) { pop(); }
  }
  inline iterator *iter() const { return iterator{h}; }
  inline bool empty() const { return h == nullptr; }
  inline const T &head() const { return h->val; }
  inline void push(const T &val) {
    if (t) {
      t->next = new list_node{val};
      t = t->next;
    } else {
      h = t = new list_node{val};
    }
  }
  inline void pop() {
    if (h) {
      auto hh = h->next;
      delete[] h;
      h = hh, t = hh ? t : nullptr;
    }
  }
  inline void join(list &l) {
    if (l.empty()) { return; }
    if (empty()) {
      h = l.h, t = l.t;
      l.h = l.t = nullptr;
    } else {
      t->next = l.h, t->l.t;
    }
  }
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
