#include <cassert>
#include <cstdint>

// the rust-style type alias
//
// arithemetic types
using i8 = std::int8_t;
using u8 = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
using f32 = float;
using f64 = double;
// string types
using Cstr = const char *;

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

  void push(const T &x) { data[r++] = x; }
  void pop() { l++; }
  const T &get() const { return data[l]; }
};
