#pragma once // include guard

#include <cassert>
#include <cctype>
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

template <typename Integer> Integer parse_int(Cstr source, u32 start = 0) {
  Integer x = 0, sgn = 1;

  Cstr p = source + start;
  while (*p != '\0' && !isdigit(*p)) {
    if (*p == '-') {
      sgn = -1;
    }
    p++;
  }
  while (*p != '\0' && isdigit(*p)) {
    x = x * 10 + *(p++) - '0';
  }
  return x * sgn;
}
template <typename Integer> Integer parse_uint(Cstr source, u32 start = 0) {
  Integer x = 0;

  Cstr p = source + start;
  while (*p != '\0' && !isdigit(*p)) {
    p++;
  }
  while (*p != '\0' && isdigit(*p)) {
    x = x * 10 + *(p++) - '0';
  }
  return x;
}
