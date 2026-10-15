#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace ayuna {

template <typename T>
class PersistentQueue {
public:
  PersistentQueue() = default;

  bool empty() const { return sz == 0; }

  int size() const { return sz; }

  T front() const {
    assert(!empty());
    return nodes[ancestor(last, nodes[last].depth - sz + 1)].value;
  }

  T back() const {
    assert(!empty());
    return nodes[last].value;
  }

  PersistentQueue push(const T &x) const {
    int p = last;
    if (p == -1) {
      int t = static_cast<int>(nodes.size());
      nodes.push_back(Node{x, t, t, 0});
      return PersistentQueue(t, sz + 1);
    }
    int j = nodes[p].jump, jj = nodes[j].jump;
    int dp = nodes[p].depth, dj = nodes[j].depth, djj = nodes[jj].depth;
    int jump = dp - dj == dj - djj ? jj : p;
    nodes.push_back(Node{x, p, jump, dp + 1});
    return PersistentQueue(static_cast<int>(nodes.size()) - 1, sz + 1);
  }

  PersistentQueue pop() const {
    assert(!empty());
    return PersistentQueue(last, sz - 1);
  }

  static void reserve(std::size_t node_count) { nodes.reserve(node_count); }

  static void clear() { std::vector<Node>().swap(nodes); }

private:
  struct Node {
    T value;
    int parent;
    int jump;
    int depth;
  };

  static inline std::vector<Node> nodes;

  int last = -1;
  int sz = 0;

  PersistentQueue(int last_, int sz_) : last(last_), sz(sz_) {}

  static int ancestor(int t, int d) {
    while (nodes[t].depth > d) {
      int j = nodes[t].jump;
      t = nodes[j].depth >= d ? j : nodes[t].parent;
    }
    return t;
  }
};

} // namespace ayuna
