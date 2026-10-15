---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: persistent/persistentqueue.hpp
    title: persistent/persistentqueue.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_queue
    links:
    - https://judge.yosupo.jp/problem/persistent_queue
  bundledCode: "#line 1 \"test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n#include\
    \ <iostream>\n#include <vector>\n#line 2 \"persistent/persistentqueue.hpp\"\n\n\
    #include <cassert>\n#include <cstddef>\n#line 6 \"persistent/persistentqueue.hpp\"\
    \n\nnamespace ayuna {\n\ntemplate <typename T>\nclass PersistentQueue {\npublic:\n\
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
    \    }\n    return t;\n  }\n};\n\n} // namespace ayuna\n#line 6 \"test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp\"\
    \nusing namespace std;\nusing ll = long long;\n\nint main() {\n  cin.tie(0);\n\
    \  ios::sync_with_stdio(0);\n  int q;\n  cin >> q;\n  vector<ayuna::PersistentQueue<ll>>\
    \ history(q + 1);\n  for (int i = 1; i <= q; i++) {\n    int num, t;\n    cin\
    \ >> num >> t;\n    if (num == 0) {\n      ll x;\n      cin >> x;\n      history[i]\
    \ = history[t + 1].push(x);\n    }\n    else {\n      ll ans = history[t + 1].front();\n\
    \      history[i] = history[t + 1].pop();\n      cout << ans << '\\n';\n    }\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n\n\
    #include <iostream>\n#include <vector>\n#include \"persistent/persistentqueue.hpp\"\
    \nusing namespace std;\nusing ll = long long;\n\nint main() {\n  cin.tie(0);\n\
    \  ios::sync_with_stdio(0);\n  int q;\n  cin >> q;\n  vector<ayuna::PersistentQueue<ll>>\
    \ history(q + 1);\n  for (int i = 1; i <= q; i++) {\n    int num, t;\n    cin\
    \ >> num >> t;\n    if (num == 0) {\n      ll x;\n      cin >> x;\n      history[i]\
    \ = history[t + 1].push(x);\n    }\n    else {\n      ll ans = history[t + 1].front();\n\
    \      history[i] = history[t + 1].pop();\n      cout << ans << '\\n';\n    }\n\
    \  }\n}\n"
  dependsOn:
  - persistent/persistentqueue.hpp
  isVerificationFile: true
  path: test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
  requiredBy: []
  timestamp: '2026-10-16 03:26:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
- /verify/test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp.html
title: test/Library_Checker/Data_Structure/Persistent_Queue.test.cpp
---
