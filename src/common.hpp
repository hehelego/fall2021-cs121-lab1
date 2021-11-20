#pragma once // include guard

#include <cassert>
#include <cstdint>
#include <cstdlib>
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

#ifdef NUM_THREADS
const u32 OMP_THREADS = NUM_THREADS;
#else
const u32 OMP_THREADS = 8;
#endif

template <typename U, typename V> struct tuple2 {
  U x;
  V y;
};
template <typename U, typename V, typename W> struct tuple3 {
  U x;
  V y;
  W z;
};

// debug log
struct debug {
  std::ostream &os;
  debug(std::ostream &os = std::cerr) : os(os) {}

  template <typename T> inline debug &operator<<(const T &t) {
#ifdef DEBUG
    os << t;
#else
    (void)t;
#endif
    return *this;
  }
};

#define REQUIRE(cond)                                                                                        \
  do {                                                                                                       \
    if (!(cond)) {                                                                                           \
      fprintf(stderr, "[REQ_FAILURE](%s:%d) %s", __FILE__, __LINE__, #cond);                                 \
      std::abort();                                                                                          \
    }                                                                                                        \
  } while (0)
