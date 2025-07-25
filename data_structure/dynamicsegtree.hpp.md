---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Point_Add_Range_Sum2.test.cpp
    title: test/Library_Checker/Point_Add_Range_Sum2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Point_Set_Range_Composite2.test.cpp
    title: test/Library_Checker/Point_Set_Range_Composite2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/dynamicsegtree.hpp\"\n#include <cassert>\n\
    #include <memory>\n\ntemplate <class S, S (*op)(S, S), S (*e)()>\nclass DynamicSegmentTree\
    \ {\npublic:\n  DynamicSegmentTree(long long _n) : n(_n), root(nullptr) {}\n\n\
    \  void set(long long p, S x) {\n    assert(p < n);\n    set(root, 0, n, p, x);\n\
    \  }\n  S get(long long p) const {\n    assert(p < n);\n    return get(root, 0,\
    \ n, p);\n  }\n  S prod(long long l, long long r) const {\n    assert(l <= r &&\
    \ r <= n);\n    return prod(root, 0, n, l, r);\n  }\n\n  S all_prod() const {\
    \ return root ? root->value : e(); }\n\n  void reset(long long l, long long r)\
    \ {\n    assert(l <= r && r <= n);\n    reset(root, 0, n, l, r);\n  }\n\nprivate:\n\
    \  struct node;\n  using node_ptr = std::unique_ptr<node>;\n\n  struct node {\n\
    \    S value;\n    node_ptr left, right;\n    node() : value(e()), left(nullptr),\
    \ right(nullptr) {}\n    node(S v) : value(v), left(nullptr), right(nullptr) {}\n\
    \  };\n\n  long long n;\n  node_ptr root;\n\n  void set(node_ptr &t, long long\
    \ l, long long r, long long p, S x) {\n    if(t == nullptr)\n      t = std::make_unique<node>();\n\
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
    \ : e());\n  }\n};\n"
  code: "#include <cassert>\n#include <memory>\n\ntemplate <class S, S (*op)(S, S),\
    \ S (*e)()>\nclass DynamicSegmentTree {\npublic:\n  DynamicSegmentTree(long long\
    \ _n) : n(_n), root(nullptr) {}\n\n  void set(long long p, S x) {\n    assert(p\
    \ < n);\n    set(root, 0, n, p, x);\n  }\n  S get(long long p) const {\n    assert(p\
    \ < n);\n    return get(root, 0, n, p);\n  }\n  S prod(long long l, long long\
    \ r) const {\n    assert(l <= r && r <= n);\n    return prod(root, 0, n, l, r);\n\
    \  }\n\n  S all_prod() const { return root ? root->value : e(); }\n\n  void reset(long\
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
    \ : e());\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/dynamicsegtree.hpp
  requiredBy: []
  timestamp: '2025-07-26 00:37:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/Library_Checker/Point_Add_Range_Sum2.test.cpp
  - test/Library_Checker/Point_Set_Range_Composite2.test.cpp
documentation_of: data_structure/dynamicsegtree.hpp
layout: document
redirect_from:
- /library/data_structure/dynamicsegtree.hpp
- /library/data_structure/dynamicsegtree.hpp.html
title: data_structure/dynamicsegtree.hpp
---
