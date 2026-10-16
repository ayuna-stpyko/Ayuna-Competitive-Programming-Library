---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/binarytrie.hpp
    title: data_structure/binarytrie.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "#line 1 \"test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#line 2 \"\
    data_structure/binarytrie.hpp\"\n\n#include <array>\n#include <cassert>\n#include\
    \ <cstddef>\n#include <type_traits>\n#include <vector>\n\nnamespace ayuna {\n\n\
    template <int bit_len = 30, typename T = unsigned long long>\nstruct BinaryTrie\
    \ {\n  static constexpr bool has_sum = std::is_integral_v<T>;\n\n  BinaryTrie()\
    \ { new_node(); }\n\n  int size() const { return cnt_[0]; }\n\n  void reserve(std::size_t\
    \ n) {\n    ch_.reserve(n);\n    cnt_.reserve(n);\n    if constexpr (has_sum)\n\
    \      sum_.reserve(n);\n  }\n\n  void insert(T x) {\n    x ^= lazy_;\n    int\
    \ t = 0;\n    for (int b = bit_len - 1;; b--) {\n      cnt_[t]++;\n      if constexpr\
    \ (has_sum)\n        sum_[t] += x & low_mask(b);\n      if (b < 0)\n        return;\n\
    \      const int c = get_bit(x, b);\n      if (ch_[t][c] == -1) {\n        const\
    \ int u = new_node();\n        ch_[t][c] = u;\n      }\n      t = ch_[t][c];\n\
    \    }\n  }\n\n  void erase(T x) {\n    assert(count(x) > 0);\n    x ^= lazy_;\n\
    \    int t = 0;\n    for (int b = bit_len - 1;; b--) {\n      cnt_[t]--;\n   \
    \   if constexpr (has_sum)\n        sum_[t] -= x & low_mask(b);\n      if (b <\
    \ 0)\n        return;\n      const int c = get_bit(x, b);\n      const int u =\
    \ ch_[t][c];\n      if (cnt_[u] == 1) {\n        ch_[t][c] = -1;\n        release(u);\n\
    \        return;\n      }\n      t = u;\n    }\n  }\n\n  int count(T x) const\
    \ {\n    x ^= lazy_;\n    int t = 0;\n    for (int b = bit_len - 1; b >= 0; b--)\
    \ {\n      t = ch_[t][get_bit(x, b)];\n      if (t == -1)\n        return 0;\n\
    \    }\n    return cnt_[t];\n  }\n\n  bool find(T x) const { return count(x) >\
    \ 0; }\n\n  void op_xor(T mask) { lazy_ ^= mask; }\n\n  T kth_element(int k) const\
    \ { return kth_element_xor(k, T{}); }\n\n  T kth_element_xor(int k, T mask) const\
    \ {\n    assert(0 <= k && k < size());\n    mask ^= lazy_;\n    T res{};\n   \
    \ int t = 0;\n    for (int b = bit_len - 1; b >= 0; b--) {\n      const int c\
    \ = get_bit(mask, b);\n      const int lower_count = cnt(ch_[t][c]);\n      if\
    \ (k < lower_count) {\n        t = ch_[t][c];\n      }\n      else {\n       \
    \ k -= lower_count;\n        set_bit(res, b);\n        t = ch_[t][c ^ 1];\n  \
    \    }\n    }\n    return res;\n  }\n\n  T xor_min(T mask) const {\n    assert(size()\
    \ > 0);\n    return kth_element_xor(0, mask);\n  }\n\n  T xor_max(T mask) const\
    \ {\n    assert(size() > 0);\n    return kth_element_xor(size() - 1, mask);\n\
    \  }\n\n  int count_lt(T x) const { return count_lt(0, x, lazy_, bit_len - 1);\
    \ }\n\n  T sum(T l, T r) const\n    requires has_sum\n  {\n    return sum_xor(l,\
    \ r, T(0));\n  }\n\n  T sum_xor(T l, T r, T mask) const\n    requires has_sum\n\
    \  {\n    assert(l <= r);\n    const T m = lazy_ ^ mask;\n    return sum_lt(0,\
    \ r, m, bit_len - 1) - sum_lt(0, l, m, bit_len - 1);\n  }\n\nprivate:\n  std::vector<std::array<int,\
    \ 2>> ch_;\n  std::vector<int> cnt_;\n  std::vector<T> sum_;\n  std::vector<int>\
    \ free_;\n  T lazy_{};\n\n  int new_node() {\n    if (!free_.empty()) {\n    \
    \  const int t = free_.back();\n      free_.pop_back();\n      ch_[t] = {-1, -1};\n\
    \      cnt_[t] = 0;\n      if constexpr (has_sum)\n        sum_[t] = 0;\n    \
    \  return t;\n    }\n    ch_.push_back({-1, -1});\n    cnt_.push_back(0);\n  \
    \  if constexpr (has_sum)\n      sum_.push_back(0);\n    return static_cast<int>(ch_.size())\
    \ - 1;\n  }\n\n  void release(int t) {\n    while (t != -1) {\n      free_.push_back(t);\n\
    \      t = ch_[t][0] != -1 ? ch_[t][0] : ch_[t][1];\n    }\n  }\n\n  int cnt(int\
    \ t) const { return t == -1 ? 0 : cnt_[t]; }\n\n  static int get_bit(const T &x,\
    \ int b) {\n    if constexpr (std::is_integral_v<T>) {\n      return static_cast<int>((x\
    \ >> b) & 1);\n    }\n    else {\n      return static_cast<int>(x[b]);\n    }\n\
    \  }\n\n  static void set_bit(T &x, int b) {\n    if constexpr (std::is_integral_v<T>)\
    \ {\n      x |= T(1) << b;\n    }\n    else {\n      x.set(b);\n    }\n  }\n\n\
    \  static T low_mask(int b) { return b < 0 ? T(0) : ((T(1) << (b + 1)) - 1); }\n\
    \n  int count_lt(int t, const T &x, const T &mask, int b) const {\n    int res\
    \ = 0;\n    for (; t != -1 && b >= 0; b--) {\n      const int c = get_bit(mask,\
    \ b);\n      if (get_bit(x, b)) {\n        res += cnt(ch_[t][c]);\n        t =\
    \ ch_[t][c ^ 1];\n      }\n      else {\n        t = ch_[t][c];\n      }\n   \
    \ }\n    return res;\n  }\n\n  T full_sum_xor(int t, T mask, int b) const {\n\
    \    if (t == -1 || b < 0)\n      return 0;\n    if ((mask & low_mask(b)) == 0)\n\
    \      return sum_[t];\n    const int mb = get_bit(mask, b);\n    const T bit_contribution\
    \ = (T(1) << b) * static_cast<T>(mb ? cnt(ch_[t][0]) : cnt(ch_[t][1]));\n    return\
    \ bit_contribution + full_sum_xor(ch_[t][0], mask, b - 1) + full_sum_xor(ch_[t][1],\
    \ mask, b - 1);\n  }\n\n  T sum_lt(int t, T x, T mask, int b) const {\n    if\
    \ (t == -1 || b < 0)\n      return 0;\n    const int xb = get_bit(x, b);\n   \
    \ const int c = get_bit(mask, b);\n    if (xb == 0)\n      return sum_lt(ch_[t][c],\
    \ x, mask, b - 1);\n    return full_sum_xor(ch_[t][c], mask, b - 1) +\n      \
    \     (T(1) << b) * static_cast<T>(count_lt(ch_[t][c ^ 1], x, mask, b - 1)) +\n\
    \           sum_lt(ch_[t][c ^ 1], x, mask, b - 1);\n  }\n};\n\n} // namespace\
    \ ayuna\n#line 4 \"test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp\"\n\
    #include <iostream>\nusing namespace std;\n\nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n\
    \  ayuna::BinaryTrie trie;\n  int q;\n  cin >> q;\n  while (q--) {\n    int num,\
    \ x;\n    cin >> num >> x;\n    if (num == 0) {\n      if (trie.count(x) == 0)\n\
    \        trie.insert(x);\n    }\n    else if (num == 1) {\n      if (trie.count(x)\
    \ > 0)\n        trie.erase(x);\n    }\n    else {\n      cout << trie.kth_element_xor(0,\
    \ x) << endl;\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#include\
    \ \"data_structure/binarytrie.hpp\"\n#include <iostream>\nusing namespace std;\n\
    \nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n  ayuna::BinaryTrie\
    \ trie;\n  int q;\n  cin >> q;\n  while (q--) {\n    int num, x;\n    cin >> num\
    \ >> x;\n    if (num == 0) {\n      if (trie.count(x) == 0)\n        trie.insert(x);\n\
    \    }\n    else if (num == 1) {\n      if (trie.count(x) > 0)\n        trie.erase(x);\n\
    \    }\n    else {\n      cout << trie.kth_element_xor(0, x) << endl;\n    }\n\
    \  }\n}\n"
  dependsOn:
  - data_structure/binarytrie.hpp
  isVerificationFile: true
  path: test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp
  requiredBy: []
  timestamp: '2026-10-17 00:37:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp
- /verify/test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp.html
title: test/Library_Checker/Data_Structure/Set_Xor_Min.test.cpp
---
