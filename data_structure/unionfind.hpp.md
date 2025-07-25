---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Unionfind.test.cpp
    title: test/Library_Checker/Unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/unionfind.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nstruct UnionFind {\npublic:\n  UnionFind(int\
    \ N) : _n(N) { parent_or_size.resize(_n, -1); }\n\n  int merge(int a, int b) {\n\
    \    assert(0 <= a && a < _n);\n    assert(0 <= b && b < _n);\n    if(same(a,\
    \ b))\n      return leader(a);\n    if(size(a) < size(b))\n      std::swap(a,\
    \ b);\n    int x = leader(a), y = leader(b);\n    parent_or_size[x] += parent_or_size[y];\n\
    \    parent_or_size[y] = x;\n    return a;\n  }\n\n  bool same(const int a, const\
    \ int b) {\n    assert(0 <= a && a < _n);\n    assert(0 <= b && b < _n);\n   \
    \ return leader(a) == leader(b);\n  }\n\n  int leader(const int a) {\n    assert(0\
    \ <= a && a < _n);\n    if(parent_or_size[a] < 0)\n      return a;\n    parent_or_size[a]\
    \ = leader(parent_or_size[a]);\n    return parent_or_size[a];\n  }\n\n  int size(const\
    \ int a) {\n    assert(0 <= a && a < _n);\n    return -parent_or_size[leader(a)];\n\
    \  }\n\n  std::vector<std::vector<int>> groups() {\n    std::vector<std::vector<int>>\
    \ ret(_n);\n    for(int i = 0; i < _n; i++) {\n      if(parent_or_size[i] < 0)\
    \ {\n        ret[i].reserve(-parent_or_size[i]);\n      }\n    }\n    for(int\
    \ i = 0; i < _n; i++) {\n      ret[leader(i)].push_back(i);\n    }\n    ret.erase(std::remove_if(ret.begin(),\
    \ ret.end(), [](const std::vector<int> &a) { return a.empty(); }), ret.end());\n\
    \    return ret;\n  }\n\nprivate:\n  const int _n;\n  std::vector<int> parent_or_size;\n\
    };\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <vector>\n\nstruct UnionFind\
    \ {\npublic:\n  UnionFind(int N) : _n(N) { parent_or_size.resize(_n, -1); }\n\n\
    \  int merge(int a, int b) {\n    assert(0 <= a && a < _n);\n    assert(0 <= b\
    \ && b < _n);\n    if(same(a, b))\n      return leader(a);\n    if(size(a) < size(b))\n\
    \      std::swap(a, b);\n    int x = leader(a), y = leader(b);\n    parent_or_size[x]\
    \ += parent_or_size[y];\n    parent_or_size[y] = x;\n    return a;\n  }\n\n  bool\
    \ same(const int a, const int b) {\n    assert(0 <= a && a < _n);\n    assert(0\
    \ <= b && b < _n);\n    return leader(a) == leader(b);\n  }\n\n  int leader(const\
    \ int a) {\n    assert(0 <= a && a < _n);\n    if(parent_or_size[a] < 0)\n   \
    \   return a;\n    parent_or_size[a] = leader(parent_or_size[a]);\n    return\
    \ parent_or_size[a];\n  }\n\n  int size(const int a) {\n    assert(0 <= a && a\
    \ < _n);\n    return -parent_or_size[leader(a)];\n  }\n\n  std::vector<std::vector<int>>\
    \ groups() {\n    std::vector<std::vector<int>> ret(_n);\n    for(int i = 0; i\
    \ < _n; i++) {\n      if(parent_or_size[i] < 0) {\n        ret[i].reserve(-parent_or_size[i]);\n\
    \      }\n    }\n    for(int i = 0; i < _n; i++) {\n      ret[leader(i)].push_back(i);\n\
    \    }\n    ret.erase(std::remove_if(ret.begin(), ret.end(), [](const std::vector<int>\
    \ &a) { return a.empty(); }), ret.end());\n    return ret;\n  }\n\nprivate:\n\
    \  const int _n;\n  std::vector<int> parent_or_size;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/unionfind.hpp
  requiredBy: []
  timestamp: '2024-07-08 14:29:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/Library_Checker/Unionfind.test.cpp
documentation_of: data_structure/unionfind.hpp
layout: document
redirect_from:
- /library/data_structure/unionfind.hpp
- /library/data_structure/unionfind.hpp.html
title: data_structure/unionfind.hpp
---
