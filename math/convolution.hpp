#pragma once

#include "modint_static.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if(x < 0)
    x += m;
  return x;
}

constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
  if(m == 1)
    return 0;
  unsigned int _m = (unsigned int)(m);
  unsigned long long r = 1;
  unsigned long long y = safe_mod(x, m);
  while(n) {
    if(n & 1)
      r = (r * y) % _m;
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}

constexpr int primitive_root_constexpr(int m) {
  if(m == 2)
    return 1;
  if(m == 167772161)
    return 3;
  if(m == 469762049)
    return 3;
  if(m == 754974721)
    return 11;
  if(m == 998244353)
    return 3;
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (m - 1) / 2;
  while(x % 2 == 0)
    x >>= 1;
  for(int i = 3; (long long)(i)*i <= x; i += 2) {
    if(x % i == 0) {
      divs[cnt++] = i;
      while(x % i == 0)
        x /= i;
    }
  }
  if(x > 1)
    divs[cnt++] = x;
  for(int g = 2;; g++) {
    bool ok = true;
    for(int i = 0; i < cnt; i++) {
      if(pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if(ok)
      return g;
  }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

template <class T>
concept StaticModint = requires(T a, T b, long long n) {
  std::integral_constant<decltype(T::mod()), T::mod()>{};
  { a + b } -> std::same_as<T>;
  { a - b } -> std::same_as<T>;
  { a *b } -> std::same_as<T>;
  { a.val() } -> std::convertible_to<unsigned int>;
  { a.inv() } -> std::same_as<T>;
  { a.pow(n) } -> std::same_as<T>;
  T{1};
};

template <StaticModint mint, int g = primitive_root<(int)mint::mod()>>
struct fft_info {
  static constexpr int rank2 =
      std::countr_zero((unsigned int)(mint::mod() - 1));
  std::array<mint, rank2 + 1> root;
  std::array<mint, rank2 + 1> iroot;
  std::array<mint, std::max(0, rank2 - 1)> rate2;
  std::array<mint, std::max(0, rank2 - 1)> irate2;
  std::array<mint, std::max(0, rank2 - 2)> rate3;
  std::array<mint, std::max(0, rank2 - 2)> irate3;

  fft_info() {
    root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
    iroot[rank2] = root[rank2].inv();
    for(int i = rank2 - 1; i >= 0; i--) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }
    {
      mint prod = 1, iprod = 1;
      for(int i = 0; i <= rank2 - 2; i++) {
        rate2[i] = root[i + 2] * prod;
        irate2[i] = iroot[i + 2] * iprod;
        prod *= iroot[i + 2];
        iprod *= root[i + 2];
      }
    }
    {
      mint prod = 1, iprod = 1;
      for(int i = 0; i <= rank2 - 3; i++) {
        rate3[i] = root[i + 3] * prod;
        irate3[i] = iroot[i + 3] * iprod;
        prod *= iroot[i + 3];
        iprod *= root[i + 3];
      }
    }
  }
};

template <StaticModint mint> void butterfly(std::vector<mint> &a) {
  const int n = int(a.size());
  const int h = std::countr_zero((unsigned int)n);
  static const fft_info<mint> info;
  int len = 0;
  while(len < h) {
    if(h - len == 1) {
      int p = 1 << (h - len - 1);
      mint rot = 1;
      for(int s = 0; s < (1 << len); s++) {
        int offset = s << (h - len);
        for(int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p] * rot;
          a[i + offset] = l + r;
          a[i + offset + p] = l - r;
        }
        if(s + 1 != (1 << len))
          rot *= info.rate2[std::countr_zero(~(unsigned int)(s))];
      }
      len++;
    }
		else {
      if constexpr(fft_info<mint>::rank2 >= 2) {
        // 4-base
        int p = 1 << (h - len - 2);
        mint rot = 1, imag = info.root[2];
        for(int s = 0; s < (1 << len); s++) {
          mint rot2 = rot * rot, rot3 = rot2 * rot;
          int offset = s << (h - len);
          for(int i = 0; i < p; i++) {
            auto mod2 = 1ULL * mint::mod() * mint::mod();
            auto a0 = 1ULL * a[i + offset].val();
            auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
            auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
            auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
            auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val() * imag.val();
            auto na2 = mod2 - a2;
            a[i + offset] = a0 + a2 + a1 + a3;
            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
          }
          if(s + 1 != (1 << len))
            rot *= info.rate3[std::countr_zero(~(unsigned int)(s))];
        }
        len += 2;
      }
			else {
        assert(false && "butterfly: rank2 too small for 4-base NTT");
      }
    }
  }
}

template <StaticModint mint> void butterfly_inv(std::vector<mint> &a) {
  const int n = int(a.size());
  const int h = std::countr_zero((unsigned int)n);
  static const fft_info<mint> info;
  int len = h;
  while(len) {
    if(len == 1) {
      int p = 1 << (h - len);
      mint irot = 1;
      for(int s = 0; s < (1 << (len - 1)); s++) {
        int offset = s << (h - len + 1);
        for(int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p];
          a[i + offset] = l + r;
          a[i + offset + p] =
              (unsigned long long)(mint::mod() + l.val() - r.val()) *
              irot.val();
        }
        if(s + 1 != (1 << (len - 1)))
          irot *= info.irate2[std::countr_zero(~(unsigned int)(s))];
      }
      len--;
    }
		else {
      if constexpr(fft_info<mint>::rank2 >= 2) {
        // 4-base
        int p = 1 << (h - len);
        mint irot = 1, iimag = info.iroot[2];
        for(int s = 0; s < (1 << (len - 2)); s++) {
          mint irot2 = irot * irot, irot3 = irot2 * irot;
          int offset = s << (h - len + 2);
          for(int i = 0; i < p; i++) {
            auto a0 = 1ULL * a[i + offset + 0 * p].val();
            auto a1 = 1ULL * a[i + offset + 1 * p].val();
            auto a2 = 1ULL * a[i + offset + 2 * p].val();
            auto a3 = 1ULL * a[i + offset + 3 * p].val();
            auto a2na3iimag =
                1ULL * mint((mint::mod() + a2 - a3) * iimag.val()).val();
            a[i + offset] = a0 + a1 + a2 + a3;
            a[i + offset + 1 * p] =
                (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
            a[i + offset + 2 * p] =
                (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) *
                irot2.val();
            a[i + offset + 3 * p] =
                (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
                irot3.val();
          }
          if(s + 1 != (1 << (len - 2)))
            irot *= info.irate3[std::countr_zero(~(unsigned int)(s))];
        }
        len -= 2;
      }
			else {
        assert(false && "butterfly_inv: rank2 too small for 4-base NTT");
      }
    }
  }
}

template <StaticModint mint>
std::vector<mint> convolution_naive(const std::vector<mint> &a,
                                    const std::vector<mint> &b) {
  const int n = int(a.size()), m = int(b.size());
  std::vector<mint> ans(n + m - 1);
  for(int j = 0; j < m; j++)
    for(int i = 0; i < n; i++)
      ans[i + j] += a[i] * b[j];
  return ans;
}

template <StaticModint mint>
std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b) {
  const int n = int(a.size()), m = int(b.size());
  if(!n || !m)
    return {};
  int z = (int)std::bit_ceil((unsigned int)(n + m - 1));
  a.resize(z);
  butterfly(a);
  b.resize(z);
  butterfly(b);
  for(int i = 0; i < z; i++)
    a[i] *= b[i];
  butterfly_inv(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for(int i = 0; i < n + m - 1; i++)
    a[i] *= iz;
  return a;
}

template <StaticModint mint>
static std::vector<mint> convolution_arbitrary_mod(const std::vector<mint> &a,
                                                   const std::vector<mint> &b) {
  using m1 = modint<167772161>;  // 2^25 * 5 + 1
  using m2 = modint<469762049>;  // 2^26 * 7 + 1
  using m3 = modint<1224736769>; // 2^24 * 73 + 1

  const int n = (int)a.size(), m = (int)b.size();
  std::vector<m1> a1(n), b1(m);
  std::vector<m2> a2(n), b2(m);
  std::vector<m3> a3(n), b3(m);
  for(int i = 0; i < n; i++) {
    const unsigned int v = a[i].val();
    a1[i] = v;
    a2[i] = v;
    a3[i] = v;
  }
  for(int i = 0; i < m; i++) {
    const unsigned int v = b[i].val();
    b1[i] = v;
    b2[i] = v;
    b3[i] = v;
  }

  const auto c1 = convolution_fft(std::move(a1), std::move(b1));
  const auto c2 = convolution_fft(std::move(a2), std::move(b2));
  const auto c3 = convolution_fft(std::move(a3), std::move(b3));

  static constexpr unsigned long long M1 = m1::mod();
  static constexpr unsigned long long M2 = m2::mod();
  static constexpr unsigned long long M1M2 = M1 * M2;

  static const m2 inv_m1_mod_m2 = m2(M1).inv();
  static const m3 inv_m1m2_mod_m3 = m3(M1M2).inv();

  const int sz = n + m - 1;
  std::vector<mint> res(sz);
  for(int i = 0; i < sz; i++) {
    const unsigned long long x1 = c1[i].val();
    const unsigned long long x2 = c2[i].val();
    const unsigned long long x3 = c3[i].val();

    const unsigned long long t1 = x1;
    const unsigned long long t2 =
        (unsigned long long)(m2((long long)x2 - (long long)t1) * inv_m1_mod_m2)
            .val();
    const unsigned long long t3 =
        (unsigned long long)(m3((long long)x3 -
                                (long long)(m3(t1 + M1 * t2).val())) *
                             inv_m1m2_mod_m3)
            .val();

    const unsigned long long mod = mint::mod();
    const unsigned long long term1 = t1 % mod;
    const unsigned long long term2 = (M1 % mod) * (t2 % mod) % mod;
    const unsigned long long term3 = (M1M2 % mod) * (t3 % mod) % mod;
    res[i] = mint((term1 + term2 + term3) % mod);
  }
  return res;
}

template <StaticModint mint>
std::vector<mint> convolution(std::vector<mint> &&a, std::vector<mint> &&b) {
  const int n = int(a.size()), m = int(b.size());
  if(!n || !m)
    return {};
  const int z = (int)std::bit_ceil((unsigned int)(n + m - 1));
  if(std::min(n, m) <= 60)
    return convolution_naive(a, b);
  if((mint::mod() - 1) % z == 0)
    return convolution_fft(std::move(a), std::move(b));
  return convolution_arbitrary_mod<mint>(a, b);
}
