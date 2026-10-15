---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Data_Structure/Range_Kth_Smallest.test.cpp
    title: test/Library_Checker/Data_Structure/Range_Kth_Smallest.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"persistent/persistentsegtree.hpp\"\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\n\
    namespace ayuna {\n\ntemplate <class S, auto op, auto e>\nrequires requires(S\
    \ a, S b) {\n  { op(a, b) } -> std::same_as<S>;\n  { e() } -> std::same_as<S>;\n\
    }\nclass PersistentSegtree {\npublic:\n  PersistentSegtree() : PersistentSegtree(0,\
    \ empty_tag{}) {}\n\n  explicit PersistentSegtree(int n_) : PersistentSegtree(n_,\
    \ empty_tag{}) {\n    if (n == 0)\n      return;\n    root = alloc_leaf(e());\n\
    \    for (int d = 0; d < log; d++)\n      root = alloc_internal(root, root);\n\
    \  }\n\n  explicit PersistentSegtree(const std::vector<S> &v)\n      : PersistentSegtree(static_cast<int>(v.size()),\
    \ empty_tag{}) {\n    if (n == 0)\n      return;\n    std::vector<int> cur(1u\
    \ << log);\n    int pad = n < static_cast<int>(cur.size()) ? alloc_leaf(e()) :\
    \ -1;\n    for (int i = 0; i < static_cast<int>(cur.size()); i++)\n      cur[i]\
    \ = i < n ? alloc_leaf(v[i]) : pad;\n    while (cur.size() > 1) {\n      for (std::size_t\
    \ i = 0; i < cur.size() / 2; i++)\n        cur[i] = alloc_internal(cur[2 * i],\
    \ cur[2 * i + 1]);\n      cur.resize(cur.size() / 2);\n    }\n    root = cur[0];\n\
    \  }\n\n  int size() const { return n; }\n\n  S get(int k) const {\n    assert(0\
    \ <= k && k < n);\n    int t = root;\n    for (int d = log - 1; d >= 0; d--)\n\
    \      t = (k >> d) & 1 ? pool[t].right : pool[t].left;\n    return pool[t].value;\n\
    \  }\n\n  PersistentSegtree set(int k, const S &x) const {\n    assert(0 <= k\
    \ && k < n);\n    int path[32];\n    int t = root;\n    for (int d = log - 1;\
    \ d >= 0; d--) {\n      path[d] = t;\n      t = (k >> d) & 1 ? pool[t].right :\
    \ pool[t].left;\n    }\n    t = alloc_leaf(x);\n    for (int d = 0; d < log; d++)\
    \ {\n      const Node &p = pool[path[d]];\n      int l = p.left, r = p.right;\n\
    \      t = (k >> d) & 1 ? alloc_internal(l, t) : alloc_internal(t, r);\n    }\n\
    \    PersistentSegtree res(n, empty_tag{});\n    res.root = t;\n    return res;\n\
    \  }\n\n  PersistentSegtree assign(const PersistentSegtree &src, int l, int r)\
    \ const {\n    assert(n == src.n);\n    assert(0 <= l && l <= r && r <= n);\n\
    \    PersistentSegtree res(n, empty_tag{});\n    res.root = assign(root, src.root,\
    \ 0, 1u << log, static_cast<unsigned int>(l),\n                      static_cast<unsigned\
    \ int>(r));\n    return res;\n  }\n\n  S prod(int l, int r) const {\n    assert(0\
    \ <= l && l <= r && r <= n);\n    if (l == r)\n      return e();\n    return prod(root,\
    \ 0, 1u << log, static_cast<unsigned int>(l),\n                static_cast<unsigned\
    \ int>(r));\n  }\n\n  S all_prod() const { return root == -1 ? e() : pool[root].value;\
    \ }\n\n  template <bool (*f)(S)> int max_right(int l) const {\n    return max_right(l,\
    \ [](S x) { return f(x); });\n  }\n\n  template <class F> int max_right(int l,\
    \ F f) const {\n    assert(0 <= l && l <= n);\n    assert(f(e()));\n    if (l\
    \ == n)\n      return n;\n    S sum = e();\n    return std::min(n, static_cast<int>(max_right(\n\
    \                           root, 0, 1u << log, static_cast<unsigned int>(l),\
    \ sum, f)));\n  }\n\n  template <class F>\n  int max_right_pair(int l, const PersistentSegtree\
    \ &other, F f) const {\n    assert(n == other.n);\n    assert(0 <= l && l <= n);\n\
    \    assert(f(e(), e()));\n    if (l == n)\n      return n;\n    S sum = e(),\
    \ other_sum = e();\n    return std::min(n, static_cast<int>(max_right_pair(\n\
    \                           root, other.root, 0, 1u << log,\n                \
    \           static_cast<unsigned int>(l), sum, other_sum, f)));\n  }\n\n  template\
    \ <bool (*f)(S)> int min_left(int r) const {\n    return min_left(r, [](S x) {\
    \ return f(x); });\n  }\n\n  template <class F> int min_left(int r, F f) const\
    \ {\n    assert(0 <= r && r <= n);\n    assert(f(e()));\n    if (r == 0)\n   \
    \   return 0;\n    S sum = e();\n    return static_cast<int>(\n        min_left(root,\
    \ 0, 1u << log, static_cast<unsigned int>(r), sum, f));\n  }\n\n  template <class\
    \ F>\n  int min_left_pair(int r, const PersistentSegtree &other, F f) const {\n\
    \    assert(n == other.n);\n    assert(0 <= r && r <= n);\n    assert(f(e(), e()));\n\
    \    if (r == 0)\n      return 0;\n    S sum = e(), other_sum = e();\n    return\
    \ static_cast<int>(min_left_pair(root, other.root, 0, 1u << log,\n           \
    \                               static_cast<unsigned int>(r), sum,\n         \
    \                                 other_sum, f));\n  }\n\n  static void reserve(std::size_t\
    \ node_count) { pool.reserve(node_count); }\n\n  static void clear() { std::vector<Node>().swap(pool);\
    \ }\n\nprivate:\n  struct Node {\n    int left = -1;\n    int right = -1;\n  \
    \  S value{};\n  };\n\n  static inline std::vector<Node> pool;\n\n  int n;\n \
    \ int log;\n  int root;\n\n  struct empty_tag {};\n\n  PersistentSegtree(int n_,\
    \ empty_tag)\n      : n(n_),\n        log(std::countr_zero(std::bit_ceil(static_cast<unsigned\
    \ int>(std::max(1, n_))))),\n        root(-1) {\n    assert(n >= 0);\n  }\n\n\
    \  static int alloc_leaf(const S &value) {\n    pool.push_back(Node{-1, -1, value});\n\
    \    return static_cast<int>(pool.size()) - 1;\n  }\n\n  static int alloc_internal(int\
    \ l, int r) {\n    pool.push_back(Node{l, r, op(pool[l].value, pool[r].value)});\n\
    \    return static_cast<int>(pool.size()) - 1;\n  }\n\n  static int assign(int\
    \ dst, int src, unsigned int l, unsigned int r,\n                    unsigned\
    \ int ql, unsigned int qr) {\n    if (r <= ql || qr <= l)\n      return dst;\n\
    \    if (ql <= l && r <= qr)\n      return src;\n\n    unsigned int m = (l + r)\
    \ / 2;\n    int dl = pool[dst].left, dr = pool[dst].right;\n    int left = assign(dl,\
    \ pool[src].left, l, m, ql, qr);\n    int right = assign(dr, pool[src].right,\
    \ m, r, ql, qr);\n    if (left == dl && right == dr)\n      return dst;\n    return\
    \ alloc_internal(left, right);\n  }\n\n  static S prod(int t, unsigned int l,\
    \ unsigned int r, unsigned int ql,\n                unsigned int qr) {\n    if\
    \ (r <= ql || qr <= l)\n      return e();\n    if (ql <= l && r <= qr)\n     \
    \ return pool[t].value;\n\n    unsigned int m = (l + r) / 2;\n    return op(prod(pool[t].left,\
    \ l, m, ql, qr),\n              prod(pool[t].right, m, r, ql, qr));\n  }\n\n \
    \ template <class F>\n  static unsigned int max_right(int t, unsigned int l, unsigned\
    \ int r,\n                                unsigned int ql, S &sum, F f) {\n  \
    \  if (r <= ql)\n      return r;\n    if (ql <= l) {\n      if (f(op(sum, pool[t].value)))\
    \ {\n        sum = op(sum, pool[t].value);\n        return r;\n      }\n     \
    \ if (r - l == 1)\n        return l;\n    }\n\n    unsigned int m = (l + r) /\
    \ 2;\n    unsigned int res = max_right(pool[t].left, l, m, ql, sum, f);\n    if\
    \ (res != m)\n      return res;\n    return max_right(pool[t].right, m, r, ql,\
    \ sum, f);\n  }\n\n  template <class F>\n  static unsigned int max_right_pair(int\
    \ t, int u, unsigned int l, unsigned int r,\n                                \
    \ unsigned int ql, S &sum, S &other_sum, F f) {\n    if (r <= ql)\n      return\
    \ r;\n    if (ql <= l) {\n      S x = op(sum, pool[t].value), y = op(other_sum,\
    \ pool[u].value);\n      if (f(x, y)) {\n        sum = x;\n        other_sum =\
    \ y;\n        return r;\n      }\n      if (r - l == 1)\n        return l;\n \
    \   }\n\n    unsigned int m = (l + r) / 2;\n    unsigned int res =\n        max_right_pair(pool[t].left,\
    \ pool[u].left, l, m, ql, sum, other_sum, f);\n    if (res != m)\n      return\
    \ res;\n    return max_right_pair(pool[t].right, pool[u].right, m, r, ql, sum,\
    \ other_sum, f);\n  }\n\n  template <class F>\n  static unsigned int min_left(int\
    \ t, unsigned int l, unsigned int r,\n                               unsigned\
    \ int qr, S &sum, F f) {\n    if (qr <= l)\n      return l;\n    if (r <= qr)\
    \ {\n      if (f(op(pool[t].value, sum))) {\n        sum = op(pool[t].value, sum);\n\
    \        return l;\n      }\n      if (r - l == 1)\n        return r;\n    }\n\
    \n    unsigned int m = (l + r) / 2;\n    unsigned int res = min_left(pool[t].right,\
    \ m, r, qr, sum, f);\n    if (res != m)\n      return res;\n    return min_left(pool[t].left,\
    \ l, m, qr, sum, f);\n  }\n\n  template <class F>\n  static unsigned int min_left_pair(int\
    \ t, int u, unsigned int l, unsigned int r,\n                                \
    \    unsigned int qr, S &sum, S &other_sum, F f) {\n    if (qr <= l)\n      return\
    \ l;\n    if (r <= qr) {\n      S x = op(pool[t].value, sum), y = op(pool[u].value,\
    \ other_sum);\n      if (f(x, y)) {\n        sum = x;\n        other_sum = y;\n\
    \        return l;\n      }\n      if (r - l == 1)\n        return r;\n    }\n\
    \n    unsigned int m = (l + r) / 2;\n    unsigned int res =\n        min_left_pair(pool[t].right,\
    \ pool[u].right, m, r, qr, sum, other_sum, f);\n    if (res != m)\n      return\
    \ res;\n    return min_left_pair(pool[t].left, pool[u].left, l, m, qr, sum, other_sum,\
    \ f);\n  }\n};\n\n} // namespace ayuna\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n\nnamespace ayuna {\n\ntemplate <class\
    \ S, auto op, auto e>\nrequires requires(S a, S b) {\n  { op(a, b) } -> std::same_as<S>;\n\
    \  { e() } -> std::same_as<S>;\n}\nclass PersistentSegtree {\npublic:\n  PersistentSegtree()\
    \ : PersistentSegtree(0, empty_tag{}) {}\n\n  explicit PersistentSegtree(int n_)\
    \ : PersistentSegtree(n_, empty_tag{}) {\n    if (n == 0)\n      return;\n   \
    \ root = alloc_leaf(e());\n    for (int d = 0; d < log; d++)\n      root = alloc_internal(root,\
    \ root);\n  }\n\n  explicit PersistentSegtree(const std::vector<S> &v)\n     \
    \ : PersistentSegtree(static_cast<int>(v.size()), empty_tag{}) {\n    if (n ==\
    \ 0)\n      return;\n    std::vector<int> cur(1u << log);\n    int pad = n < static_cast<int>(cur.size())\
    \ ? alloc_leaf(e()) : -1;\n    for (int i = 0; i < static_cast<int>(cur.size());\
    \ i++)\n      cur[i] = i < n ? alloc_leaf(v[i]) : pad;\n    while (cur.size()\
    \ > 1) {\n      for (std::size_t i = 0; i < cur.size() / 2; i++)\n        cur[i]\
    \ = alloc_internal(cur[2 * i], cur[2 * i + 1]);\n      cur.resize(cur.size() /\
    \ 2);\n    }\n    root = cur[0];\n  }\n\n  int size() const { return n; }\n\n\
    \  S get(int k) const {\n    assert(0 <= k && k < n);\n    int t = root;\n   \
    \ for (int d = log - 1; d >= 0; d--)\n      t = (k >> d) & 1 ? pool[t].right :\
    \ pool[t].left;\n    return pool[t].value;\n  }\n\n  PersistentSegtree set(int\
    \ k, const S &x) const {\n    assert(0 <= k && k < n);\n    int path[32];\n  \
    \  int t = root;\n    for (int d = log - 1; d >= 0; d--) {\n      path[d] = t;\n\
    \      t = (k >> d) & 1 ? pool[t].right : pool[t].left;\n    }\n    t = alloc_leaf(x);\n\
    \    for (int d = 0; d < log; d++) {\n      const Node &p = pool[path[d]];\n \
    \     int l = p.left, r = p.right;\n      t = (k >> d) & 1 ? alloc_internal(l,\
    \ t) : alloc_internal(t, r);\n    }\n    PersistentSegtree res(n, empty_tag{});\n\
    \    res.root = t;\n    return res;\n  }\n\n  PersistentSegtree assign(const PersistentSegtree\
    \ &src, int l, int r) const {\n    assert(n == src.n);\n    assert(0 <= l && l\
    \ <= r && r <= n);\n    PersistentSegtree res(n, empty_tag{});\n    res.root =\
    \ assign(root, src.root, 0, 1u << log, static_cast<unsigned int>(l),\n       \
    \               static_cast<unsigned int>(r));\n    return res;\n  }\n\n  S prod(int\
    \ l, int r) const {\n    assert(0 <= l && l <= r && r <= n);\n    if (l == r)\n\
    \      return e();\n    return prod(root, 0, 1u << log, static_cast<unsigned int>(l),\n\
    \                static_cast<unsigned int>(r));\n  }\n\n  S all_prod() const {\
    \ return root == -1 ? e() : pool[root].value; }\n\n  template <bool (*f)(S)> int\
    \ max_right(int l) const {\n    return max_right(l, [](S x) { return f(x); });\n\
    \  }\n\n  template <class F> int max_right(int l, F f) const {\n    assert(0 <=\
    \ l && l <= n);\n    assert(f(e()));\n    if (l == n)\n      return n;\n    S\
    \ sum = e();\n    return std::min(n, static_cast<int>(max_right(\n           \
    \                root, 0, 1u << log, static_cast<unsigned int>(l), sum, f)));\n\
    \  }\n\n  template <class F>\n  int max_right_pair(int l, const PersistentSegtree\
    \ &other, F f) const {\n    assert(n == other.n);\n    assert(0 <= l && l <= n);\n\
    \    assert(f(e(), e()));\n    if (l == n)\n      return n;\n    S sum = e(),\
    \ other_sum = e();\n    return std::min(n, static_cast<int>(max_right_pair(\n\
    \                           root, other.root, 0, 1u << log,\n                \
    \           static_cast<unsigned int>(l), sum, other_sum, f)));\n  }\n\n  template\
    \ <bool (*f)(S)> int min_left(int r) const {\n    return min_left(r, [](S x) {\
    \ return f(x); });\n  }\n\n  template <class F> int min_left(int r, F f) const\
    \ {\n    assert(0 <= r && r <= n);\n    assert(f(e()));\n    if (r == 0)\n   \
    \   return 0;\n    S sum = e();\n    return static_cast<int>(\n        min_left(root,\
    \ 0, 1u << log, static_cast<unsigned int>(r), sum, f));\n  }\n\n  template <class\
    \ F>\n  int min_left_pair(int r, const PersistentSegtree &other, F f) const {\n\
    \    assert(n == other.n);\n    assert(0 <= r && r <= n);\n    assert(f(e(), e()));\n\
    \    if (r == 0)\n      return 0;\n    S sum = e(), other_sum = e();\n    return\
    \ static_cast<int>(min_left_pair(root, other.root, 0, 1u << log,\n           \
    \                               static_cast<unsigned int>(r), sum,\n         \
    \                                 other_sum, f));\n  }\n\n  static void reserve(std::size_t\
    \ node_count) { pool.reserve(node_count); }\n\n  static void clear() { std::vector<Node>().swap(pool);\
    \ }\n\nprivate:\n  struct Node {\n    int left = -1;\n    int right = -1;\n  \
    \  S value{};\n  };\n\n  static inline std::vector<Node> pool;\n\n  int n;\n \
    \ int log;\n  int root;\n\n  struct empty_tag {};\n\n  PersistentSegtree(int n_,\
    \ empty_tag)\n      : n(n_),\n        log(std::countr_zero(std::bit_ceil(static_cast<unsigned\
    \ int>(std::max(1, n_))))),\n        root(-1) {\n    assert(n >= 0);\n  }\n\n\
    \  static int alloc_leaf(const S &value) {\n    pool.push_back(Node{-1, -1, value});\n\
    \    return static_cast<int>(pool.size()) - 1;\n  }\n\n  static int alloc_internal(int\
    \ l, int r) {\n    pool.push_back(Node{l, r, op(pool[l].value, pool[r].value)});\n\
    \    return static_cast<int>(pool.size()) - 1;\n  }\n\n  static int assign(int\
    \ dst, int src, unsigned int l, unsigned int r,\n                    unsigned\
    \ int ql, unsigned int qr) {\n    if (r <= ql || qr <= l)\n      return dst;\n\
    \    if (ql <= l && r <= qr)\n      return src;\n\n    unsigned int m = (l + r)\
    \ / 2;\n    int dl = pool[dst].left, dr = pool[dst].right;\n    int left = assign(dl,\
    \ pool[src].left, l, m, ql, qr);\n    int right = assign(dr, pool[src].right,\
    \ m, r, ql, qr);\n    if (left == dl && right == dr)\n      return dst;\n    return\
    \ alloc_internal(left, right);\n  }\n\n  static S prod(int t, unsigned int l,\
    \ unsigned int r, unsigned int ql,\n                unsigned int qr) {\n    if\
    \ (r <= ql || qr <= l)\n      return e();\n    if (ql <= l && r <= qr)\n     \
    \ return pool[t].value;\n\n    unsigned int m = (l + r) / 2;\n    return op(prod(pool[t].left,\
    \ l, m, ql, qr),\n              prod(pool[t].right, m, r, ql, qr));\n  }\n\n \
    \ template <class F>\n  static unsigned int max_right(int t, unsigned int l, unsigned\
    \ int r,\n                                unsigned int ql, S &sum, F f) {\n  \
    \  if (r <= ql)\n      return r;\n    if (ql <= l) {\n      if (f(op(sum, pool[t].value)))\
    \ {\n        sum = op(sum, pool[t].value);\n        return r;\n      }\n     \
    \ if (r - l == 1)\n        return l;\n    }\n\n    unsigned int m = (l + r) /\
    \ 2;\n    unsigned int res = max_right(pool[t].left, l, m, ql, sum, f);\n    if\
    \ (res != m)\n      return res;\n    return max_right(pool[t].right, m, r, ql,\
    \ sum, f);\n  }\n\n  template <class F>\n  static unsigned int max_right_pair(int\
    \ t, int u, unsigned int l, unsigned int r,\n                                \
    \ unsigned int ql, S &sum, S &other_sum, F f) {\n    if (r <= ql)\n      return\
    \ r;\n    if (ql <= l) {\n      S x = op(sum, pool[t].value), y = op(other_sum,\
    \ pool[u].value);\n      if (f(x, y)) {\n        sum = x;\n        other_sum =\
    \ y;\n        return r;\n      }\n      if (r - l == 1)\n        return l;\n \
    \   }\n\n    unsigned int m = (l + r) / 2;\n    unsigned int res =\n        max_right_pair(pool[t].left,\
    \ pool[u].left, l, m, ql, sum, other_sum, f);\n    if (res != m)\n      return\
    \ res;\n    return max_right_pair(pool[t].right, pool[u].right, m, r, ql, sum,\
    \ other_sum, f);\n  }\n\n  template <class F>\n  static unsigned int min_left(int\
    \ t, unsigned int l, unsigned int r,\n                               unsigned\
    \ int qr, S &sum, F f) {\n    if (qr <= l)\n      return l;\n    if (r <= qr)\
    \ {\n      if (f(op(pool[t].value, sum))) {\n        sum = op(pool[t].value, sum);\n\
    \        return l;\n      }\n      if (r - l == 1)\n        return r;\n    }\n\
    \n    unsigned int m = (l + r) / 2;\n    unsigned int res = min_left(pool[t].right,\
    \ m, r, qr, sum, f);\n    if (res != m)\n      return res;\n    return min_left(pool[t].left,\
    \ l, m, qr, sum, f);\n  }\n\n  template <class F>\n  static unsigned int min_left_pair(int\
    \ t, int u, unsigned int l, unsigned int r,\n                                \
    \    unsigned int qr, S &sum, S &other_sum, F f) {\n    if (qr <= l)\n      return\
    \ l;\n    if (r <= qr) {\n      S x = op(pool[t].value, sum), y = op(pool[u].value,\
    \ other_sum);\n      if (f(x, y)) {\n        sum = x;\n        other_sum = y;\n\
    \        return l;\n      }\n      if (r - l == 1)\n        return r;\n    }\n\
    \n    unsigned int m = (l + r) / 2;\n    unsigned int res =\n        min_left_pair(pool[t].right,\
    \ pool[u].right, m, r, qr, sum, other_sum, f);\n    if (res != m)\n      return\
    \ res;\n    return min_left_pair(pool[t].left, pool[u].left, l, m, qr, sum, other_sum,\
    \ f);\n  }\n};\n\n} // namespace ayuna\n"
  dependsOn: []
  isVerificationFile: false
  path: persistent/persistentsegtree.hpp
  requiredBy: []
  timestamp: '2026-10-16 03:26:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/Library_Checker/Data_Structure/Range_Kth_Smallest.test.cpp
documentation_of: persistent/persistentsegtree.hpp
layout: document
redirect_from:
- /library/persistent/persistentsegtree.hpp
- /library/persistent/persistentsegtree.hpp.html
title: persistent/persistentsegtree.hpp
---
