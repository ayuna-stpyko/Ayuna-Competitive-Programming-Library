---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
    title: test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"persistent/persistentqueue.hpp\"\n\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n\nnamespace ayuna {\n\ntemplate <typename\
    \ T>\nclass PersistentQueue {\npublic:\n  PersistentQueue() = default;\n\n  bool\
    \ empty() const { return sz == 0; }\n\n  int size() const { return sz; }\n\n \
    \ T front() const {\n    assert(!empty());\n    return nodes[ancestor(last, nodes[last].depth\
    \ - sz + 1)].value;\n  }\n\n  T back() const {\n    assert(!empty());\n    return\
    \ nodes[last].value;\n  }\n\n  PersistentQueue push(const T &x) const {\n    int\
    \ p = last;\n    if (p == -1) {\n      int t = static_cast<int>(nodes.size());\n\
    \      nodes.push_back(Node{x, t, t, 0});\n      return PersistentQueue(t, sz\
    \ + 1);\n    }\n    int j = nodes[p].jump, jj = nodes[j].jump;\n    int dp = nodes[p].depth,\
    \ dj = nodes[j].depth, djj = nodes[jj].depth;\n    int jump = dp - dj == dj -\
    \ djj ? jj : p;\n    nodes.push_back(Node{x, p, jump, dp + 1});\n    return PersistentQueue(static_cast<int>(nodes.size())\
    \ - 1, sz + 1);\n  }\n\n  PersistentQueue pop() const {\n    assert(!empty());\n\
    \    return PersistentQueue(last, sz - 1);\n  }\n\n  static void reserve(std::size_t\
    \ node_count) { nodes.reserve(node_count); }\n\n  static void clear() { std::vector<Node>().swap(nodes);\
    \ }\n\nprivate:\n  struct Node {\n    T value;\n    int parent;\n    int jump;\n\
    \    int depth;\n  };\n\n  static inline std::vector<Node> nodes;\n\n  int last\
    \ = -1;\n  int sz = 0;\n\n  PersistentQueue(int last_, int sz_) : last(last_),\
    \ sz(sz_) {}\n\n  static int ancestor(int t, int d) {\n    while (nodes[t].depth\
    \ > d) {\n      int j = nodes[t].jump;\n      t = nodes[j].depth >= d ? j : nodes[t].parent;\n\
    \    }\n    return t;\n  }\n};\n\n} // namespace ayuna\n"
  code: "#pragma once\n\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\
    \nnamespace ayuna {\n\ntemplate <typename T>\nclass PersistentQueue {\npublic:\n\
    \  PersistentQueue() = default;\n\n  bool empty() const { return sz == 0; }\n\n\
    \  int size() const { return sz; }\n\n  T front() const {\n    assert(!empty());\n\
    \    return nodes[ancestor(last, nodes[last].depth - sz + 1)].value;\n  }\n\n\
    \  T back() const {\n    assert(!empty());\n    return nodes[last].value;\n  }\n\
    \n  PersistentQueue push(const T &x) const {\n    int p = last;\n    if (p ==\
    \ -1) {\n      int t = static_cast<int>(nodes.size());\n      nodes.push_back(Node{x,\
    \ t, t, 0});\n      return PersistentQueue(t, sz + 1);\n    }\n    int j = nodes[p].jump,\
    \ jj = nodes[j].jump;\n    int dp = nodes[p].depth, dj = nodes[j].depth, djj =\
    \ nodes[jj].depth;\n    int jump = dp - dj == dj - djj ? jj : p;\n    nodes.push_back(Node{x,\
    \ p, jump, dp + 1});\n    return PersistentQueue(static_cast<int>(nodes.size())\
    \ - 1, sz + 1);\n  }\n\n  PersistentQueue pop() const {\n    assert(!empty());\n\
    \    return PersistentQueue(last, sz - 1);\n  }\n\n  static void reserve(std::size_t\
    \ node_count) { nodes.reserve(node_count); }\n\n  static void clear() { std::vector<Node>().swap(nodes);\
    \ }\n\nprivate:\n  struct Node {\n    T value;\n    int parent;\n    int jump;\n\
    \    int depth;\n  };\n\n  static inline std::vector<Node> nodes;\n\n  int last\
    \ = -1;\n  int sz = 0;\n\n  PersistentQueue(int last_, int sz_) : last(last_),\
    \ sz(sz_) {}\n\n  static int ancestor(int t, int d) {\n    while (nodes[t].depth\
    \ > d) {\n      int j = nodes[t].jump;\n      t = nodes[j].depth >= d ? j : nodes[t].parent;\n\
    \    }\n    return t;\n  }\n};\n\n} // namespace ayuna\n"
  dependsOn: []
  isVerificationFile: false
  path: persistent/persistentqueue.hpp
  requiredBy: []
  timestamp: '2026-10-16 03:26:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
documentation_of: persistent/persistentqueue.hpp
layout: document
redirect_from:
- /library/persistent/persistentqueue.hpp
- /library/persistent/persistentqueue.hpp.html
title: persistent/persistentqueue.hpp
---
