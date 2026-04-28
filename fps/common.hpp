#pragma once

#include "../math/convolution.hpp"
#include <algorithm>
#include <cassert>
#include <concepts>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <vector>

template <typename mint, class Derived>
struct FormalPowerSeriesBase : std::vector<mint> {
  using std::vector<mint>::vector;
  using FPS = Derived;

  FPS &self() { return static_cast<FPS &>(*this); }
  const FPS &self() const { return static_cast<const FPS &>(*this); }

  FPS &operator+=(const FPS &r) {
    if(r.size() > this->size())
      this->resize(r.size());
    for(int i = 0; i < (int)r.size(); i++)
      (*this)[i] += r[i];
    return self();
  }

  FPS &operator+=(const mint &r) {
    if(this->empty())
      this->resize(1);
    (*this)[0] += r;
    return self();
  }

  FPS &operator-=(const FPS &r) {
    if(r.size() > this->size())
      this->resize(r.size());
    for(int i = 0; i < (int)r.size(); i++)
      (*this)[i] -= r[i];
    return self();
  }

  FPS &operator*=(const mint &v) {
    for(int k = 0; k < (int)this->size(); k++)
      (*this)[k] *= v;
    return self();
  }

  FPS &operator-=(const mint &r) {
    if(this->empty())
      this->resize(1);
    (*this)[0] -= r;
    return self();
  }

  FPS &operator/=(const FPS &r) {
    if(this->size() < r.size()) {
      this->clear();
      return self();
    }
    int n = this->size() - r.size() + 1;
    if((int)r.size() <= 64) {
      FPS f(self()), g(std::begin(r), std::end(r));
      g.shrink();
      mint coeff = g.back().inv();
      for(auto &x : g)
        x *= coeff;
      int deg = (int)f.size() - (int)g.size() + 1;
      int gs = g.size();
      FPS quo(deg);
      for(int i = deg - 1; i >= 0; i--) {
        quo[i] = f[i + gs - 1];
        for(int j = 0; j < gs; j++)
          f[i + j] -= quo[i] * g[j];
      }
      *this = quo * coeff;
      this->resize(n, mint(0));
      return self();
    }
    FPS rr(std::begin(r), std::end(r));
    return *this = (self().rev().pre(n) * rr.rev().inv(n)).pre(n).rev();
  }

  FPS &operator%=(const FPS &r) {
    *this -= *this / r * r;
    shrink();
    return self();
  }

  FPS operator+(const FPS &r) const { return FPS(self()) += r; }
  FPS operator+(const mint &v) const { return FPS(self()) += v; }
  FPS operator-(const FPS &r) const { return FPS(self()) -= r; }
  FPS operator-(const mint &v) const { return FPS(self()) -= v; }
  FPS operator*(const mint &v) const { return FPS(self()) *= v; }
  FPS operator/(const FPS &r) const { return FPS(self()) /= r; }
  FPS operator%(const FPS &r) const { return FPS(self()) %= r; }
  FPS operator-() const {
    FPS ret(this->size());
    for(int i = 0; i < (int)this->size(); i++)
      ret[i] = -(*this)[i];
    return ret;
  }

  void shrink() {
    while(this->size() && this->back() == mint(0))
      this->pop_back();
  }

  FPS rev() const {
    FPS ret(self());
    reverse(begin(ret), end(ret));
    return ret;
  }

  FPS dot(const FPS &r) const {
    FPS ret(std::min(this->size(), r.size()));
    for(int i = 0; i < (int)ret.size(); i++)
      ret[i] = (*this)[i] * r[i];
    return ret;
  }

  FPS pre(int sz) const {
    FPS ret(begin(*this), begin(*this) + std::min((int)this->size(), sz));
    if((int)ret.size() < sz)
      ret.resize(sz);
    return ret;
  }

  FPS operator>>(int sz) const {
    if((int)this->size() <= sz)
      return {};
    FPS ret(self());
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  FPS operator<<(int sz) const {
    FPS ret(self());
    ret.insert(ret.begin(), sz, mint(0));
    return ret;
  }

  FPS diff() const {
    const int n = (int)this->size();
    FPS ret(std::max(0, n - 1));
    const mint one(1);
    mint coeff(1);
    for(int i = 1; i < n; i++) {
      ret[i - 1] = (*this)[i] * coeff;
      coeff += one;
    }
    return ret;
  }

  FPS inv(int deg = -1) const {
    assert((*this)[0] != mint(0));
    if(deg == -1)
      deg = (*this).size();
    FPS ret({mint(1) / (*this)[0]});
    for(int i = 1; i < deg; i <<= 1)
      ret = (ret + ret - ret * ret * (*this).pre(i << 1)).pre(i << 1);
    return ret.pre(deg);
  }

  FPS integral() const {
    const int n = (int)this->size();
    FPS ret(n + 1);
    ret[0] = mint(0);
    if(n > 0)
      ret[1] = mint(1);
    const auto mod = mint::mod();
    for(int i = 2; i <= n; i++)
      ret[i] = (-ret[mod % i]) * (mod / i);
    for(int i = 0; i < n; i++)
      ret[i + 1] *= (*this)[i];
    return ret;
  }

  mint eval(mint x) const {
    mint r = 0, w = 1;
    for(auto &v : *this)
      r += w * v, w *= x;
    return r;
  }

  FPS log(int deg = -1) const {
    assert(!(*this).empty() && (*this)[0] == mint(1));
    assert(deg);
    if(deg == -1)
      deg = (int)this->size();
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  FPS exp(int deg = -1) const {
    assert((*this).size() == 0 || (*this)[0] == mint(0));
    if(deg == -1)
      deg = (int)this->size();
    FPS ret({mint(1)});
    for(int i = 1; i < deg; i <<= 1) {
      ret = (ret * (pre(i << 1) + mint(1) - ret.log(i << 1))).pre(i << 1);
    }
    return ret.pre(deg);
  }

  FPS pow(int64_t k, int deg = -1) const {
    const int n = (int)this->size();
    if(deg == -1)
      deg = n;
    if(k == 0) {
      FPS ret(deg);
      if(deg)
        ret[0] = 1;
      return ret;
    }
    for(int i = 0; i < n; i++) {
      if((*this)[i] != mint(0)) {
        mint rev = mint(1) / (*this)[i];
        FPS ret = (((*this * rev) >> i).log(deg) * k).exp(deg);
        ret *= (*this)[i].pow(k);
        ret = (ret << (i * k)).pre(deg);
        if((int)ret.size() < deg)
          ret.resize(deg, mint(0));
        return ret;
      }
      if(__int128_t(i + 1) * k >= deg)
        return FPS(deg, mint(0));
    }
    return FPS(deg, mint(0));
  }
};

template <typename mint>
struct FormalPowerSeries
    : FormalPowerSeriesBase<mint, FormalPowerSeries<mint>> {
  using Base = FormalPowerSeriesBase<mint, FormalPowerSeries<mint>>;
  using Base::Base;
  using FPS = FormalPowerSeries;
  using Base::operator*=;
  using Base::operator*;

  FPS &operator*=(const FPS &r) {
    if(this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    auto result = convolution(std::vector<mint>(*this), std::vector<mint>(r));
    this->assign(result.begin(), result.end());
    return *this;
  }

  FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
};
