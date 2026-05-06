---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: fps/common.hpp
    title: fps/common.hpp
  - icon: ':question:'
    path: fps/common_ntt.hpp
    title: fps/common_ntt.hpp
  - icon: ':question:'
    path: math/convolution.hpp
    title: math/convolution.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Convolution/Bitwise_And_Convolution.test.cpp
    title: test/Library_Checker/Convolution/Bitwise_And_Convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Convolution/Bitwise_Xor_Convolution.test.cpp
    title: test/Library_Checker/Convolution/Bitwise_Xor_Convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Convolution/Convolution_Mod_1097.test.cpp
    title: test/Library_Checker/Convolution/Convolution_Mod_1097.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series.test.cpp
    title: test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series2.test.cpp
    title: test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series2.test.cpp
  - icon: ':x:'
    path: test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series.test.cpp
    title: test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series.test.cpp
  - icon: ':x:'
    path: test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series2.test.cpp
    title: test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series2.test.cpp
  - icon: ':x:'
    path: test/Library_Checker/Polynomial/Log_of_Formal_Power_Series.test.cpp
    title: test/Library_Checker/Polynomial/Log_of_Formal_Power_Series.test.cpp
  - icon: ':x:'
    path: test/Library_Checker/Polynomial/Log_of_Formal_Power_Series2.test.cpp
    title: test/Library_Checker/Polynomial/Log_of_Formal_Power_Series2.test.cpp
  - icon: ':x:'
    path: test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series.test.cpp
    title: test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series.test.cpp
  - icon: ':x:'
    path: test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series2.test.cpp
    title: test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"math/modint_static.hpp\"\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace ayuna {\n\nusing ll = long long;\nusing ull = unsigned long long;\n\
    using u32 = unsigned int;\n\ntemplate <int m> struct modint {\n  using mint =\
    \ modint;\n\nprivate:\n  u32 _v;\n\npublic:\n  constexpr modint() : _v(0) {}\n\
    \  template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  constexpr\
    \ modint(T v) {\n    ll x = (ll)(v % (ll)(m));\n    if(x < 0)\n      x += m;\n\
    \    _v = (u32)(x);\n  }\n\n  u32 val() const { return _v; }\n\n  static constexpr\
    \ u32 mod() { return m; }\n\n  mint &operator++() {\n    _v++;\n    if(_v == m)\n\
    \      _v = 0;\n    return *this;\n  }\n  mint &operator--() {\n    if(_v == 0)\n\
    \      _v = m;\n    _v--;\n    return *this;\n  }\n  mint operator++(int) {\n\
    \    mint result = *this;\n    ++*this;\n    return result;\n  }\n  mint operator--(int)\
    \ {\n    mint result = *this;\n    --*this;\n    return result;\n  }\n\n  mint\
    \ &operator+=(const mint &r) {\n    _v += r._v;\n    if(_v >= m)\n      _v -=\
    \ m;\n    return *this;\n  }\n  mint &operator-=(const mint &r) {\n    _v -= r._v;\n\
    \    if(_v >= m)\n      _v += m;\n    return *this;\n  }\n  mint &operator*=(const\
    \ mint &r) {\n    ull z = _v;\n    z *= r._v;\n    _v = (u32)(z % m);\n    return\
    \ *this;\n  }\n  mint &operator/=(const mint &r) { return *this = *this * r.inv();\
    \ }\n\n  mint operator+() const { return *this; }\n  mint operator-() const {\
    \ return mint() - *this; }\n\n  mint pow(ll n) const {\n    assert(0 <= n);\n\
    \    mint x = *this, r = 1;\n    while(n) {\n      if(n & 1)\n        r *= x;\n\
    \      x *= x;\n      n >>= 1;\n    }\n    return r;\n  }\n  mint inv() const\
    \ {\n    assert(_v);\n    return pow(m - 2);\n  }\n\n  friend mint operator+(const\
    \ mint &l, const mint &r) { return mint(l) += r; }\n  friend mint operator-(const\
    \ mint &l, const mint &r) { return mint(l) -= r; }\n  friend mint operator*(const\
    \ mint &l, const mint &r) { return mint(l) *= r; }\n  friend mint operator/(const\
    \ mint &l, const mint &r) { return mint(l) /= r; }\n  friend bool operator==(const\
    \ mint &l, const mint &r) { return l._v == r._v; }\n  friend bool operator!=(const\
    \ mint &l, const mint &r) { return l._v != r._v; }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const mint &a) {\n    return os << a.val();\n  }\n};\n\nusing modint998244353\
    \ = modint<998244353>;\nusing modint1000000007 = modint<1000000007>;\n\n} // namespace\
    \ ayuna\n"
  code: "#pragma once\n\n#include <cassert>\n#include <iostream>\n#include <numeric>\n\
    #include <type_traits>\n#include <utility>\n\nnamespace ayuna {\n\nusing ll =\
    \ long long;\nusing ull = unsigned long long;\nusing u32 = unsigned int;\n\ntemplate\
    \ <int m> struct modint {\n  using mint = modint;\n\nprivate:\n  u32 _v;\n\npublic:\n\
    \  constexpr modint() : _v(0) {}\n  template <class T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  constexpr modint(T v) {\n    ll x = (ll)(v % (ll)(m));\n    if(x\
    \ < 0)\n      x += m;\n    _v = (u32)(x);\n  }\n\n  u32 val() const { return _v;\
    \ }\n\n  static constexpr u32 mod() { return m; }\n\n  mint &operator++() {\n\
    \    _v++;\n    if(_v == m)\n      _v = 0;\n    return *this;\n  }\n  mint &operator--()\
    \ {\n    if(_v == 0)\n      _v = m;\n    _v--;\n    return *this;\n  }\n  mint\
    \ operator++(int) {\n    mint result = *this;\n    ++*this;\n    return result;\n\
    \  }\n  mint operator--(int) {\n    mint result = *this;\n    --*this;\n    return\
    \ result;\n  }\n\n  mint &operator+=(const mint &r) {\n    _v += r._v;\n    if(_v\
    \ >= m)\n      _v -= m;\n    return *this;\n  }\n  mint &operator-=(const mint\
    \ &r) {\n    _v -= r._v;\n    if(_v >= m)\n      _v += m;\n    return *this;\n\
    \  }\n  mint &operator*=(const mint &r) {\n    ull z = _v;\n    z *= r._v;\n \
    \   _v = (u32)(z % m);\n    return *this;\n  }\n  mint &operator/=(const mint\
    \ &r) { return *this = *this * r.inv(); }\n\n  mint operator+() const { return\
    \ *this; }\n  mint operator-() const { return mint() - *this; }\n\n  mint pow(ll\
    \ n) const {\n    assert(0 <= n);\n    mint x = *this, r = 1;\n    while(n) {\n\
    \      if(n & 1)\n        r *= x;\n      x *= x;\n      n >>= 1;\n    }\n    return\
    \ r;\n  }\n  mint inv() const {\n    assert(_v);\n    return pow(m - 2);\n  }\n\
    \n  friend mint operator+(const mint &l, const mint &r) { return mint(l) += r;\
    \ }\n  friend mint operator-(const mint &l, const mint &r) { return mint(l) -=\
    \ r; }\n  friend mint operator*(const mint &l, const mint &r) { return mint(l)\
    \ *= r; }\n  friend mint operator/(const mint &l, const mint &r) { return mint(l)\
    \ /= r; }\n  friend bool operator==(const mint &l, const mint &r) { return l._v\
    \ == r._v; }\n  friend bool operator!=(const mint &l, const mint &r) { return\
    \ l._v != r._v; }\n  friend std::ostream &operator<<(std::ostream &os, const mint\
    \ &a) {\n    return os << a.val();\n  }\n};\n\nusing modint998244353 = modint<998244353>;\n\
    using modint1000000007 = modint<1000000007>;\n\n} // namespace ayuna\n"
  dependsOn: []
  isVerificationFile: false
  path: math/modint_static.hpp
  requiredBy:
  - math/convolution.hpp
  - fps/common_ntt.hpp
  - fps/common.hpp
  timestamp: '2026-05-07 00:37:36+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/Library_Checker/Convolution/Bitwise_Xor_Convolution.test.cpp
  - test/Library_Checker/Convolution/Bitwise_And_Convolution.test.cpp
  - test/Library_Checker/Convolution/Convolution_Mod_1097.test.cpp
  - test/Library_Checker/Polynomial/Log_of_Formal_Power_Series2.test.cpp
  - test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Log_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series2.test.cpp
  - test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series2.test.cpp
  - test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series2.test.cpp
documentation_of: math/modint_static.hpp
layout: document
redirect_from:
- /library/math/modint_static.hpp
- /library/math/modint_static.hpp.html
title: math/modint_static.hpp
---
