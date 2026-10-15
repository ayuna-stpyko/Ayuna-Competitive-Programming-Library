---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: persistent/persistentunionfind.hpp
    title: persistent/persistentunionfind.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Data_Structure/Persistent_Unionfind.test.cpp
    title: test/Library_Checker/Data_Structure/Persistent_Unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"persistent/persistentarray.hpp\"\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\n\
    namespace ayuna {\n\ntemplate <typename T>\nclass PersistentArray {\npublic:\n\
    \  PersistentArray() : PersistentArray(Raw{}, 0, -1) {}\n\n  explicit PersistentArray(int\
    \ n_, const T &x = T{}) : PersistentArray(Raw{}, n_, -1) {\n    if (n == 0)\n\
    \      return;\n    root = alloc_leaf(x);\n    for (int d = 0; d < log; d++)\n\
    \      root = alloc_node(root, root);\n  }\n\n  explicit PersistentArray(const\
    \ std::vector<T> &v)\n      : PersistentArray(Raw{}, static_cast<int>(v.size()),\
    \ -1) {\n    if (n == 0)\n      return;\n    int base = static_cast<int>(leaves.size());\n\
    \    leaves.insert(leaves.end(), v.begin(), v.end());\n    std::vector<int> cur(1u\
    \ << log);\n    for (int i = 0; i < static_cast<int>(cur.size()); i++)\n     \
    \ cur[i] = base + std::min(i, n - 1);\n    while (cur.size() > 1) {\n      for\
    \ (std::size_t i = 0; i < cur.size() / 2; i++)\n        cur[i] = alloc_node(cur[2\
    \ * i], cur[2 * i + 1]);\n      cur.resize(cur.size() / 2);\n    }\n    root =\
    \ cur[0];\n  }\n\n  int size() const { return n; }\n\n  T get(int k) const {\n\
    \    assert(0 <= k && k < n);\n    int t = root;\n    for (int d = log - 1; d\
    \ >= 0; d--)\n      t = nodes[t].ch[(k >> d) & 1];\n    return leaves[t];\n  }\n\
    \n  PersistentArray set(int k, const T &x) const {\n    assert(0 <= k && k < n);\n\
    \    int leaf = alloc_leaf(x);\n    if (log == 0)\n      return PersistentArray(Raw{},\
    \ n, leaf);\n    int base = static_cast<int>(nodes.size());\n    nodes.resize(base\
    \ + log);\n    int t = root;\n    for (int d = log - 1, i = base; d >= 0; d--,\
    \ i++) {\n      int b = (k >> d) & 1;\n      nodes[i] = nodes[t];\n      t = nodes[t].ch[b];\n\
    \      nodes[i].ch[b] = d > 0 ? i + 1 : leaf;\n    }\n    return PersistentArray(Raw{},\
    \ n, base);\n  }\n\n  PersistentArray assign(const PersistentArray &src, int l,\
    \ int r) const {\n    assert(n == src.n);\n    assert(0 <= l && l <= r && r <=\
    \ n);\n    return PersistentArray(Raw{}, n,\n                           assign(root,\
    \ src.root, 0, 1u << log,\n                                  static_cast<unsigned\
    \ int>(l),\n                                  static_cast<unsigned int>(r)));\n\
    \  }\n\n  static void reserve(std::size_t node_count, std::size_t leaf_count)\
    \ {\n    nodes.reserve(node_count);\n    leaves.reserve(leaf_count);\n  }\n\n\
    \  static void clear() {\n    std::vector<Node>().swap(nodes);\n    std::vector<T>().swap(leaves);\n\
    \  }\n\nprivate:\n  struct Raw {};\n\n  struct Node {\n    int ch[2];\n  };\n\n\
    \  static inline std::vector<Node> nodes;\n  static inline std::vector<T> leaves;\n\
    \n  int n;\n  int log;\n  int root;\n\n  PersistentArray(Raw, int n_, int root_)\n\
    \      : n(n_),\n        log(std::countr_zero(std::bit_ceil(static_cast<unsigned\
    \ int>(std::max(1, n_))))),\n        root(root_) {\n    assert(n >= 0);\n  }\n\
    \n  static int alloc_leaf(const T &x) {\n    leaves.push_back(x);\n    return\
    \ static_cast<int>(leaves.size()) - 1;\n  }\n\n  static int alloc_node(int l,\
    \ int r) {\n    nodes.push_back(Node{{l, r}});\n    return static_cast<int>(nodes.size())\
    \ - 1;\n  }\n\n  static int assign(int dst, int src, unsigned int l, unsigned\
    \ int r,\n                    unsigned int ql, unsigned int qr) {\n    if (r <=\
    \ ql || qr <= l)\n      return dst;\n    if (ql <= l && r <= qr)\n      return\
    \ src;\n\n    unsigned int m = (l + r) / 2;\n    Node d = nodes[dst], s = nodes[src];\n\
    \    int left = assign(d.ch[0], s.ch[0], l, m, ql, qr);\n    int right = assign(d.ch[1],\
    \ s.ch[1], m, r, ql, qr);\n    if (left == d.ch[0] && right == d.ch[1])\n    \
    \  return dst;\n    return alloc_node(left, right);\n  }\n};\n\n} // namespace\
    \ ayuna\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n\nnamespace ayuna {\n\ntemplate <typename\
    \ T>\nclass PersistentArray {\npublic:\n  PersistentArray() : PersistentArray(Raw{},\
    \ 0, -1) {}\n\n  explicit PersistentArray(int n_, const T &x = T{}) : PersistentArray(Raw{},\
    \ n_, -1) {\n    if (n == 0)\n      return;\n    root = alloc_leaf(x);\n    for\
    \ (int d = 0; d < log; d++)\n      root = alloc_node(root, root);\n  }\n\n  explicit\
    \ PersistentArray(const std::vector<T> &v)\n      : PersistentArray(Raw{}, static_cast<int>(v.size()),\
    \ -1) {\n    if (n == 0)\n      return;\n    int base = static_cast<int>(leaves.size());\n\
    \    leaves.insert(leaves.end(), v.begin(), v.end());\n    std::vector<int> cur(1u\
    \ << log);\n    for (int i = 0; i < static_cast<int>(cur.size()); i++)\n     \
    \ cur[i] = base + std::min(i, n - 1);\n    while (cur.size() > 1) {\n      for\
    \ (std::size_t i = 0; i < cur.size() / 2; i++)\n        cur[i] = alloc_node(cur[2\
    \ * i], cur[2 * i + 1]);\n      cur.resize(cur.size() / 2);\n    }\n    root =\
    \ cur[0];\n  }\n\n  int size() const { return n; }\n\n  T get(int k) const {\n\
    \    assert(0 <= k && k < n);\n    int t = root;\n    for (int d = log - 1; d\
    \ >= 0; d--)\n      t = nodes[t].ch[(k >> d) & 1];\n    return leaves[t];\n  }\n\
    \n  PersistentArray set(int k, const T &x) const {\n    assert(0 <= k && k < n);\n\
    \    int leaf = alloc_leaf(x);\n    if (log == 0)\n      return PersistentArray(Raw{},\
    \ n, leaf);\n    int base = static_cast<int>(nodes.size());\n    nodes.resize(base\
    \ + log);\n    int t = root;\n    for (int d = log - 1, i = base; d >= 0; d--,\
    \ i++) {\n      int b = (k >> d) & 1;\n      nodes[i] = nodes[t];\n      t = nodes[t].ch[b];\n\
    \      nodes[i].ch[b] = d > 0 ? i + 1 : leaf;\n    }\n    return PersistentArray(Raw{},\
    \ n, base);\n  }\n\n  PersistentArray assign(const PersistentArray &src, int l,\
    \ int r) const {\n    assert(n == src.n);\n    assert(0 <= l && l <= r && r <=\
    \ n);\n    return PersistentArray(Raw{}, n,\n                           assign(root,\
    \ src.root, 0, 1u << log,\n                                  static_cast<unsigned\
    \ int>(l),\n                                  static_cast<unsigned int>(r)));\n\
    \  }\n\n  static void reserve(std::size_t node_count, std::size_t leaf_count)\
    \ {\n    nodes.reserve(node_count);\n    leaves.reserve(leaf_count);\n  }\n\n\
    \  static void clear() {\n    std::vector<Node>().swap(nodes);\n    std::vector<T>().swap(leaves);\n\
    \  }\n\nprivate:\n  struct Raw {};\n\n  struct Node {\n    int ch[2];\n  };\n\n\
    \  static inline std::vector<Node> nodes;\n  static inline std::vector<T> leaves;\n\
    \n  int n;\n  int log;\n  int root;\n\n  PersistentArray(Raw, int n_, int root_)\n\
    \      : n(n_),\n        log(std::countr_zero(std::bit_ceil(static_cast<unsigned\
    \ int>(std::max(1, n_))))),\n        root(root_) {\n    assert(n >= 0);\n  }\n\
    \n  static int alloc_leaf(const T &x) {\n    leaves.push_back(x);\n    return\
    \ static_cast<int>(leaves.size()) - 1;\n  }\n\n  static int alloc_node(int l,\
    \ int r) {\n    nodes.push_back(Node{{l, r}});\n    return static_cast<int>(nodes.size())\
    \ - 1;\n  }\n\n  static int assign(int dst, int src, unsigned int l, unsigned\
    \ int r,\n                    unsigned int ql, unsigned int qr) {\n    if (r <=\
    \ ql || qr <= l)\n      return dst;\n    if (ql <= l && r <= qr)\n      return\
    \ src;\n\n    unsigned int m = (l + r) / 2;\n    Node d = nodes[dst], s = nodes[src];\n\
    \    int left = assign(d.ch[0], s.ch[0], l, m, ql, qr);\n    int right = assign(d.ch[1],\
    \ s.ch[1], m, r, ql, qr);\n    if (left == d.ch[0] && right == d.ch[1])\n    \
    \  return dst;\n    return alloc_node(left, right);\n  }\n};\n\n} // namespace\
    \ ayuna\n"
  dependsOn: []
  isVerificationFile: false
  path: persistent/persistentarray.hpp
  requiredBy:
  - persistent/persistentunionfind.hpp
  timestamp: '2026-10-16 03:26:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/Library_Checker/Data_Structure/Persistent_Unionfind.test.cpp
documentation_of: persistent/persistentarray.hpp
layout: document
redirect_from:
- /library/persistent/persistentarray.hpp
- /library/persistent/persistentarray.hpp.html
title: persistent/persistentarray.hpp
---
