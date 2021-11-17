#pragma once // include guard

#include <cassert>
#include <cstdint>
#include <iostream>

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

// one row in the final BFS output
struct output_row {
  u32 node, distance, parent;
};

// debug log
struct debug {
  std::ostream &os;
  debug(std::ostream &os = std::cerr) : os(os) {}

#ifdef DEBUG
  template <typename T> inline debug &operator<<(const T &t) {
    os << t;
    return *this;
  }
#else
  template <typename T> inline debug &operator<<(const T &) { return *this; }
#endif
};
