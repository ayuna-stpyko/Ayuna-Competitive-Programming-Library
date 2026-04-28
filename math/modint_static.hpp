#pragma once

#include <cassert>
#include <iostream>
#include <numeric>
#include <type_traits>
#include <utility>

using ll = long long;
using ull = unsigned long long;
using u32 = unsigned int;

template <int m> struct modint {
  using mint = modint;

private:
  u32 _v;

public:
  constexpr modint() : _v(0) {}
  template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  constexpr modint(T v) {
    ll x = (ll)(v % (ll)(m));
    if(x < 0)
      x += m;
    _v = (u32)(x);
  }

  u32 val() const { return _v; }

  static constexpr u32 mod() { return m; }

  mint &operator++() {
    _v++;
    if(_v == m)
      _v = 0;
    return *this;
  }
  mint &operator--() {
    if(_v == 0)
      _v = m;
    _v--;
    return *this;
  }
  mint operator++(int) {
    mint result = *this;
    ++*this;
    return result;
  }
  mint operator--(int) {
    mint result = *this;
    --*this;
    return result;
  }

  mint &operator+=(const mint &r) {
    _v += r._v;
    if(_v >= m)
      _v -= m;
    return *this;
  }
  mint &operator-=(const mint &r) {
    _v -= r._v;
    if(_v >= m)
      _v += m;
    return *this;
  }
  mint &operator*=(const mint &r) {
    ull z = _v;
    z *= r._v;
    _v = (u32)(z % m);
    return *this;
  }
  mint &operator/=(const mint &r) { return *this = *this * r.inv(); }

  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }

  mint pow(ll n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while(n) {
      if(n & 1)
        r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    assert(_v);
    return pow(m - 2);
  }

  friend mint operator+(const mint &l, const mint &r) { return mint(l) += r; }
  friend mint operator-(const mint &l, const mint &r) { return mint(l) -= r; }
  friend mint operator*(const mint &l, const mint &r) { return mint(l) *= r; }
  friend mint operator/(const mint &l, const mint &r) { return mint(l) /= r; }
  friend bool operator==(const mint &l, const mint &r) { return l._v == r._v; }
  friend bool operator!=(const mint &l, const mint &r) { return l._v != r._v; }
  friend std::ostream &operator<<(std::ostream &os, const mint &a) {
    return os << a.val();
  }
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;
