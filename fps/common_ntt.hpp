#pragma once

#include "common.hpp"
#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>

template <typename mint>
struct NTTFriendlyFormalPowerSeries
    : FormalPowerSeriesBase<mint, NTTFriendlyFormalPowerSeries<mint>> {
  using Base = FormalPowerSeriesBase<mint, NTTFriendlyFormalPowerSeries<mint>>;
  using FPS = NTTFriendlyFormalPowerSeries;
  using Base::operator*=;
  using Base::operator*;

  void init_tables() { setwy(level); }

  NTTFriendlyFormalPowerSeries() : Base() { init_tables(); }

  explicit NTTFriendlyFormalPowerSeries(int n) : Base(n) { init_tables(); }

  NTTFriendlyFormalPowerSeries(int n, const mint &v) : Base(n, v) {
    init_tables();
  }

  NTTFriendlyFormalPowerSeries(std::initializer_list<mint> init) : Base(init) {
    init_tables();
  }

  template <std::input_iterator It>
  NTTFriendlyFormalPowerSeries(It first, It last) : Base(first, last) {
    init_tables();
  }

  static constexpr uint32_t mod = mint::mod();
  static constexpr mint primitive_root = primitive_root_constexpr(mod);
  static constexpr int level = std::countr_zero((uint32_t)(mod - 1));
  static_assert(level >= 3, "NTTFriendlyFormalPowerSeries requires v2(mod-1) "
                            ">= 3 (NTT-friendly prime).");
  mint dw[level], dy[level];

  void setwy(int k) {
    mint w[level], y[level];
    w[k - 1] = primitive_root.pow((mod - 1) / (1 << k));
    y[k - 1] = w[k - 1].inv();
    for(int i = k - 2; i > 0; i--) {
      w[i] = w[i + 1] * w[i + 1];
      y[i] = y[i + 1] * y[i + 1];
    }
    dw[1] = w[1], dw[2] = w[2];
    dy[1] = y[1], dy[2] = y[2];
    for(int i = 3; i < k; i++) {
      dw[i] = dw[i - 1] * y[i - 2] * w[i];
      dy[i] = dy[i - 1] * w[i - 2] * y[i];
    }
  }

  void fft4(std::vector<mint> &a, int k) {
    if((int)a.size() <= 1)
      return;
    if(k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    if(k & 1) {
      int v = 1 << (k - 1);
      for(int j = 0; j < v; j++) {
        mint ajv = a[j + v];
        a[j + v] = a[j] - ajv;
        a[j] += ajv;
      }
    }
    int u = 1 << (2 + (k & 1));
    int v = 1 << (k - 2 - (k & 1));
    const mint one = mint(1);
    const mint imag = dw[1];
    while(v) {
      for(int j0 = 0, j1 = v, j2 = j1 + v, j3 = j2 + v; j0 < v;
          j0++, j1++, j2++, j3++) {
        const mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
        const mint t0p2 = t0 + t2, t1p3 = t1 + t3;
        const mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
        a[j0] = t0p2 + t1p3, a[j1] = t0p2 - t1p3;
        a[j2] = t0m2 + t1m3, a[j3] = t0m2 - t1m3;
      }
      mint ww = one, xx = one * dw[2], wx = one;
      for(int jh = 4; jh < u;) {
        ww = xx * xx, wx = ww * xx;
        for(int j0 = jh * v, je = j0 + v, j2 = je + v; j0 < je; j0++, j2++) {
          const mint t0 = a[j0], t1 = a[j0 + v] * xx;
          const mint t2 = a[j2] * ww, t3 = a[j2 + v] * wx;
          const mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          const mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[j0] = t0p2 + t1p3, a[j0 + v] = t0p2 - t1p3;
          a[j2] = t0m2 + t1m3, a[j2 + v] = t0m2 - t1m3;
        }
        jh += 4;
        xx *= dw[__builtin_ctzll(jh)];
      }
      u <<= 2;
      v >>= 2;
    }
  }

  void ifft4(std::vector<mint> &a, int k) {
    if((int)a.size() <= 1)
      return;
    if(k == 1) {
      const mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    int u = 1 << (k - 2);
    int v = 1;
    const mint one = mint(1);
    const mint imag = dy[1];
    while(u) {
      for(int j0 = 0, j1 = v, j2 = j1 + v, j3 = j2 + v; j0 < v;
          j0++, j1++, j2++, j3++) {
        const mint t0 = a[j0], t1 = a[j1], t2 = a[j2], t3 = a[j3];
        const mint t0p1 = t0 + t1, t2p3 = t2 + t3;
        const mint t0m1 = t0 - t1, t2m3 = (t2 - t3) * imag;
        a[j0] = t0p1 + t2p3, a[j2] = t0p1 - t2p3;
        a[j1] = t0m1 + t2m3, a[j3] = t0m1 - t2m3;
      }
      mint ww = one, xx = one * dy[2], yy = one;
      u <<= 2;
      for(int jh = 4; jh < u;) {
        ww = xx * xx, yy = xx * imag;
        for(int j0 = jh * v, je = j0 + v, j2 = je + v; j0 < je; j0++, j2++) {
          const mint t0 = a[j0], t1 = a[j0 + v], t2 = a[j2], t3 = a[j2 + v];
          const mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          const mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
          a[j0] = t0p1 + t2p3, a[j2] = (t0p1 - t2p3) * ww;
          a[j0 + v] = t0m1 + t2m3, a[j2 + v] = (t0m1 - t2m3) * ww;
        }
        jh += 4;
        xx *= dy[__builtin_ctzll(jh)];
      }
      u >>= 4;
      v <<= 2;
    }
    if(k & 1) {
      u = 1 << (k - 1);
      for(int j = 0; j < u; j++) {
        mint ajv = a[j] - a[j + u];
        a[j] += a[j + u];
        a[j + u] = ajv;
      }
    }
  }

  void ntt(std::vector<mint> &a) {
    if((int)a.size() <= 1)
      return;
    fft4(a, __builtin_ctz(a.size()));
  }

  void intt(std::vector<mint> &a) {
    if((int)a.size() <= 1)
      return;
    ifft4(a, __builtin_ctz(a.size()));
    const mint iv = mint(a.size()).inv();
    for(auto &x : a)
      x *= iv;
  }

  FPS &operator*=(const FPS &r) {
    if(this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    int l = int(this->size() + r.size()) - 1;
    if(std::min(this->size(), r.size()) <= size_t(40)) {
      std::vector<mint> s(l);
      for(int i = 0; i < (int)this->size(); i++)
        for(int j = 0; j < (int)r.size(); j++)
          s[i + j] += (*this)[i] * r[j];
      this->assign(s.begin(), s.end());
      return *this;
    }
    int k = 2, M = 4;
    while(M < l) {
      M <<= 1;
      k++;
    }
    setwy(k);
    std::vector<mint> s(M);
    for(int i = 0; i < (int)this->size(); i++)
      s[i] = (*this)[i];
    fft4(s, k);
    if(this->size() == r.size() && *this == r) {
      for(int i = 0; i < M; i++)
        s[i] *= s[i];
    }
    else {
      std::vector<mint> t(M);
      for(int i = 0; i < (int)r.size(); i++)
        t[i] = r[i];
      fft4(t, k);
      for(int i = 0; i < M; i++)
        s[i] *= t[i];
    }
    ifft4(s, k);
    s.resize(l);
    const mint invm = mint(M).inv();
    for(int i = 0; i < l; i++)
      s[i] *= invm;
    this->assign(s.begin(), s.end());
    return *this;
  }

  FPS operator*(const FPS &r) const { return FPS(*this) *= r; }

  void ntt_doubling(std::vector<mint> &a) {
    const int M = int(a.size());
    auto b = a;
    intt(b);
    mint r = 1, zeta = primitive_root.pow((mod - 1) / (M << 1));
    for(int i = 0; i < M; i++) {
      b[i] *= r;
      r *= zeta;
    }
    ntt(b);
    std::copy(std::begin(b), std::end(b), std::back_inserter(a));
  }
};
