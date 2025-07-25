---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/dynamicsegtree.hpp
    title: data_structure/dynamicsegtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/Library_Checker/Point_Set_Range_Composite2.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include <iostream>\n#line 1 \"data_structure/dynamicsegtree.hpp\"\n#include\
    \ <cassert>\n#include <memory>\n\ntemplate <class S, S (*op)(S, S), S (*e)()>\n\
    class DynamicSegmentTree {\npublic:\n  DynamicSegmentTree(long long _n) : n(_n),\
    \ root(nullptr) {}\n\n  void set(long long p, S x) {\n    assert(p < n);\n   \
    \ set(root, 0, n, p, x);\n  }\n  S get(long long p) const {\n    assert(p < n);\n\
    \    return get(root, 0, n, p);\n  }\n  S prod(long long l, long long r) const\
    \ {\n    assert(l <= r && r <= n);\n    return prod(root, 0, n, l, r);\n  }\n\n\
    \  S all_prod() const { return root ? root->value : e(); }\n\n  void reset(long\
    \ long l, long long r) {\n    assert(l <= r && r <= n);\n    reset(root, 0, n,\
    \ l, r);\n  }\n\nprivate:\n  struct node;\n  using node_ptr = std::unique_ptr<node>;\n\
    \n  struct node {\n    S value;\n    node_ptr left, right;\n    node() : value(e()),\
    \ left(nullptr), right(nullptr) {}\n    node(S v) : value(v), left(nullptr), right(nullptr)\
    \ {}\n  };\n\n  long long n;\n  node_ptr root;\n\n  void set(node_ptr &t, long\
    \ long l, long long r, long long p, S x) {\n    if(t == nullptr)\n      t = std::make_unique<node>();\n\
    \    if(r - l == 1) {\n      t->value = x;\n      return;\n    }\n    long long\
    \ m = (l + r) >> 1;\n    if(p < m)\n      set(t->left, l, m, p, x);\n    else\n\
    \      set(t->right, m, r, p, x);\n    t->value =\n        op(t->left ? t->left->value\
    \ : e(), t->right ? t->right->value : e());\n  }\n\n  S get(const node_ptr &t,\
    \ long long l, long long r, long long p) const {\n    if(t == nullptr)\n     \
    \ return e();\n    if(r - l == 1)\n      return t->value;\n    long long m = (l\
    \ + r) >> 1;\n    if(p < m)\n      return get(t->left, l, m, p);\n    else\n \
    \     return get(t->right, m, r, p);\n  }\n\n  S prod(const node_ptr &t, long\
    \ long l, long long r, long long ql,\n         long long qr) const {\n    if(t\
    \ == nullptr || r <= ql || qr <= l)\n      return e();\n    if(ql <= l && r <=\
    \ qr)\n      return t->value;\n    long long m = (l + r) >> 1;\n    return op(prod(t->left,\
    \ l, m, ql, qr), prod(t->right, m, r, ql, qr));\n  }\n\n  void reset(node_ptr\
    \ &t, long long l, long long r, long long ql,\n             long long qr) {\n\
    \    if(t == nullptr || r <= ql || qr <= l)\n      return;\n    if(ql <= l &&\
    \ r <= qr) {\n      t.reset();\n      return;\n    }\n    long long m = (l + r)\
    \ >> 1;\n    reset(t->left, l, m, ql, qr);\n    reset(t->right, m, r, ql, qr);\n\
    \    t->value =\n        op(t->left ? t->left->value : e(), t->right ? t->right->value\
    \ : e());\n  }\n};\n#line 5 \"test/Library_Checker/Point_Set_Range_Composite2.test.cpp\"\
    \nusing namespace std;\nusing ll = long long;\n\nconstexpr ll m93 = 998244353ll;\n\
    pair<ll, ll> op(pair<ll, ll> a, pair<ll, ll> b) { return make_pair(a.first * b.first\
    \ % m93, (a.second * b.first % m93 + b.second) % m93);}\npair<ll, ll> e() { return\
    \ make_pair(1ll, 0ll);}\n\nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n\
    \  int n, q;\n  cin >> n >> q;\n  DynamicSegmentTree<pair<ll, ll>, op, e> st(n);\n\
    \  for (int i = 0; i < n; i++) {\n    int c, d;\n    cin >> c >> d;\n    st.set(i,\
    \ make_pair(c, d));\n  }\n  while (q--) {\n    int num;\n    cin >> num;\n   \
    \ switch (num) {\n      case 0:{\n        int p;\n        ll c, d;\n        cin\
    \ >> p >> c >> d;\n        st.set(p, make_pair(c, d));\n        break;\n     \
    \ }\n      case 1:{\n        int l, r;\n        ll x;\n        cin >> l >> r >>\
    \ x;\n        auto [c, d] = st.prod(l, r);\n        cout << (c * x % m93 + d)\
    \ % m93 << endl;\n        break;\n      }\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include <iostream>\n#include \"data_structure/dynamicsegtree.hpp\"\nusing\
    \ namespace std;\nusing ll = long long;\n\nconstexpr ll m93 = 998244353ll;\npair<ll,\
    \ ll> op(pair<ll, ll> a, pair<ll, ll> b) { return make_pair(a.first * b.first\
    \ % m93, (a.second * b.first % m93 + b.second) % m93);}\npair<ll, ll> e() { return\
    \ make_pair(1ll, 0ll);}\n\nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n\
    \  int n, q;\n  cin >> n >> q;\n  DynamicSegmentTree<pair<ll, ll>, op, e> st(n);\n\
    \  for (int i = 0; i < n; i++) {\n    int c, d;\n    cin >> c >> d;\n    st.set(i,\
    \ make_pair(c, d));\n  }\n  while (q--) {\n    int num;\n    cin >> num;\n   \
    \ switch (num) {\n      case 0:{\n        int p;\n        ll c, d;\n        cin\
    \ >> p >> c >> d;\n        st.set(p, make_pair(c, d));\n        break;\n     \
    \ }\n      case 1:{\n        int l, r;\n        ll x;\n        cin >> l >> r >>\
    \ x;\n        auto [c, d] = st.prod(l, r);\n        cout << (c * x % m93 + d)\
    \ % m93 << endl;\n        break;\n      }\n    }\n  }\n}"
  dependsOn:
  - data_structure/dynamicsegtree.hpp
  isVerificationFile: true
  path: test/Library_Checker/Point_Set_Range_Composite2.test.cpp
  requiredBy: []
  timestamp: '2025-07-26 00:37:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Point_Set_Range_Composite2.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Point_Set_Range_Composite2.test.cpp
- /verify/test/Library_Checker/Point_Set_Range_Composite2.test.cpp.html
title: test/Library_Checker/Point_Set_Range_Composite2.test.cpp
---
