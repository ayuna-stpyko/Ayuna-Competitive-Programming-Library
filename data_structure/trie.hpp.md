---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/AOJ/Dictionary_ALDS1_4_C.test.cpp
    title: test/AOJ/Dictionary_ALDS1_4_C.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/trie.hpp\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <cstddef>\n#include <functional>\n#include\
    \ <string>\n#include <utility>\n#include <vector>\n\nnamespace ayuna {\n\ntemplate\
    \ <int char_size = 26, int base = 'a', typename Val = int>\nstruct Trie {\n  struct\
    \ Node {\n    std::array<int, char_size> nxt;\n    int exist = 0;\n    int accept\
    \ = 0;\n    Val val{};\n    int head = -1;\n\n    Node() { nxt.fill(-1); }\n \
    \ };\n\n  Trie() : nodes_(1) {}\n\n  void reserve(std::size_t n) { nodes_.reserve(n);\
    \ }\n\n  int add(const std::string &s) { return add(s, word_count_, nullptr);\
    \ }\n\n  int add(const std::string &s, int id) { return add(s, id, nullptr); }\n\
    \n  int add(const std::string &s, const std::function<void(Node *)> &f) {\n  \
    \  return add(s, word_count_, f);\n  }\n\n  int add(const std::string &s, int\
    \ id, const std::function<void(Node *)> &f) {\n    std::vector<int> path;\n  \
    \  path.reserve(s.size() + 1);\n    path.push_back(0);\n    for (const char ch\
    \ : s) {\n      const int c = to_index(ch);\n      int u = nodes_[path.back()].nxt[c];\n\
    \      if (u == -1) {\n        u = static_cast<int>(nodes_.size());\n        nodes_.emplace_back();\n\
    \        nodes_[path.back()].nxt[c] = u;\n      }\n      path.push_back(u);\n\
    \    }\n    for (const int t : path) nodes_[t].exist++;\n    Node &last = nodes_[path.back()];\n\
    \    last.accept++;\n    entry_id_.push_back(id);\n    entry_next_.push_back(last.head);\n\
    \    last.head = static_cast<int>(entry_id_.size()) - 1;\n    if (f) {\n     \
    \ for (auto it = path.rbegin(); it != path.rend(); ++it) f(&nodes_[*it]);\n  \
    \  }\n    word_count_++;\n    return id;\n  }\n\n  void erase(const std::string\
    \ &s) { erase(s, nullptr); }\n\n  void erase(const std::string &s, const std::function<void(Node\
    \ *)> &f) {\n    assert(count(s) > 0);\n    std::vector<int> path;\n    path.reserve(s.size()\
    \ + 1);\n    path.push_back(0);\n    for (const char ch : s) path.push_back(nodes_[path.back()].nxt[to_index(ch)]);\n\
    \    for (const int t : path) nodes_[t].exist--;\n    Node &last = nodes_[path.back()];\n\
    \    last.accept--;\n    last.head = entry_next_[last.head];\n    if (f) {\n \
    \     for (auto it = path.rbegin(); it != path.rend(); ++it) f(&nodes_[*it]);\n\
    \    }\n  }\n\n  bool exist(const std::string &s) const { return count(s) > 0;\
    \ }\n\n  int count(const std::string &s) const {\n    const int t = find(s);\n\
    \    return t == -1 ? 0 : nodes_[t].accept;\n  }\n\n  int count_prefix(const std::string\
    \ &s) const {\n    const int t = find(s);\n    return t == -1 ? 0 : nodes_[t].exist;\n\
    \  }\n\n  void query(const std::string &s, const std::function<void(int)> &f)\
    \ const {\n    for (const int t : prefix_path(s)) {\n      for (const int idx\
    \ : accept_ids(&nodes_[t])) f(idx);\n    }\n  }\n\n  void query_post(const std::string\
    \ &s, const std::function<void(int)> &f) const {\n    const std::vector<int> path\
    \ = prefix_path(s);\n    for (auto it = path.rbegin(); it != path.rend(); ++it)\
    \ {\n      for (const int idx : accept_ids(&nodes_[*it])) f(idx);\n    }\n  }\n\
    \n  std::vector<int> accept_ids(const Node *t) const {\n    std::vector<int> res;\n\
    \    res.reserve(t->accept);\n    for (int e = t->head; e != -1; e = entry_next_[e])\
    \ res.push_back(entry_id_[e]);\n    std::reverse(res.begin(), res.end());\n  \
    \  return res;\n  }\n\n  void dp(const std::function<void(Node *)> &f) {\n   \
    \ std::vector<std::pair<int, int>> st{{0, 0}};\n    while (!st.empty()) {\n  \
    \    auto &[t, c] = st.back();\n      while (c < char_size && nodes_[t].nxt[c]\
    \ == -1) c++;\n      if (c == char_size) {\n        f(&nodes_[t]);\n        st.pop_back();\n\
    \      }\n      else {\n        const int u = nodes_[t].nxt[c++];\n        st.emplace_back(u,\
    \ 0);\n      }\n    }\n  }\n\n  Node *root() { return &nodes_[0]; }\n\n  int size()\
    \ const { return nodes_[0].exist; }\n\n  int node_count() const { return static_cast<int>(nodes_.size());\
    \ }\n\nprivate:\n  std::vector<Node> nodes_;\n  std::vector<int> entry_id_;\n\
    \  std::vector<int> entry_next_;\n  int word_count_ = 0;\n\n  static int to_index(char\
    \ ch) {\n    const int c = static_cast<int>(ch) - base;\n    assert(0 <= c &&\
    \ c < char_size);\n    return c;\n  }\n\n  int find(const std::string &s) const\
    \ {\n    int t = 0;\n    for (const char ch : s) {\n      const int c = static_cast<int>(ch)\
    \ - base;\n      if (c < 0 || c >= char_size) return -1;\n      t = nodes_[t].nxt[c];\n\
    \      if (t == -1) return -1;\n    }\n    return t;\n  }\n\n  std::vector<int>\
    \ prefix_path(const std::string &s) const {\n    std::vector<int> path{0};\n \
    \   for (const char ch : s) {\n      const int c = static_cast<int>(ch) - base;\n\
    \      if (c < 0 || c >= char_size || nodes_[path.back()].nxt[c] == -1) break;\n\
    \      path.push_back(nodes_[path.back()].nxt[c]);\n    }\n    return path;\n\
    \  }\n};\n\n} // namespace ayuna\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <cstddef>\n#include <functional>\n#include <string>\n#include <utility>\n\
    #include <vector>\n\nnamespace ayuna {\n\ntemplate <int char_size = 26, int base\
    \ = 'a', typename Val = int>\nstruct Trie {\n  struct Node {\n    std::array<int,\
    \ char_size> nxt;\n    int exist = 0;\n    int accept = 0;\n    Val val{};\n \
    \   int head = -1;\n\n    Node() { nxt.fill(-1); }\n  };\n\n  Trie() : nodes_(1)\
    \ {}\n\n  void reserve(std::size_t n) { nodes_.reserve(n); }\n\n  int add(const\
    \ std::string &s) { return add(s, word_count_, nullptr); }\n\n  int add(const\
    \ std::string &s, int id) { return add(s, id, nullptr); }\n\n  int add(const std::string\
    \ &s, const std::function<void(Node *)> &f) {\n    return add(s, word_count_,\
    \ f);\n  }\n\n  int add(const std::string &s, int id, const std::function<void(Node\
    \ *)> &f) {\n    std::vector<int> path;\n    path.reserve(s.size() + 1);\n   \
    \ path.push_back(0);\n    for (const char ch : s) {\n      const int c = to_index(ch);\n\
    \      int u = nodes_[path.back()].nxt[c];\n      if (u == -1) {\n        u =\
    \ static_cast<int>(nodes_.size());\n        nodes_.emplace_back();\n        nodes_[path.back()].nxt[c]\
    \ = u;\n      }\n      path.push_back(u);\n    }\n    for (const int t : path)\
    \ nodes_[t].exist++;\n    Node &last = nodes_[path.back()];\n    last.accept++;\n\
    \    entry_id_.push_back(id);\n    entry_next_.push_back(last.head);\n    last.head\
    \ = static_cast<int>(entry_id_.size()) - 1;\n    if (f) {\n      for (auto it\
    \ = path.rbegin(); it != path.rend(); ++it) f(&nodes_[*it]);\n    }\n    word_count_++;\n\
    \    return id;\n  }\n\n  void erase(const std::string &s) { erase(s, nullptr);\
    \ }\n\n  void erase(const std::string &s, const std::function<void(Node *)> &f)\
    \ {\n    assert(count(s) > 0);\n    std::vector<int> path;\n    path.reserve(s.size()\
    \ + 1);\n    path.push_back(0);\n    for (const char ch : s) path.push_back(nodes_[path.back()].nxt[to_index(ch)]);\n\
    \    for (const int t : path) nodes_[t].exist--;\n    Node &last = nodes_[path.back()];\n\
    \    last.accept--;\n    last.head = entry_next_[last.head];\n    if (f) {\n \
    \     for (auto it = path.rbegin(); it != path.rend(); ++it) f(&nodes_[*it]);\n\
    \    }\n  }\n\n  bool exist(const std::string &s) const { return count(s) > 0;\
    \ }\n\n  int count(const std::string &s) const {\n    const int t = find(s);\n\
    \    return t == -1 ? 0 : nodes_[t].accept;\n  }\n\n  int count_prefix(const std::string\
    \ &s) const {\n    const int t = find(s);\n    return t == -1 ? 0 : nodes_[t].exist;\n\
    \  }\n\n  void query(const std::string &s, const std::function<void(int)> &f)\
    \ const {\n    for (const int t : prefix_path(s)) {\n      for (const int idx\
    \ : accept_ids(&nodes_[t])) f(idx);\n    }\n  }\n\n  void query_post(const std::string\
    \ &s, const std::function<void(int)> &f) const {\n    const std::vector<int> path\
    \ = prefix_path(s);\n    for (auto it = path.rbegin(); it != path.rend(); ++it)\
    \ {\n      for (const int idx : accept_ids(&nodes_[*it])) f(idx);\n    }\n  }\n\
    \n  std::vector<int> accept_ids(const Node *t) const {\n    std::vector<int> res;\n\
    \    res.reserve(t->accept);\n    for (int e = t->head; e != -1; e = entry_next_[e])\
    \ res.push_back(entry_id_[e]);\n    std::reverse(res.begin(), res.end());\n  \
    \  return res;\n  }\n\n  void dp(const std::function<void(Node *)> &f) {\n   \
    \ std::vector<std::pair<int, int>> st{{0, 0}};\n    while (!st.empty()) {\n  \
    \    auto &[t, c] = st.back();\n      while (c < char_size && nodes_[t].nxt[c]\
    \ == -1) c++;\n      if (c == char_size) {\n        f(&nodes_[t]);\n        st.pop_back();\n\
    \      }\n      else {\n        const int u = nodes_[t].nxt[c++];\n        st.emplace_back(u,\
    \ 0);\n      }\n    }\n  }\n\n  Node *root() { return &nodes_[0]; }\n\n  int size()\
    \ const { return nodes_[0].exist; }\n\n  int node_count() const { return static_cast<int>(nodes_.size());\
    \ }\n\nprivate:\n  std::vector<Node> nodes_;\n  std::vector<int> entry_id_;\n\
    \  std::vector<int> entry_next_;\n  int word_count_ = 0;\n\n  static int to_index(char\
    \ ch) {\n    const int c = static_cast<int>(ch) - base;\n    assert(0 <= c &&\
    \ c < char_size);\n    return c;\n  }\n\n  int find(const std::string &s) const\
    \ {\n    int t = 0;\n    for (const char ch : s) {\n      const int c = static_cast<int>(ch)\
    \ - base;\n      if (c < 0 || c >= char_size) return -1;\n      t = nodes_[t].nxt[c];\n\
    \      if (t == -1) return -1;\n    }\n    return t;\n  }\n\n  std::vector<int>\
    \ prefix_path(const std::string &s) const {\n    std::vector<int> path{0};\n \
    \   for (const char ch : s) {\n      const int c = static_cast<int>(ch) - base;\n\
    \      if (c < 0 || c >= char_size || nodes_[path.back()].nxt[c] == -1) break;\n\
    \      path.push_back(nodes_[path.back()].nxt[c]);\n    }\n    return path;\n\
    \  }\n};\n\n} // namespace ayuna\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/trie.hpp
  requiredBy: []
  timestamp: '2026-10-16 03:26:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/AOJ/Dictionary_ALDS1_4_C.test.cpp
documentation_of: data_structure/trie.hpp
layout: document
redirect_from:
- /library/data_structure/trie.hpp
- /library/data_structure/trie.hpp.html
title: data_structure/trie.hpp
---
