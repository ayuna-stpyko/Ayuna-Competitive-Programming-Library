---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/lowestcommonancestor.hpp
    title: tree/lowestcommonancestor.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/jump_on_tree
    links:
    - https://judge.yosupo.jp/problem/jump_on_tree
  bundledCode: "#line 1 \"test/Library_Checker/Jump_on_Tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/jump_on_tree\"\n\n#include <iostream>\n#line\
    \ 1 \"tree/lowestcommonancestor.hpp\"\n#include <vector>\n#include <tuple>\n#include\
    \ <queue>\n#include <algorithm>\n#include <cassert>\n\nstruct LowestCommonAncestor\
    \ {\npublic:\n  std::vector<std::vector<int>> parents;\n  std::vector<int> depth;\n\
    \  int lg = 0;\n\n  LowestCommonAncestor(std::vector<std::vector<int>> G, int\
    \ root = 0) : graph(G), r(root) {\n    n = G.size();\n    assert(0 <= root &&\
    \ root < n);\n    depth.resize(n, inf);\n    build();\n  }\n\n  void build(){\n\
    \    while ((1 << lg) < n) lg++;\n    parents.resize(lg + 1, std::vector<int>(n));\n\
    \    std::queue<int> que;\n    que.emplace(r);\n    depth[r] = 0;\n    parents[0][r]\
    \ = -1;\n    while (!que.empty()) {\n      int now = que.front();\n      que.pop();\n\
    \      for(const int &to: graph[now]) {\n        if (depth[to] == inf) {\n   \
    \       depth[to] = depth[now] + 1;\n          que.emplace(to);\n          parents[0][to]\
    \ = now;\n        }\n      }\n    }\n    for (int t = 0; t < lg; t++) {\n    \
    \  for (int i = 0; i < n; i++) {\n        if (parents[t][i] == -1)\n         \
    \ parents[t + 1][i] = -1;\n        else\n          parents[t + 1][i] = parents[t][parents[t][i]];\n\
    \      }\n    }\n  }\n\n  int lca(int a, int b){\n    assert(0 <= a && a < n);\n\
    \    assert(0 <= b && b < n);\n\n    if (depth[a] > depth[b]) std::swap(a, b);\n\
    \    while (depth[a] != depth[b]) {\n      for (int to = lg; to >= 0; to--) {\n\
    \        if (depth[b] - (1 << to) >= depth[a]) {\n          b = parents[to][b];\n\
    \          break;\n        }\n      }\n    }\n    if (a == b) return a;\n    for\
    \ (int to = lg; to >= 0; to--) {\n      if (parents[to][a] != parents[to][b])\
    \ {\n        a = parents[to][a];\n        b = parents[to][b];\n      }\n    }\n\
    \    return parents[0][a];\n  }\n\n  int distance(int u, int v) {\n    assert(0\
    \ <= u && u < n);\n    assert(0 <= v && v < n);\n    return depth[u] + depth[v]\
    \ - depth[lca(u, v)] * 2;\n  }\n\n  int la(int u, int k) {\n    assert(0 <= u\
    \ && u < n);\n    assert(k >= 0);\n    if (depth[u] < k) return -1;\n    for (int\
    \ i = 0; i <= lg; i++) {\n      if ((k >> i) & 1) {\n        k -= (1 << i);\n\
    \        u = parents[i][u];\n      }\n      if (k == 0) break;\n    }\n    return\
    \ u;\n  }\n\n  int jumpto(int u, int v, int k) {\n    assert(0 <= u && u < n);\n\
    \    assert(0 <= v && v < n);\n    assert(k >= 0);\n    int l = lca(u, v);\n \
    \   if (depth[u] - depth[l] >= k)\n      return la(u, k);\n    else {\n      k\
    \ -= (depth[u] - depth[l]);\n      int d = depth[v] - depth[l];\n      if (d -\
    \ k < 0) return -1;\n      else return la(v, d - k);\n    }\n  }\n\nprivate:\n\
    \  int n;\n  std::vector<std::vector<int>> graph;\n  int r;\n  const int inf =\
    \ 1 << 29;\n};\n#line 5 \"test/Library_Checker/Jump_on_Tree.test.cpp\"\nusing\
    \ namespace std;\n\nint main(){\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n \
    \ int n, q;\n  cin >> n >> q;\n  vector<vector<int>> graph(n);\n  for (int i =\
    \ 0; i < n - 1; i++){\n    int a, b;\n    cin >> a >> b;\n    graph[a].push_back(b);\n\
    \    graph[b].push_back(a);\n  }\n\n  LowestCommonAncestor lca(graph);\n\n  while(q--){\n\
    \    int s, t, i;\n    cin >> s >> t >> i;\n    cout << lca.jumpto(s, t, i) <<\
    \ endl;\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n\n#include\
    \ <iostream>\n#include \"tree/lowestcommonancestor.hpp\"\nusing namespace std;\n\
    \nint main(){\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n  int n, q;\n  cin >>\
    \ n >> q;\n  vector<vector<int>> graph(n);\n  for (int i = 0; i < n - 1; i++){\n\
    \    int a, b;\n    cin >> a >> b;\n    graph[a].push_back(b);\n    graph[b].push_back(a);\n\
    \  }\n\n  LowestCommonAncestor lca(graph);\n\n  while(q--){\n    int s, t, i;\n\
    \    cin >> s >> t >> i;\n    cout << lca.jumpto(s, t, i) << endl;\n  }\n}\n"
  dependsOn:
  - tree/lowestcommonancestor.hpp
  isVerificationFile: true
  path: test/Library_Checker/Jump_on_Tree.test.cpp
  requiredBy: []
  timestamp: '2024-10-28 02:38:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Jump_on_Tree.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Jump_on_Tree.test.cpp
- /verify/test/Library_Checker/Jump_on_Tree.test.cpp.html
title: test/Library_Checker/Jump_on_Tree.test.cpp
---
