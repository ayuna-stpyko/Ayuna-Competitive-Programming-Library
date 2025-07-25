---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segmenttree.hpp
    title: data_structure/segmenttree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/Library_Checker/Point_Add_Range_Sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#include\
    \ <iostream>\n#line 1 \"data_structure/segmenttree.hpp\"\n#include <cassert>\n\
    #include <vector>\n#include <functional>\n\ntemplate <class S, auto op, auto e>\
    \ struct SegmentTree {\n  SegmentTree(int n) : SegmentTree(std::vector<S>(n, e()))\
    \ {}\n  SegmentTree(const std::vector<S> &v) : _n(v.size()) {\n    size = bit_ceil((unsigned\
    \ int)_n);\n    log = __builtin_ctz((unsigned int)size);\n    d.resize(size <<\
    \ 1, e());\n    for (int i = 0; i < _n; i++) d[size + i] = v[i];\n    for (int\
    \ i = size - 1; i >= 1; i--) update(i);\n  }\n\n  void set(int p, S x){\n    assert(0\
    \ <= p && p < _n);\n    p += size;\n    d[p] = x;\n    for (int i = 1; i <= log;\
    \ i++) update(p >> i);\n  }\n\n  S get(const int p) const{\n    assert(0 <= p\
    \ && p < _n);\n    return d[p + size];\n  }\n\n  S prod(int l, int r) const{\n\
    \    assert(0 <= l && l <= r && r <= _n);\n    S sml = e(), smr = e();\n    l\
    \ += size;\n    r += size;\n    while (l < r) {\n      if (l & 1) sml = op(sml,\
    \ d[l++]);\n      if (r & 1) smr = op(d[--r], smr);\n      l >>= 1;\n      r >>=\
    \ 1;\n    }\n    return op(sml, smr);\n  }\n\n  S all_prod() const{\n    return\
    \ d[1];\n  }\n\nprivate:\n  int _n, size, log;\n  std::vector<S> d;\n  void update(int\
    \ i) { d[i] = op(d[i << 1], d[i << 1 | 1]); }\n\n  unsigned int bit_ceil(unsigned\
    \ int n) {\n    unsigned int x = 1;\n    while (x < (unsigned int)(n)) x <<= 1;\n\
    \    return x;\n  }\n};\n#line 5 \"test/Library_Checker/Point_Add_Range_Sum.test.cpp\"\
    \nusing namespace std;\nusing ll = long long;\n\nll op(ll a, ll b) { return a\
    \ + b;}\nll e() { return 0;}\n\nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n\
    \  int n, q;\n  cin >> n >> q;\n  vector<ll> a(n);\n  for (ll &i: a) cin >> i;\n\
    \  SegmentTree<ll, op, e> st(a);\n  while (q--) {\n    int num;\n    cin >> num;\n\
    \    switch (num) {\n    case 0:\n      int p;\n      ll x;\n      cin >> p >>\
    \ x;\n      st.set(p, st.get(p) + x);\n      break;\n    \n    case 1:\n     \
    \ int l, r;\n      cin >> l >> r;\n      cout << st.prod(l, r) << endl;\n    \
    \  break;\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <iostream>\n#include \"data_structure/segmenttree.hpp\"\nusing namespace\
    \ std;\nusing ll = long long;\n\nll op(ll a, ll b) { return a + b;}\nll e() {\
    \ return 0;}\n\nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n  int\
    \ n, q;\n  cin >> n >> q;\n  vector<ll> a(n);\n  for (ll &i: a) cin >> i;\n  SegmentTree<ll,\
    \ op, e> st(a);\n  while (q--) {\n    int num;\n    cin >> num;\n    switch (num)\
    \ {\n    case 0:\n      int p;\n      ll x;\n      cin >> p >> x;\n      st.set(p,\
    \ st.get(p) + x);\n      break;\n    \n    case 1:\n      int l, r;\n      cin\
    \ >> l >> r;\n      cout << st.prod(l, r) << endl;\n      break;\n    }\n  }\n\
    }"
  dependsOn:
  - data_structure/segmenttree.hpp
  isVerificationFile: true
  path: test/Library_Checker/Point_Add_Range_Sum.test.cpp
  requiredBy: []
  timestamp: '2024-11-27 18:01:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Point_Add_Range_Sum.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Point_Add_Range_Sum.test.cpp
- /verify/test/Library_Checker/Point_Add_Range_Sum.test.cpp.html
title: test/Library_Checker/Point_Add_Range_Sum.test.cpp
---
