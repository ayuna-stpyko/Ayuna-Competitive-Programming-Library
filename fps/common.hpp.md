---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/convolution.hpp
    title: math/convolution.hpp
  - icon: ':question:'
    path: math/modint_static.hpp
    title: math/modint_static.hpp
  _extendedRequiredBy:
  - icon: ':question:'
    path: fps/common_ntt.hpp
    title: fps/common_ntt.hpp
  _extendedVerifiedWith:
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
  bundledCode: "#line 2 \"fps/common.hpp\"\n\n#line 2 \"math/convolution.hpp\"\n\n\
    #line 2 \"math/modint_static.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <numeric>\n#include <type_traits>\n#include <utility>\n\nnamespace ayuna\
    \ {\n\nusing ll = long long;\nusing ull = unsigned long long;\nusing u32 = unsigned\
    \ int;\n\ntemplate <int m> struct modint {\n  using mint = modint;\n\nprivate:\n\
    \  u32 _v;\n\npublic:\n  constexpr modint() : _v(0) {}\n  template <class T, std::enable_if_t<std::is_integral_v<T>,\
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
    using modint1000000007 = modint<1000000007>;\n\n} // namespace ayuna\n#line 4\
    \ \"math/convolution.hpp\"\n#include <algorithm>\n#include <array>\n#include <bit>\n\
    #line 8 \"math/convolution.hpp\"\n#include <concepts>\n#line 11 \"math/convolution.hpp\"\
    \n#include <vector>\n\nnamespace ayuna {\n\nconstexpr long long safe_mod(long\
    \ long x, long long m) {\n  x %= m;\n  if(x < 0)\n    x += m;\n  return x;\n}\n\
    \nconstexpr long long pow_mod_constexpr(long long x, long long n, int m) {\n \
    \ if(m == 1)\n    return 0;\n  unsigned int _m = (unsigned int)(m);\n  unsigned\
    \ long long r = 1;\n  unsigned long long y = safe_mod(x, m);\n  while(n) {\n \
    \   if(n & 1)\n      r = (r * y) % _m;\n    y = (y * y) % _m;\n    n >>= 1;\n\
    \  }\n  return r;\n}\n\nconstexpr int primitive_root_constexpr(int m) {\n  if(m\
    \ == 2)\n    return 1;\n  if(m == 167772161)\n    return 3;\n  if(m == 469762049)\n\
    \    return 3;\n  if(m == 754974721)\n    return 11;\n  if(m == 998244353)\n \
    \   return 3;\n  int divs[20] = {};\n  divs[0] = 2;\n  int cnt = 1;\n  int x =\
    \ (m - 1) / 2;\n  while(x % 2 == 0)\n    x >>= 1;\n  for(int i = 3; (long long)(i)*i\
    \ <= x; i += 2) {\n    if(x % i == 0) {\n      divs[cnt++] = i;\n      while(x\
    \ % i == 0)\n        x /= i;\n    }\n  }\n  if(x > 1)\n    divs[cnt++] = x;\n\
    \  for(int g = 2;; g++) {\n    bool ok = true;\n    for(int i = 0; i < cnt; i++)\
    \ {\n      if(pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n        ok =\
    \ false;\n        break;\n      }\n    }\n    if(ok)\n      return g;\n  }\n}\n\
    template <int m> constexpr int primitive_root = primitive_root_constexpr(m);\n\
    \ntemplate <class T>\nconcept StaticModint = requires(T a, T b, long long n) {\n\
    \  std::integral_constant<decltype(T::mod()), T::mod()>{};\n  { a + b } -> std::same_as<T>;\n\
    \  { a - b } -> std::same_as<T>;\n  { a *b } -> std::same_as<T>;\n  { a.val()\
    \ } -> std::convertible_to<unsigned int>;\n  { a.inv() } -> std::same_as<T>;\n\
    \  { a.pow(n) } -> std::same_as<T>;\n  T{1};\n};\n\ntemplate <StaticModint mint,\
    \ int g = primitive_root<(int)mint::mod()>>\nstruct fft_info {\n  static constexpr\
    \ int rank2 =\n      std::countr_zero((unsigned int)(mint::mod() - 1));\n  std::array<mint,\
    \ rank2 + 1> root;\n  std::array<mint, rank2 + 1> iroot;\n  std::array<mint, std::max(0,\
    \ rank2 - 1)> rate2;\n  std::array<mint, std::max(0, rank2 - 1)> irate2;\n  std::array<mint,\
    \ std::max(0, rank2 - 2)> rate3;\n  std::array<mint, std::max(0, rank2 - 2)> irate3;\n\
    \n  fft_info() {\n    root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);\n\
    \    iroot[rank2] = root[rank2].inv();\n    for(int i = rank2 - 1; i >= 0; i--)\
    \ {\n      root[i] = root[i + 1] * root[i + 1];\n      iroot[i] = iroot[i + 1]\
    \ * iroot[i + 1];\n    }\n    {\n      mint prod = 1, iprod = 1;\n      for(int\
    \ i = 0; i <= rank2 - 2; i++) {\n        rate2[i] = root[i + 2] * prod;\n    \
    \    irate2[i] = iroot[i + 2] * iprod;\n        prod *= iroot[i + 2];\n      \
    \  iprod *= root[i + 2];\n      }\n    }\n    {\n      mint prod = 1, iprod =\
    \ 1;\n      for(int i = 0; i <= rank2 - 3; i++) {\n        rate3[i] = root[i +\
    \ 3] * prod;\n        irate3[i] = iroot[i + 3] * iprod;\n        prod *= iroot[i\
    \ + 3];\n        iprod *= root[i + 3];\n      }\n    }\n  }\n};\n\ntemplate <StaticModint\
    \ mint> void butterfly(std::vector<mint> &a) {\n  const int n = int(a.size());\n\
    \  const int h = std::countr_zero((unsigned int)n);\n  static const fft_info<mint>\
    \ info;\n  int len = 0;\n  while(len < h) {\n    if(h - len == 1) {\n      int\
    \ p = 1 << (h - len - 1);\n      mint rot = 1;\n      for(int s = 0; s < (1 <<\
    \ len); s++) {\n        int offset = s << (h - len);\n        for(int i = 0; i\
    \ < p; i++) {\n          auto l = a[i + offset];\n          auto r = a[i + offset\
    \ + p] * rot;\n          a[i + offset] = l + r;\n          a[i + offset + p] =\
    \ l - r;\n        }\n        if(s + 1 != (1 << len))\n          rot *= info.rate2[std::countr_zero(~(unsigned\
    \ int)(s))];\n      }\n      len++;\n    }\n\t\telse {\n      if constexpr(fft_info<mint>::rank2\
    \ >= 2) {\n        // 4-base\n        int p = 1 << (h - len - 2);\n        mint\
    \ rot = 1, imag = info.root[2];\n        for(int s = 0; s < (1 << len); s++) {\n\
    \          mint rot2 = rot * rot, rot3 = rot2 * rot;\n          int offset = s\
    \ << (h - len);\n          for(int i = 0; i < p; i++) {\n            auto mod2\
    \ = 1ULL * mint::mod() * mint::mod();\n            auto a0 = 1ULL * a[i + offset].val();\n\
    \            auto a1 = 1ULL * a[i + offset + p].val() * rot.val();\n         \
    \   auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();\n            auto\
    \ a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();\n            auto a1na3imag\
    \ = 1ULL * mint(a1 + mod2 - a3).val() * imag.val();\n            auto na2 = mod2\
    \ - a2;\n            a[i + offset] = a0 + a2 + a1 + a3;\n            a[i + offset\
    \ + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));\n            a[i + offset + 2 *\
    \ p] = a0 + na2 + a1na3imag;\n            a[i + offset + 3 * p] = a0 + na2 + (mod2\
    \ - a1na3imag);\n          }\n          if(s + 1 != (1 << len))\n            rot\
    \ *= info.rate3[std::countr_zero(~(unsigned int)(s))];\n        }\n        len\
    \ += 2;\n      }\n\t\t\telse {\n        assert(false && \"butterfly: rank2 too\
    \ small for 4-base NTT\");\n      }\n    }\n  }\n}\n\ntemplate <StaticModint mint>\
    \ void butterfly_inv(std::vector<mint> &a) {\n  const int n = int(a.size());\n\
    \  const int h = std::countr_zero((unsigned int)n);\n  static const fft_info<mint>\
    \ info;\n  int len = h;\n  while(len) {\n    if(len == 1) {\n      int p = 1 <<\
    \ (h - len);\n      mint irot = 1;\n      for(int s = 0; s < (1 << (len - 1));\
    \ s++) {\n        int offset = s << (h - len + 1);\n        for(int i = 0; i <\
    \ p; i++) {\n          auto l = a[i + offset];\n          auto r = a[i + offset\
    \ + p];\n          a[i + offset] = l + r;\n          a[i + offset + p] =\n   \
    \           (unsigned long long)(mint::mod() + l.val() - r.val()) *\n        \
    \      irot.val();\n        }\n        if(s + 1 != (1 << (len - 1)))\n       \
    \   irot *= info.irate2[std::countr_zero(~(unsigned int)(s))];\n      }\n    \
    \  len--;\n    }\n\t\telse {\n      if constexpr(fft_info<mint>::rank2 >= 2) {\n\
    \        // 4-base\n        int p = 1 << (h - len);\n        mint irot = 1, iimag\
    \ = info.iroot[2];\n        for(int s = 0; s < (1 << (len - 2)); s++) {\n    \
    \      mint irot2 = irot * irot, irot3 = irot2 * irot;\n          int offset =\
    \ s << (h - len + 2);\n          for(int i = 0; i < p; i++) {\n            auto\
    \ a0 = 1ULL * a[i + offset + 0 * p].val();\n            auto a1 = 1ULL * a[i +\
    \ offset + 1 * p].val();\n            auto a2 = 1ULL * a[i + offset + 2 * p].val();\n\
    \            auto a3 = 1ULL * a[i + offset + 3 * p].val();\n            auto a2na3iimag\
    \ =\n                1ULL * mint((mint::mod() + a2 - a3) * iimag.val()).val();\n\
    \            a[i + offset] = a0 + a1 + a2 + a3;\n            a[i + offset + 1\
    \ * p] =\n                (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();\n\
    \            a[i + offset + 2 * p] =\n                (a0 + a1 + (mint::mod()\
    \ - a2) + (mint::mod() - a3)) *\n                irot2.val();\n            a[i\
    \ + offset + 3 * p] =\n                (a0 + (mint::mod() - a1) + (mint::mod()\
    \ - a2na3iimag)) *\n                irot3.val();\n          }\n          if(s\
    \ + 1 != (1 << (len - 2)))\n            irot *= info.irate3[std::countr_zero(~(unsigned\
    \ int)(s))];\n        }\n        len -= 2;\n      }\n\t\t\telse {\n        assert(false\
    \ && \"butterfly_inv: rank2 too small for 4-base NTT\");\n      }\n    }\n  }\n\
    }\n\ntemplate <StaticModint mint>\nstd::vector<mint> convolution_naive(const std::vector<mint>\
    \ &a,\n                                    const std::vector<mint> &b) {\n  const\
    \ int n = int(a.size()), m = int(b.size());\n  std::vector<mint> ans(n + m - 1);\n\
    \  for(int j = 0; j < m; j++)\n    for(int i = 0; i < n; i++)\n      ans[i + j]\
    \ += a[i] * b[j];\n  return ans;\n}\n\ntemplate <StaticModint mint>\nstd::vector<mint>\
    \ convolution_fft(std::vector<mint> a, std::vector<mint> b) {\n  const int n =\
    \ int(a.size()), m = int(b.size());\n  if(!n || !m)\n    return {};\n  int z =\
    \ (int)std::bit_ceil((unsigned int)(n + m - 1));\n  a.resize(z);\n  ayuna::butterfly(a);\n\
    \  b.resize(z);\n  ayuna::butterfly(b);\n  for(int i = 0; i < z; i++)\n    a[i]\
    \ *= b[i];\n  ayuna::butterfly_inv(a);\n  a.resize(n + m - 1);\n  mint iz = mint(z).inv();\n\
    \  for(int i = 0; i < n + m - 1; i++)\n    a[i] *= iz;\n  return a;\n}\n\ntemplate\
    \ <StaticModint mint>\nstatic std::vector<mint> convolution_arbitrary_mod(const\
    \ std::vector<mint> &a,\n                                                   const\
    \ std::vector<mint> &b) {\n  using m1 = modint<167772161>;  // 2^25 * 5 + 1\n\
    \  using m2 = modint<469762049>;  // 2^26 * 7 + 1\n  using m3 = modint<1224736769>;\
    \ // 2^24 * 73 + 1\n  static_assert(StaticModint<m1>);\n  static_assert(StaticModint<m2>);\n\
    \  static_assert(StaticModint<m3>);\n\n  const int n = (int)a.size(), m = (int)b.size();\n\
    \  std::vector<m1> a1(n), b1(m);\n  std::vector<m2> a2(n), b2(m);\n  std::vector<m3>\
    \ a3(n), b3(m);\n  for(int i = 0; i < n; i++) {\n    const unsigned int v = a[i].val();\n\
    \    a1[i] = v;\n    a2[i] = v;\n    a3[i] = v;\n  }\n  for(int i = 0; i < m;\
    \ i++) {\n    const unsigned int v = b[i].val();\n    b1[i] = v;\n    b2[i] =\
    \ v;\n    b3[i] = v;\n  }\n\n  const auto c1 = ayuna::convolution_fft(std::move(a1),\
    \ std::move(b1));\n  const auto c2 = ayuna::convolution_fft(std::move(a2), std::move(b2));\n\
    \  const auto c3 = ayuna::convolution_fft(std::move(a3), std::move(b3));\n\n \
    \ static constexpr unsigned long long M1 = m1::mod();\n  static constexpr unsigned\
    \ long long M2 = m2::mod();\n  static constexpr unsigned long long M1M2 = M1 *\
    \ M2;\n\n  static const m2 inv_m1_mod_m2 = m2(M1).inv();\n  static const m3 inv_m1m2_mod_m3\
    \ = m3(M1M2).inv();\n\n  const int sz = n + m - 1;\n  std::vector<mint> res(sz);\n\
    \  for(int i = 0; i < sz; i++) {\n    const unsigned long long x1 = c1[i].val();\n\
    \    const unsigned long long x2 = c2[i].val();\n    const unsigned long long\
    \ x3 = c3[i].val();\n\n    const unsigned long long t1 = x1;\n    const unsigned\
    \ long long t2 =\n        (unsigned long long)(m2((long long)x2 - (long long)t1)\
    \ * inv_m1_mod_m2)\n            .val();\n    const unsigned long long t3 =\n \
    \       (unsigned long long)(m3((long long)x3 -\n                            \
    \    (long long)(m3(t1 + M1 * t2).val())) *\n                             inv_m1m2_mod_m3)\n\
    \            .val();\n\n    const unsigned long long mod = mint::mod();\n    const\
    \ unsigned long long term1 = t1 % mod;\n    const unsigned long long term2 = (M1\
    \ % mod) * (t2 % mod) % mod;\n    const unsigned long long term3 = (M1M2 % mod)\
    \ * (t3 % mod) % mod;\n    res[i] = mint((term1 + term2 + term3) % mod);\n  }\n\
    \  return res;\n}\n\ntemplate <StaticModint mint>\nstd::vector<mint> convolution(std::vector<mint>\
    \ &&a, std::vector<mint> &&b) {\n  const int n = int(a.size()), m = int(b.size());\n\
    \  if(!n || !m)\n    return {};\n  const int z = (int)std::bit_ceil((unsigned\
    \ int)(n + m - 1));\n  if(std::min(n, m) <= 60)\n    return ayuna::convolution_naive(a,\
    \ b);\n  if((mint::mod() - 1) % z == 0)\n    return ayuna::convolution_fft(std::move(a),\
    \ std::move(b));\n  return ayuna::convolution_arbitrary_mod<mint>(a, b);\n}\n\n\
    // -------------------------\n// Bitwise Convolutions (FWT)\n// -------------------------\n\
    \ntemplate <StaticModint mint>\nstatic void hadamard_transform(std::vector<mint>\
    \ &a) {\n  const int n = (int)a.size();\n  for(int len = 1; len < n; len <<= 1)\
    \ {\n    for(int i = 0; i < n; i += (len << 1)) {\n      for(int j = 0; j < len;\
    \ j++) {\n        const mint u = a[i + j];\n        const mint v = a[i + j + len];\n\
    \        a[i + j] = u + v;\n        a[i + j + len] = u - v;\n      }\n    }\n\
    \  }\n}\n\ntemplate <StaticModint mint>\nstatic void hadamard_transform_inv(std::vector<mint>\
    \ &a) {\n  hadamard_transform(a);\n  const mint inv_n = mint((int)a.size()).inv();\n\
    \  for(auto &x : a)\n    x *= inv_n;\n}\n\ntemplate <StaticModint mint>\nstd::vector<mint>\
    \ xor_convolution(std::vector<mint> a, std::vector<mint> b) {\n  const int n =\
    \ (int)a.size();\n  assert(n == (int)b.size());\n  if(n == 0)\n    return {};\n\
    \  assert(std::has_single_bit((unsigned int)n));\n  hadamard_transform(a);\n \
    \ hadamard_transform(b);\n  for(int i = 0; i < n; i++)\n    a[i] *= b[i];\n  hadamard_transform_inv(a);\n\
    \  return a;\n}\n\ntemplate <StaticModint mint>\nstatic void and_transform(std::vector<mint>\
    \ &a) {\n  const int n = (int)a.size();\n  for(int len = 1; len < n; len <<= 1)\
    \ {\n    for(int i = 0; i < n; i += (len << 1)) {\n      for(int j = 0; j < len;\
    \ j++) {\n        // f[S] += f[S \\ {bit}]\n        a[i + j] += a[i + j + len];\n\
    \      }\n    }\n  }\n}\n\ntemplate <StaticModint mint>\nstatic void and_transform_inv(std::vector<mint>\
    \ &a) {\n  const int n = (int)a.size();\n  for(int len = 1; len < n; len <<= 1)\
    \ {\n    for(int i = 0; i < n; i += (len << 1)) {\n      for(int j = 0; j < len;\
    \ j++) {\n        a[i + j] -= a[i + j + len];\n      }\n    }\n  }\n}\n\ntemplate\
    \ <StaticModint mint>\nstd::vector<mint> and_convolution(std::vector<mint> a,\
    \ std::vector<mint> b) {\n  const int n = (int)a.size();\n  assert(n == (int)b.size());\n\
    \  if(n == 0)\n    return {};\n  assert(std::has_single_bit((unsigned int)n));\n\
    \  and_transform(a);\n  and_transform(b);\n  for(int i = 0; i < n; i++)\n    a[i]\
    \ *= b[i];\n  and_transform_inv(a);\n  return a;\n}\n\ntemplate <StaticModint\
    \ mint>\nstatic void or_transform(std::vector<mint> &a) {\n  const int n = (int)a.size();\n\
    \  for(int len = 1; len < n; len <<= 1) {\n    for(int i = 0; i < n; i += (len\
    \ << 1)) {\n      for(int j = 0; j < len; j++) {\n        // f[S \u222A {bit}]\
    \ += f[S]\n        a[i + j + len] += a[i + j];\n      }\n    }\n  }\n}\n\ntemplate\
    \ <StaticModint mint>\nstatic void or_transform_inv(std::vector<mint> &a) {\n\
    \  const int n = (int)a.size();\n  for(int len = 1; len < n; len <<= 1) {\n  \
    \  for(int i = 0; i < n; i += (len << 1)) {\n      for(int j = 0; j < len; j++)\
    \ {\n        a[i + j + len] -= a[i + j];\n      }\n    }\n  }\n}\n\ntemplate <StaticModint\
    \ mint>\nstd::vector<mint> or_convolution(std::vector<mint> a, std::vector<mint>\
    \ b) {\n  const int n = (int)a.size();\n  assert(n == (int)b.size());\n  if(n\
    \ == 0)\n    return {};\n  assert(std::has_single_bit((unsigned int)n));\n  or_transform(a);\n\
    \  or_transform(b);\n  for(int i = 0; i < n; i++)\n    a[i] *= b[i];\n  or_transform_inv(a);\n\
    \  return a;\n}\n\n} // namespace ayuna\n#line 7 \"fps/common.hpp\"\n#include\
    \ <iterator>\n#line 11 \"fps/common.hpp\"\n\nnamespace ayuna {\n\ntemplate <typename\
    \ mint, class Derived>\nstruct FormalPowerSeriesBase : std::vector<mint> {\n \
    \ using std::vector<mint>::vector;\n  using FPS = Derived;\n\n  FPS &self() {\
    \ return static_cast<FPS &>(*this); }\n  const FPS &self() const { return static_cast<const\
    \ FPS &>(*this); }\n\n  FPS &operator+=(const FPS &r) {\n    if(r.size() > this->size())\n\
    \      this->resize(r.size());\n    for(int i = 0; i < (int)r.size(); i++)\n \
    \     (*this)[i] += r[i];\n    return self();\n  }\n\n  FPS &operator+=(const\
    \ mint &r) {\n    if(this->empty())\n      this->resize(1);\n    (*this)[0] +=\
    \ r;\n    return self();\n  }\n\n  FPS &operator-=(const FPS &r) {\n    if(r.size()\
    \ > this->size())\n      this->resize(r.size());\n    for(int i = 0; i < (int)r.size();\
    \ i++)\n      (*this)[i] -= r[i];\n    return self();\n  }\n\n  FPS &operator*=(const\
    \ mint &v) {\n    for(int k = 0; k < (int)this->size(); k++)\n      (*this)[k]\
    \ *= v;\n    return self();\n  }\n\n  FPS &operator-=(const mint &r) {\n    if(this->empty())\n\
    \      this->resize(1);\n    (*this)[0] -= r;\n    return self();\n  }\n\n  FPS\
    \ &operator/=(const FPS &r) {\n    if(this->size() < r.size()) {\n      this->clear();\n\
    \      return self();\n    }\n    int n = this->size() - r.size() + 1;\n    if((int)r.size()\
    \ <= 64) {\n      FPS f(self()), g(std::begin(r), std::end(r));\n      g.shrink();\n\
    \      mint coeff = g.back().inv();\n      for(auto &x : g)\n        x *= coeff;\n\
    \      int deg = (int)f.size() - (int)g.size() + 1;\n      int gs = g.size();\n\
    \      FPS quo(deg);\n      for(int i = deg - 1; i >= 0; i--) {\n        quo[i]\
    \ = f[i + gs - 1];\n        for(int j = 0; j < gs; j++)\n          f[i + j] -=\
    \ quo[i] * g[j];\n      }\n      *this = quo * coeff;\n      this->resize(n, mint(0));\n\
    \      return self();\n    }\n    FPS rr(std::begin(r), std::end(r));\n    return\
    \ *this = (self().rev().pre(n) * rr.rev().inv(n)).pre(n).rev();\n  }\n\n  FPS\
    \ &operator%=(const FPS &r) {\n    *this -= *this / r * r;\n    shrink();\n  \
    \  return self();\n  }\n\n  FPS operator+(const FPS &r) const { return FPS(self())\
    \ += r; }\n  FPS operator+(const mint &v) const { return FPS(self()) += v; }\n\
    \  FPS operator-(const FPS &r) const { return FPS(self()) -= r; }\n  FPS operator-(const\
    \ mint &v) const { return FPS(self()) -= v; }\n  FPS operator*(const mint &v)\
    \ const { return FPS(self()) *= v; }\n  FPS operator/(const FPS &r) const { return\
    \ FPS(self()) /= r; }\n  FPS operator%(const FPS &r) const { return FPS(self())\
    \ %= r; }\n  FPS operator-() const {\n    FPS ret(this->size());\n    for(int\
    \ i = 0; i < (int)this->size(); i++)\n      ret[i] = -(*this)[i];\n    return\
    \ ret;\n  }\n\n  void shrink() {\n    while(this->size() && this->back() == mint(0))\n\
    \      this->pop_back();\n  }\n\n  FPS rev() const {\n    FPS ret(self());\n \
    \   reverse(begin(ret), end(ret));\n    return ret;\n  }\n\n  FPS dot(const FPS\
    \ &r) const {\n    FPS ret(std::min(this->size(), r.size()));\n    for(int i =\
    \ 0; i < (int)ret.size(); i++)\n      ret[i] = (*this)[i] * r[i];\n    return\
    \ ret;\n  }\n\n  FPS pre(int sz) const {\n    FPS ret(begin(*this), begin(*this)\
    \ + std::min((int)this->size(), sz));\n    if((int)ret.size() < sz)\n      ret.resize(sz);\n\
    \    return ret;\n  }\n\n  FPS operator>>(int sz) const {\n    if((int)this->size()\
    \ <= sz)\n      return {};\n    FPS ret(self());\n    ret.erase(ret.begin(), ret.begin()\
    \ + sz);\n    return ret;\n  }\n\n  FPS operator<<(int sz) const {\n    FPS ret(self());\n\
    \    ret.insert(ret.begin(), sz, mint(0));\n    return ret;\n  }\n\n  FPS diff()\
    \ const {\n    const int n = (int)this->size();\n    FPS ret(std::max(0, n - 1));\n\
    \    const mint one(1);\n    mint coeff(1);\n    for(int i = 1; i < n; i++) {\n\
    \      ret[i - 1] = (*this)[i] * coeff;\n      coeff += one;\n    }\n    return\
    \ ret;\n  }\n\n  FPS inv(int deg = -1) const {\n    assert((*this)[0] != mint(0));\n\
    \    if(deg == -1)\n      deg = (*this).size();\n    FPS ret({mint(1) / (*this)[0]});\n\
    \    for(int i = 1; i < deg; i <<= 1)\n      ret = (ret + ret - ret * ret * (*this).pre(i\
    \ << 1)).pre(i << 1);\n    return ret.pre(deg);\n  }\n\n  FPS integral() const\
    \ {\n    const int n = (int)this->size();\n    FPS ret(n + 1);\n    ret[0] = mint(0);\n\
    \    if(n > 0)\n      ret[1] = mint(1);\n    const auto mod = mint::mod();\n \
    \   for(int i = 2; i <= n; i++)\n      ret[i] = (-ret[mod % i]) * (mod / i);\n\
    \    for(int i = 0; i < n; i++)\n      ret[i + 1] *= (*this)[i];\n    return ret;\n\
    \  }\n\n  mint eval(mint x) const {\n    mint r = 0, w = 1;\n    for(auto &v :\
    \ *this)\n      r += w * v, w *= x;\n    return r;\n  }\n\n  FPS log(int deg =\
    \ -1) const {\n    assert(!(*this).empty() && (*this)[0] == mint(1));\n    assert(deg);\n\
    \    if(deg == -1)\n      deg = (int)this->size();\n    return (this->diff() *\
    \ this->inv(deg)).pre(deg - 1).integral();\n  }\n\n  FPS exp(int deg = -1) const\
    \ {\n    assert((*this).size() == 0 || (*this)[0] == mint(0));\n    if(deg ==\
    \ -1)\n      deg = (int)this->size();\n    FPS ret({mint(1)});\n    for(int i\
    \ = 1; i < deg; i <<= 1) {\n      ret = (ret * (pre(i << 1) + mint(1) - ret.log(i\
    \ << 1))).pre(i << 1);\n    }\n    return ret.pre(deg);\n  }\n\n  FPS pow(int64_t\
    \ k, int deg = -1) const {\n    const int n = (int)this->size();\n    if(deg ==\
    \ -1)\n      deg = n;\n    if(k == 0) {\n      FPS ret(deg);\n      if(deg)\n\
    \        ret[0] = 1;\n      return ret;\n    }\n    for(int i = 0; i < n; i++)\
    \ {\n      if((*this)[i] != mint(0)) {\n        mint rev = mint(1) / (*this)[i];\n\
    \        FPS ret = (((*this * rev) >> i).log(deg) * k).exp(deg);\n        ret\
    \ *= (*this)[i].pow(k);\n        ret = (ret << (i * k)).pre(deg);\n        if((int)ret.size()\
    \ < deg)\n          ret.resize(deg, mint(0));\n        return ret;\n      }\n\
    \      if(__int128_t(i + 1) * k >= deg)\n        return FPS(deg, mint(0));\n \
    \   }\n    return FPS(deg, mint(0));\n  }\n};\n\ntemplate <typename mint>\nstruct\
    \ FormalPowerSeries\n    : FormalPowerSeriesBase<mint, FormalPowerSeries<mint>>\
    \ {\n  using Base = FormalPowerSeriesBase<mint, FormalPowerSeries<mint>>;\n  using\
    \ Base::Base;\n  using FPS = FormalPowerSeries;\n  using Base::operator*=;\n \
    \ using Base::operator*;\n\n  FPS &operator*=(const FPS &r) {\n    if(this->empty()\
    \ || r.empty()) {\n      this->clear();\n      return *this;\n    }\n    auto\
    \ result = ayuna::convolution(std::vector<mint>(*this), std::vector<mint>(r));\n\
    \    this->assign(result.begin(), result.end());\n    return *this;\n  }\n\n \
    \ FPS operator*(const FPS &r) const { return FPS(*this) *= r; }\n};\n\n} // namespace\
    \ ayuna\n"
  code: "#pragma once\n\n#include \"../math/convolution.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <iterator>\n#include <numeric>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace ayuna {\n\ntemplate <typename\
    \ mint, class Derived>\nstruct FormalPowerSeriesBase : std::vector<mint> {\n \
    \ using std::vector<mint>::vector;\n  using FPS = Derived;\n\n  FPS &self() {\
    \ return static_cast<FPS &>(*this); }\n  const FPS &self() const { return static_cast<const\
    \ FPS &>(*this); }\n\n  FPS &operator+=(const FPS &r) {\n    if(r.size() > this->size())\n\
    \      this->resize(r.size());\n    for(int i = 0; i < (int)r.size(); i++)\n \
    \     (*this)[i] += r[i];\n    return self();\n  }\n\n  FPS &operator+=(const\
    \ mint &r) {\n    if(this->empty())\n      this->resize(1);\n    (*this)[0] +=\
    \ r;\n    return self();\n  }\n\n  FPS &operator-=(const FPS &r) {\n    if(r.size()\
    \ > this->size())\n      this->resize(r.size());\n    for(int i = 0; i < (int)r.size();\
    \ i++)\n      (*this)[i] -= r[i];\n    return self();\n  }\n\n  FPS &operator*=(const\
    \ mint &v) {\n    for(int k = 0; k < (int)this->size(); k++)\n      (*this)[k]\
    \ *= v;\n    return self();\n  }\n\n  FPS &operator-=(const mint &r) {\n    if(this->empty())\n\
    \      this->resize(1);\n    (*this)[0] -= r;\n    return self();\n  }\n\n  FPS\
    \ &operator/=(const FPS &r) {\n    if(this->size() < r.size()) {\n      this->clear();\n\
    \      return self();\n    }\n    int n = this->size() - r.size() + 1;\n    if((int)r.size()\
    \ <= 64) {\n      FPS f(self()), g(std::begin(r), std::end(r));\n      g.shrink();\n\
    \      mint coeff = g.back().inv();\n      for(auto &x : g)\n        x *= coeff;\n\
    \      int deg = (int)f.size() - (int)g.size() + 1;\n      int gs = g.size();\n\
    \      FPS quo(deg);\n      for(int i = deg - 1; i >= 0; i--) {\n        quo[i]\
    \ = f[i + gs - 1];\n        for(int j = 0; j < gs; j++)\n          f[i + j] -=\
    \ quo[i] * g[j];\n      }\n      *this = quo * coeff;\n      this->resize(n, mint(0));\n\
    \      return self();\n    }\n    FPS rr(std::begin(r), std::end(r));\n    return\
    \ *this = (self().rev().pre(n) * rr.rev().inv(n)).pre(n).rev();\n  }\n\n  FPS\
    \ &operator%=(const FPS &r) {\n    *this -= *this / r * r;\n    shrink();\n  \
    \  return self();\n  }\n\n  FPS operator+(const FPS &r) const { return FPS(self())\
    \ += r; }\n  FPS operator+(const mint &v) const { return FPS(self()) += v; }\n\
    \  FPS operator-(const FPS &r) const { return FPS(self()) -= r; }\n  FPS operator-(const\
    \ mint &v) const { return FPS(self()) -= v; }\n  FPS operator*(const mint &v)\
    \ const { return FPS(self()) *= v; }\n  FPS operator/(const FPS &r) const { return\
    \ FPS(self()) /= r; }\n  FPS operator%(const FPS &r) const { return FPS(self())\
    \ %= r; }\n  FPS operator-() const {\n    FPS ret(this->size());\n    for(int\
    \ i = 0; i < (int)this->size(); i++)\n      ret[i] = -(*this)[i];\n    return\
    \ ret;\n  }\n\n  void shrink() {\n    while(this->size() && this->back() == mint(0))\n\
    \      this->pop_back();\n  }\n\n  FPS rev() const {\n    FPS ret(self());\n \
    \   reverse(begin(ret), end(ret));\n    return ret;\n  }\n\n  FPS dot(const FPS\
    \ &r) const {\n    FPS ret(std::min(this->size(), r.size()));\n    for(int i =\
    \ 0; i < (int)ret.size(); i++)\n      ret[i] = (*this)[i] * r[i];\n    return\
    \ ret;\n  }\n\n  FPS pre(int sz) const {\n    FPS ret(begin(*this), begin(*this)\
    \ + std::min((int)this->size(), sz));\n    if((int)ret.size() < sz)\n      ret.resize(sz);\n\
    \    return ret;\n  }\n\n  FPS operator>>(int sz) const {\n    if((int)this->size()\
    \ <= sz)\n      return {};\n    FPS ret(self());\n    ret.erase(ret.begin(), ret.begin()\
    \ + sz);\n    return ret;\n  }\n\n  FPS operator<<(int sz) const {\n    FPS ret(self());\n\
    \    ret.insert(ret.begin(), sz, mint(0));\n    return ret;\n  }\n\n  FPS diff()\
    \ const {\n    const int n = (int)this->size();\n    FPS ret(std::max(0, n - 1));\n\
    \    const mint one(1);\n    mint coeff(1);\n    for(int i = 1; i < n; i++) {\n\
    \      ret[i - 1] = (*this)[i] * coeff;\n      coeff += one;\n    }\n    return\
    \ ret;\n  }\n\n  FPS inv(int deg = -1) const {\n    assert((*this)[0] != mint(0));\n\
    \    if(deg == -1)\n      deg = (*this).size();\n    FPS ret({mint(1) / (*this)[0]});\n\
    \    for(int i = 1; i < deg; i <<= 1)\n      ret = (ret + ret - ret * ret * (*this).pre(i\
    \ << 1)).pre(i << 1);\n    return ret.pre(deg);\n  }\n\n  FPS integral() const\
    \ {\n    const int n = (int)this->size();\n    FPS ret(n + 1);\n    ret[0] = mint(0);\n\
    \    if(n > 0)\n      ret[1] = mint(1);\n    const auto mod = mint::mod();\n \
    \   for(int i = 2; i <= n; i++)\n      ret[i] = (-ret[mod % i]) * (mod / i);\n\
    \    for(int i = 0; i < n; i++)\n      ret[i + 1] *= (*this)[i];\n    return ret;\n\
    \  }\n\n  mint eval(mint x) const {\n    mint r = 0, w = 1;\n    for(auto &v :\
    \ *this)\n      r += w * v, w *= x;\n    return r;\n  }\n\n  FPS log(int deg =\
    \ -1) const {\n    assert(!(*this).empty() && (*this)[0] == mint(1));\n    assert(deg);\n\
    \    if(deg == -1)\n      deg = (int)this->size();\n    return (this->diff() *\
    \ this->inv(deg)).pre(deg - 1).integral();\n  }\n\n  FPS exp(int deg = -1) const\
    \ {\n    assert((*this).size() == 0 || (*this)[0] == mint(0));\n    if(deg ==\
    \ -1)\n      deg = (int)this->size();\n    FPS ret({mint(1)});\n    for(int i\
    \ = 1; i < deg; i <<= 1) {\n      ret = (ret * (pre(i << 1) + mint(1) - ret.log(i\
    \ << 1))).pre(i << 1);\n    }\n    return ret.pre(deg);\n  }\n\n  FPS pow(int64_t\
    \ k, int deg = -1) const {\n    const int n = (int)this->size();\n    if(deg ==\
    \ -1)\n      deg = n;\n    if(k == 0) {\n      FPS ret(deg);\n      if(deg)\n\
    \        ret[0] = 1;\n      return ret;\n    }\n    for(int i = 0; i < n; i++)\
    \ {\n      if((*this)[i] != mint(0)) {\n        mint rev = mint(1) / (*this)[i];\n\
    \        FPS ret = (((*this * rev) >> i).log(deg) * k).exp(deg);\n        ret\
    \ *= (*this)[i].pow(k);\n        ret = (ret << (i * k)).pre(deg);\n        if((int)ret.size()\
    \ < deg)\n          ret.resize(deg, mint(0));\n        return ret;\n      }\n\
    \      if(__int128_t(i + 1) * k >= deg)\n        return FPS(deg, mint(0));\n \
    \   }\n    return FPS(deg, mint(0));\n  }\n};\n\ntemplate <typename mint>\nstruct\
    \ FormalPowerSeries\n    : FormalPowerSeriesBase<mint, FormalPowerSeries<mint>>\
    \ {\n  using Base = FormalPowerSeriesBase<mint, FormalPowerSeries<mint>>;\n  using\
    \ Base::Base;\n  using FPS = FormalPowerSeries;\n  using Base::operator*=;\n \
    \ using Base::operator*;\n\n  FPS &operator*=(const FPS &r) {\n    if(this->empty()\
    \ || r.empty()) {\n      this->clear();\n      return *this;\n    }\n    auto\
    \ result = ayuna::convolution(std::vector<mint>(*this), std::vector<mint>(r));\n\
    \    this->assign(result.begin(), result.end());\n    return *this;\n  }\n\n \
    \ FPS operator*(const FPS &r) const { return FPS(*this) *= r; }\n};\n\n} // namespace\
    \ ayuna\n"
  dependsOn:
  - math/convolution.hpp
  - math/modint_static.hpp
  isVerificationFile: false
  path: fps/common.hpp
  requiredBy:
  - fps/common_ntt.hpp
  timestamp: '2026-05-07 00:37:36+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/Library_Checker/Convolution/Convolution_Mod_1097.test.cpp
  - test/Library_Checker/Polynomial/Log_of_Formal_Power_Series2.test.cpp
  - test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Log_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series.test.cpp
  - test/Library_Checker/Polynomial/Pow_of_Formal_Power_Series2.test.cpp
  - test/Library_Checker/Polynomial/Inv_of_Formal_Power_Series2.test.cpp
  - test/Library_Checker/Polynomial/Exp_of_Formal_Power_Series2.test.cpp
documentation_of: fps/common.hpp
layout: document
redirect_from:
- /library/fps/common.hpp
- /library/fps/common.hpp.html
title: fps/common.hpp
---
