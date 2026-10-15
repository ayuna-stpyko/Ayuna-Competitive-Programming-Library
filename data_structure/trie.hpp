#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace ayuna {

template <int char_size = 26, int base = 'a', typename Val = int>
struct Trie {
  struct Node {
    std::array<int, char_size> nxt;
    int exist = 0;
    int accept = 0;
    Val val{};
    int head = -1;

    Node() { nxt.fill(-1); }
  };

  Trie() : nodes_(1) {}

  void reserve(std::size_t n) { nodes_.reserve(n); }

  int add(const std::string &s) { return add(s, word_count_, nullptr); }

  int add(const std::string &s, int id) { return add(s, id, nullptr); }

  int add(const std::string &s, const std::function<void(Node *)> &f) {
    return add(s, word_count_, f);
  }

  int add(const std::string &s, int id, const std::function<void(Node *)> &f) {
    std::vector<int> path;
    path.reserve(s.size() + 1);
    path.push_back(0);
    for (const char ch : s) {
      const int c = to_index(ch);
      int u = nodes_[path.back()].nxt[c];
      if (u == -1) {
        u = static_cast<int>(nodes_.size());
        nodes_.emplace_back();
        nodes_[path.back()].nxt[c] = u;
      }
      path.push_back(u);
    }
    for (const int t : path) nodes_[t].exist++;
    Node &last = nodes_[path.back()];
    last.accept++;
    entry_id_.push_back(id);
    entry_next_.push_back(last.head);
    last.head = static_cast<int>(entry_id_.size()) - 1;
    if (f) {
      for (auto it = path.rbegin(); it != path.rend(); ++it) f(&nodes_[*it]);
    }
    word_count_++;
    return id;
  }

  void erase(const std::string &s) { erase(s, nullptr); }

  void erase(const std::string &s, const std::function<void(Node *)> &f) {
    assert(count(s) > 0);
    std::vector<int> path;
    path.reserve(s.size() + 1);
    path.push_back(0);
    for (const char ch : s) path.push_back(nodes_[path.back()].nxt[to_index(ch)]);
    for (const int t : path) nodes_[t].exist--;
    Node &last = nodes_[path.back()];
    last.accept--;
    last.head = entry_next_[last.head];
    if (f) {
      for (auto it = path.rbegin(); it != path.rend(); ++it) f(&nodes_[*it]);
    }
  }

  bool exist(const std::string &s) const { return count(s) > 0; }

  int count(const std::string &s) const {
    const int t = find(s);
    return t == -1 ? 0 : nodes_[t].accept;
  }

  int count_prefix(const std::string &s) const {
    const int t = find(s);
    return t == -1 ? 0 : nodes_[t].exist;
  }

  void query(const std::string &s, const std::function<void(int)> &f) const {
    for (const int t : prefix_path(s)) {
      for (const int idx : accept_ids(&nodes_[t])) f(idx);
    }
  }

  void query_post(const std::string &s, const std::function<void(int)> &f) const {
    const std::vector<int> path = prefix_path(s);
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      for (const int idx : accept_ids(&nodes_[*it])) f(idx);
    }
  }

  std::vector<int> accept_ids(const Node *t) const {
    std::vector<int> res;
    res.reserve(t->accept);
    for (int e = t->head; e != -1; e = entry_next_[e]) res.push_back(entry_id_[e]);
    std::reverse(res.begin(), res.end());
    return res;
  }

  void dp(const std::function<void(Node *)> &f) {
    std::vector<std::pair<int, int>> st{{0, 0}};
    while (!st.empty()) {
      auto &[t, c] = st.back();
      while (c < char_size && nodes_[t].nxt[c] == -1) c++;
      if (c == char_size) {
        f(&nodes_[t]);
        st.pop_back();
      }
      else {
        const int u = nodes_[t].nxt[c++];
        st.emplace_back(u, 0);
      }
    }
  }

  Node *root() { return &nodes_[0]; }

  int size() const { return nodes_[0].exist; }

  int node_count() const { return static_cast<int>(nodes_.size()); }

private:
  std::vector<Node> nodes_;
  std::vector<int> entry_id_;
  std::vector<int> entry_next_;
  int word_count_ = 0;

  static int to_index(char ch) {
    const int c = static_cast<int>(ch) - base;
    assert(0 <= c && c < char_size);
    return c;
  }

  int find(const std::string &s) const {
    int t = 0;
    for (const char ch : s) {
      const int c = static_cast<int>(ch) - base;
      if (c < 0 || c >= char_size) return -1;
      t = nodes_[t].nxt[c];
      if (t == -1) return -1;
    }
    return t;
  }

  std::vector<int> prefix_path(const std::string &s) const {
    std::vector<int> path{0};
    for (const char ch : s) {
      const int c = static_cast<int>(ch) - base;
      if (c < 0 || c >= char_size || nodes_[path.back()].nxt[c] == -1) break;
      path.push_back(nodes_[path.back()].nxt[c]);
    }
    return path;
  }
};

} // namespace ayuna
