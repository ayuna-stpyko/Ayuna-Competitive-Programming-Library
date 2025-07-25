---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Point_Add_Range_Sum.test.cpp
    title: test/Library_Checker/Point_Add_Range_Sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/Library_Checker/Point_Set_Range_Composite.test.cpp
    title: test/Library_Checker/Point_Set_Range_Composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/segmenttree.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n#include <functional>\n\ntemplate <class S, auto op, auto e> struct\
    \ SegmentTree {\n  SegmentTree(int n) : SegmentTree(std::vector<S>(n, e())) {}\n\
    \  SegmentTree(const std::vector<S> &v) : _n(v.size()) {\n    size = bit_ceil((unsigned\
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
    \    return x;\n  }\n};\n"
  code: "#include <cassert>\n#include <vector>\n#include <functional>\n\ntemplate\
    \ <class S, auto op, auto e> struct SegmentTree {\n  SegmentTree(int n) : SegmentTree(std::vector<S>(n,\
    \ e())) {}\n  SegmentTree(const std::vector<S> &v) : _n(v.size()) {\n    size\
    \ = bit_ceil((unsigned int)_n);\n    log = __builtin_ctz((unsigned int)size);\n\
    \    d.resize(size << 1, e());\n    for (int i = 0; i < _n; i++) d[size + i] =\
    \ v[i];\n    for (int i = size - 1; i >= 1; i--) update(i);\n  }\n\n  void set(int\
    \ p, S x){\n    assert(0 <= p && p < _n);\n    p += size;\n    d[p] = x;\n   \
    \ for (int i = 1; i <= log; i++) update(p >> i);\n  }\n\n  S get(const int p)\
    \ const{\n    assert(0 <= p && p < _n);\n    return d[p + size];\n  }\n\n  S prod(int\
    \ l, int r) const{\n    assert(0 <= l && l <= r && r <= _n);\n    S sml = e(),\
    \ smr = e();\n    l += size;\n    r += size;\n    while (l < r) {\n      if (l\
    \ & 1) sml = op(sml, d[l++]);\n      if (r & 1) smr = op(d[--r], smr);\n     \
    \ l >>= 1;\n      r >>= 1;\n    }\n    return op(sml, smr);\n  }\n\n  S all_prod()\
    \ const{\n    return d[1];\n  }\n\nprivate:\n  int _n, size, log;\n  std::vector<S>\
    \ d;\n  void update(int i) { d[i] = op(d[i << 1], d[i << 1 | 1]); }\n\n  unsigned\
    \ int bit_ceil(unsigned int n) {\n    unsigned int x = 1;\n    while (x < (unsigned\
    \ int)(n)) x <<= 1;\n    return x;\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segmenttree.hpp
  requiredBy: []
  timestamp: '2024-11-27 18:01:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/Library_Checker/Point_Set_Range_Composite.test.cpp
  - test/Library_Checker/Point_Add_Range_Sum.test.cpp
documentation_of: data_structure/segmenttree.hpp
layout: document
redirect_from:
- /library/data_structure/segmenttree.hpp
- /library/data_structure/segmenttree.hpp.html
title: data_structure/segmenttree.hpp
---
