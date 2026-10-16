#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace ayuna {

template <int bit_len = 30, typename T = unsigned long long>
struct BinaryTrie {
  static constexpr bool has_sum = std::is_integral_v<T>;

  BinaryTrie() { new_node(); }

  int size() const { return cnt_[0]; }

  void reserve(std::size_t n) {
    ch_.reserve(n);
    cnt_.reserve(n);
    if constexpr (has_sum)
      sum_.reserve(n);
  }

  void insert(T x) {
    x ^= lazy_;
    int t = 0;
    for (int b = bit_len - 1;; b--) {
      cnt_[t]++;
      if constexpr (has_sum)
        sum_[t] += x & low_mask(b);
      if (b < 0)
        return;
      const int c = get_bit(x, b);
      if (ch_[t][c] == -1) {
        const int u = new_node();
        ch_[t][c] = u;
      }
      t = ch_[t][c];
    }
  }

  void erase(T x) {
    assert(count(x) > 0);
    x ^= lazy_;
    int t = 0;
    for (int b = bit_len - 1;; b--) {
      cnt_[t]--;
      if constexpr (has_sum)
        sum_[t] -= x & low_mask(b);
      if (b < 0)
        return;
      const int c = get_bit(x, b);
      const int u = ch_[t][c];
      if (cnt_[u] == 1) {
        ch_[t][c] = -1;
        release(u);
        return;
      }
      t = u;
    }
  }

  int count(T x) const {
    x ^= lazy_;
    int t = 0;
    for (int b = bit_len - 1; b >= 0; b--) {
      t = ch_[t][get_bit(x, b)];
      if (t == -1)
        return 0;
    }
    return cnt_[t];
  }

  bool find(T x) const { return count(x) > 0; }

  void op_xor(T mask) { lazy_ ^= mask; }

  T kth_element(int k) const { return kth_element_xor(k, T{}); }

  T kth_element_xor(int k, T mask) const {
    assert(0 <= k && k < size());
    mask ^= lazy_;
    T res{};
    int t = 0;
    for (int b = bit_len - 1; b >= 0; b--) {
      const int c = get_bit(mask, b);
      const int lower_count = cnt(ch_[t][c]);
      if (k < lower_count) {
        t = ch_[t][c];
      }
      else {
        k -= lower_count;
        set_bit(res, b);
        t = ch_[t][c ^ 1];
      }
    }
    return res;
  }

  T xor_min(T mask) const {
    assert(size() > 0);
    return kth_element_xor(0, mask);
  }

  T xor_max(T mask) const {
    assert(size() > 0);
    return kth_element_xor(size() - 1, mask);
  }

  int count_lt(T x) const { return count_lt(0, x, lazy_, bit_len - 1); }

  T sum(T l, T r) const
    requires has_sum
  {
    return sum_xor(l, r, T(0));
  }

  T sum_xor(T l, T r, T mask) const
    requires has_sum
  {
    assert(l <= r);
    const T m = lazy_ ^ mask;
    return sum_lt(0, r, m, bit_len - 1) - sum_lt(0, l, m, bit_len - 1);
  }

private:
  std::vector<std::array<int, 2>> ch_;
  std::vector<int> cnt_;
  std::vector<T> sum_;
  std::vector<int> free_;
  T lazy_{};

  int new_node() {
    if (!free_.empty()) {
      const int t = free_.back();
      free_.pop_back();
      ch_[t] = {-1, -1};
      cnt_[t] = 0;
      if constexpr (has_sum)
        sum_[t] = 0;
      return t;
    }
    ch_.push_back({-1, -1});
    cnt_.push_back(0);
    if constexpr (has_sum)
      sum_.push_back(0);
    return static_cast<int>(ch_.size()) - 1;
  }

  void release(int t) {
    while (t != -1) {
      free_.push_back(t);
      t = ch_[t][0] != -1 ? ch_[t][0] : ch_[t][1];
    }
  }

  int cnt(int t) const { return t == -1 ? 0 : cnt_[t]; }

  static int get_bit(const T &x, int b) {
    if constexpr (std::is_integral_v<T>) {
      return static_cast<int>((x >> b) & 1);
    }
    else {
      return static_cast<int>(x[b]);
    }
  }

  static void set_bit(T &x, int b) {
    if constexpr (std::is_integral_v<T>) {
      x |= T(1) << b;
    }
    else {
      x.set(b);
    }
  }

  static T low_mask(int b) { return b < 0 ? T(0) : ((T(1) << (b + 1)) - 1); }

  int count_lt(int t, const T &x, const T &mask, int b) const {
    int res = 0;
    for (; t != -1 && b >= 0; b--) {
      const int c = get_bit(mask, b);
      if (get_bit(x, b)) {
        res += cnt(ch_[t][c]);
        t = ch_[t][c ^ 1];
      }
      else {
        t = ch_[t][c];
      }
    }
    return res;
  }

  T full_sum_xor(int t, T mask, int b) const {
    if (t == -1 || b < 0)
      return 0;
    if ((mask & low_mask(b)) == 0)
      return sum_[t];
    const int mb = get_bit(mask, b);
    const T bit_contribution = (T(1) << b) * static_cast<T>(mb ? cnt(ch_[t][0]) : cnt(ch_[t][1]));
    return bit_contribution + full_sum_xor(ch_[t][0], mask, b - 1) + full_sum_xor(ch_[t][1], mask, b - 1);
  }

  T sum_lt(int t, T x, T mask, int b) const {
    if (t == -1 || b < 0)
      return 0;
    const int xb = get_bit(x, b);
    const int c = get_bit(mask, b);
    if (xb == 0)
      return sum_lt(ch_[t][c], x, mask, b - 1);
    return full_sum_xor(ch_[t][c], mask, b - 1) +
           (T(1) << b) * static_cast<T>(count_lt(ch_[t][c ^ 1], x, mask, b - 1)) +
           sum_lt(ch_[t][c ^ 1], x, mask, b - 1);
  }
};

} // namespace ayuna
