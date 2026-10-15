#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <vector>

namespace ayuna {

template <typename T>
class PersistentArray {
public:
  PersistentArray() : PersistentArray(Raw{}, 0, -1) {}

  explicit PersistentArray(int n_, const T &x = T{}) : PersistentArray(Raw{}, n_, -1) {
    if (n == 0)
      return;
    root = alloc_leaf(x);
    for (int d = 0; d < log; d++)
      root = alloc_node(root, root);
  }

  explicit PersistentArray(const std::vector<T> &v)
      : PersistentArray(Raw{}, static_cast<int>(v.size()), -1) {
    if (n == 0)
      return;
    int base = static_cast<int>(leaves.size());
    leaves.insert(leaves.end(), v.begin(), v.end());
    std::vector<int> cur(1u << log);
    for (int i = 0; i < static_cast<int>(cur.size()); i++)
      cur[i] = base + std::min(i, n - 1);
    while (cur.size() > 1) {
      for (std::size_t i = 0; i < cur.size() / 2; i++)
        cur[i] = alloc_node(cur[2 * i], cur[2 * i + 1]);
      cur.resize(cur.size() / 2);
    }
    root = cur[0];
  }

  int size() const { return n; }

  T get(int k) const {
    assert(0 <= k && k < n);
    int t = root;
    for (int d = log - 1; d >= 0; d--)
      t = nodes[t].ch[(k >> d) & 1];
    return leaves[t];
  }

  PersistentArray set(int k, const T &x) const {
    assert(0 <= k && k < n);
    int leaf = alloc_leaf(x);
    if (log == 0)
      return PersistentArray(Raw{}, n, leaf);
    int base = static_cast<int>(nodes.size());
    nodes.resize(base + log);
    int t = root;
    for (int d = log - 1, i = base; d >= 0; d--, i++) {
      int b = (k >> d) & 1;
      nodes[i] = nodes[t];
      t = nodes[t].ch[b];
      nodes[i].ch[b] = d > 0 ? i + 1 : leaf;
    }
    return PersistentArray(Raw{}, n, base);
  }

  PersistentArray assign(const PersistentArray &src, int l, int r) const {
    assert(n == src.n);
    assert(0 <= l && l <= r && r <= n);
    return PersistentArray(Raw{}, n,
                           assign(root, src.root, 0, 1u << log,
                                  static_cast<unsigned int>(l),
                                  static_cast<unsigned int>(r)));
  }

  static void reserve(std::size_t node_count, std::size_t leaf_count) {
    nodes.reserve(node_count);
    leaves.reserve(leaf_count);
  }

  static void clear() {
    std::vector<Node>().swap(nodes);
    std::vector<T>().swap(leaves);
  }

private:
  struct Raw {};

  struct Node {
    int ch[2];
  };

  static inline std::vector<Node> nodes;
  static inline std::vector<T> leaves;

  int n;
  int log;
  int root;

  PersistentArray(Raw, int n_, int root_)
      : n(n_),
        log(std::countr_zero(std::bit_ceil(static_cast<unsigned int>(std::max(1, n_))))),
        root(root_) {
    assert(n >= 0);
  }

  static int alloc_leaf(const T &x) {
    leaves.push_back(x);
    return static_cast<int>(leaves.size()) - 1;
  }

  static int alloc_node(int l, int r) {
    nodes.push_back(Node{{l, r}});
    return static_cast<int>(nodes.size()) - 1;
  }

  static int assign(int dst, int src, unsigned int l, unsigned int r,
                    unsigned int ql, unsigned int qr) {
    if (r <= ql || qr <= l)
      return dst;
    if (ql <= l && r <= qr)
      return src;

    unsigned int m = (l + r) / 2;
    Node d = nodes[dst], s = nodes[src];
    int left = assign(d.ch[0], s.ch[0], l, m, ql, qr);
    int right = assign(d.ch[1], s.ch[1], m, r, ql, qr);
    if (left == d.ch[0] && right == d.ch[1])
      return dst;
    return alloc_node(left, right);
  }
};

} // namespace ayuna
