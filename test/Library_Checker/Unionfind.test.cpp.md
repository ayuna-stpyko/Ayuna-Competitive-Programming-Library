---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/unionfind.hpp
    title: data_structure/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/Library_Checker/Unionfind.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include <iostream>\n#line\
    \ 1 \"data_structure/unionfind.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\nstruct UnionFind {\npublic:\n  UnionFind(int N) : _n(N) {\
    \ parent_or_size.resize(_n, -1); }\n\n  int merge(int a, int b) {\n    assert(0\
    \ <= a && a < _n);\n    assert(0 <= b && b < _n);\n    if(same(a, b))\n      return\
    \ leader(a);\n    if(size(a) < size(b))\n      std::swap(a, b);\n    int x = leader(a),\
    \ y = leader(b);\n    parent_or_size[x] += parent_or_size[y];\n    parent_or_size[y]\
    \ = x;\n    return a;\n  }\n\n  bool same(const int a, const int b) {\n    assert(0\
    \ <= a && a < _n);\n    assert(0 <= b && b < _n);\n    return leader(a) == leader(b);\n\
    \  }\n\n  int leader(const int a) {\n    assert(0 <= a && a < _n);\n    if(parent_or_size[a]\
    \ < 0)\n      return a;\n    parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    return parent_or_size[a];\n  }\n\n  int size(const int a) {\n    assert(0\
    \ <= a && a < _n);\n    return -parent_or_size[leader(a)];\n  }\n\n  std::vector<std::vector<int>>\
    \ groups() {\n    std::vector<std::vector<int>> ret(_n);\n    for(int i = 0; i\
    \ < _n; i++) {\n      if(parent_or_size[i] < 0) {\n        ret[i].reserve(-parent_or_size[i]);\n\
    \      }\n    }\n    for(int i = 0; i < _n; i++) {\n      ret[leader(i)].push_back(i);\n\
    \    }\n    ret.erase(std::remove_if(ret.begin(), ret.end(), [](const std::vector<int>\
    \ &a) { return a.empty(); }), ret.end());\n    return ret;\n  }\n\nprivate:\n\
    \  const int _n;\n  std::vector<int> parent_or_size;\n};\n#line 5 \"test/Library_Checker/Unionfind.test.cpp\"\
    \nusing namespace std;\n\nint main(){\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n\
    \  int n, q;\n  cin >> n >> q;\n  UnionFind uf(n);\n  while(q--){\n    int t,\
    \ u, v;\n    cin >> t >> u >> v;\n    if (t){\n      if (uf.same(u, v)) cout <<\
    \ 1 << endl;\n      else cout << 0 << endl;\n    }\n    else uf.merge(u, v);\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <iostream>\n#include \"data_structure/unionfind.hpp\"\nusing namespace std;\n\
    \nint main(){\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n  int n, q;\n  cin >>\
    \ n >> q;\n  UnionFind uf(n);\n  while(q--){\n    int t, u, v;\n    cin >> t >>\
    \ u >> v;\n    if (t){\n      if (uf.same(u, v)) cout << 1 << endl;\n      else\
    \ cout << 0 << endl;\n    }\n    else uf.merge(u, v);\n  }\n}\n"
  dependsOn:
  - data_structure/unionfind.hpp
  isVerificationFile: true
  path: test/Library_Checker/Unionfind.test.cpp
  requiredBy: []
  timestamp: '2024-10-28 02:38:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Unionfind.test.cpp
- /verify/test/Library_Checker/Unionfind.test.cpp.html
title: test/Library_Checker/Unionfind.test.cpp
---
