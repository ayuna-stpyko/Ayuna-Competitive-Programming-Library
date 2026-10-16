#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <vector>

namespace ayuna {

template <class S, auto op, auto e>
  requires requires(S a, S b) {
    { op(a, b) } -> std::same_as<S>;
    { e() } -> std::same_as<S>;
  }
class PersistentSegtree {
public:
  PersistentSegtree() : PersistentSegtree(0, empty_tag{}) {}

  explicit PersistentSegtree(int n_) : PersistentSegtree(n_, empty_tag{}) {
    if (n == 0)
      return;
    root = alloc_leaf(e());
    for (int d = 0; d < log; d++)
      root = alloc_internal(root, root);
  }

  explicit PersistentSegtree(const std::vector<S> &v)
      : PersistentSegtree(static_cast<int>(v.size()), empty_tag{}) {
    if (n == 0)
      return;
    std::vector<int> cur(1u << log);
    int pad = n < static_cast<int>(cur.size()) ? alloc_leaf(e()) : -1;
    for (int i = 0; i < static_cast<int>(cur.size()); i++)
      cur[i] = i < n ? alloc_leaf(v[i]) : pad;
    while (cur.size() > 1) {
      for (std::size_t i = 0; i < cur.size() / 2; i++)
        cur[i] = alloc_internal(cur[2 * i], cur[2 * i + 1]);
      cur.resize(cur.size() / 2);
    }
    root = cur[0];
  }

  int size() const { return n; }

  S get(int k) const {
    assert(0 <= k && k < n);
    int t = root;
    for (int d = log - 1; d >= 0; d--)
      t = (k >> d) & 1 ? pool[t].right : pool[t].left;
    return pool[t].value;
  }

  PersistentSegtree set(int k, const S &x) const {
    assert(0 <= k && k < n);
    int path[32];
    int t = root;
    for (int d = log - 1; d >= 0; d--) {
      path[d] = t;
      t = (k >> d) & 1 ? pool[t].right : pool[t].left;
    }
    t = alloc_leaf(x);
    for (int d = 0; d < log; d++) {
      const Node &p = pool[path[d]];
      int l = p.left, r = p.right;
      t = (k >> d) & 1 ? alloc_internal(l, t) : alloc_internal(t, r);
    }
    PersistentSegtree res(n, empty_tag{});
    res.root = t;
    return res;
  }

  PersistentSegtree assign(const PersistentSegtree &src, int l, int r) const {
    assert(n == src.n);
    assert(0 <= l && l <= r && r <= n);
    PersistentSegtree res(n, empty_tag{});
    res.root = assign(root, src.root, 0, 1u << log, static_cast<unsigned int>(l),
                      static_cast<unsigned int>(r));
    return res;
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r)
      return e();
    return prod(root, 0, 1u << log, static_cast<unsigned int>(l),
                static_cast<unsigned int>(r));
  }

  S all_prod() const { return root == -1 ? e() : pool[root].value; }

  template <bool (*f)(S)>
  int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }

  template <class F>
  int max_right(int l, F f) const {
    assert(0 <= l && l <= n);
    assert(f(e()));
    if (l == n)
      return n;
    S sum = e();
    return std::min(n, static_cast<int>(max_right(
                           root, 0, 1u << log, static_cast<unsigned int>(l), sum, f)));
  }

  template <class F>
  int max_right_pair(int l, const PersistentSegtree &other, F f) const {
    assert(n == other.n);
    assert(0 <= l && l <= n);
    assert(f(e(), e()));
    if (l == n)
      return n;
    S sum = e(), other_sum = e();
    return std::min(n, static_cast<int>(max_right_pair(
                           root, other.root, 0, 1u << log,
                           static_cast<unsigned int>(l), sum, other_sum, f)));
  }

  template <bool (*f)(S)>
  int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }

  template <class F>
  int min_left(int r, F f) const {
    assert(0 <= r && r <= n);
    assert(f(e()));
    if (r == 0)
      return 0;
    S sum = e();
    return static_cast<int>(
        min_left(root, 0, 1u << log, static_cast<unsigned int>(r), sum, f));
  }

  template <class F>
  int min_left_pair(int r, const PersistentSegtree &other, F f) const {
    assert(n == other.n);
    assert(0 <= r && r <= n);
    assert(f(e(), e()));
    if (r == 0)
      return 0;
    S sum = e(), other_sum = e();
    return static_cast<int>(min_left_pair(root, other.root, 0, 1u << log,
                                          static_cast<unsigned int>(r), sum,
                                          other_sum, f));
  }

  static void reserve(std::size_t node_count) { pool.reserve(node_count); }

  static void clear() { std::vector<Node>().swap(pool); }

private:
  struct Node {
    int left = -1;
    int right = -1;
    S value{};
  };

  static inline std::vector<Node> pool;

  int n;
  int log;
  int root;

  struct empty_tag {};

  PersistentSegtree(int n_, empty_tag)
      : n(n_),
        log(std::countr_zero(std::bit_ceil(static_cast<unsigned int>(std::max(1, n_))))),
        root(-1) {
    assert(n >= 0);
  }

  static int alloc_leaf(const S &value) {
    pool.push_back(Node{-1, -1, value});
    return static_cast<int>(pool.size()) - 1;
  }

  static int alloc_internal(int l, int r) {
    pool.push_back(Node{l, r, op(pool[l].value, pool[r].value)});
    return static_cast<int>(pool.size()) - 1;
  }

  static int assign(int dst, int src, unsigned int l, unsigned int r,
                    unsigned int ql, unsigned int qr) {
    if (r <= ql || qr <= l)
      return dst;
    if (ql <= l && r <= qr)
      return src;

    unsigned int m = (l + r) / 2;
    int dl = pool[dst].left, dr = pool[dst].right;
    int left = assign(dl, pool[src].left, l, m, ql, qr);
    int right = assign(dr, pool[src].right, m, r, ql, qr);
    if (left == dl && right == dr)
      return dst;
    return alloc_internal(left, right);
  }

  static S prod(int t, unsigned int l, unsigned int r, unsigned int ql,
                unsigned int qr) {
    if (r <= ql || qr <= l)
      return e();
    if (ql <= l && r <= qr)
      return pool[t].value;

    unsigned int m = (l + r) / 2;
    return op(prod(pool[t].left, l, m, ql, qr),
              prod(pool[t].right, m, r, ql, qr));
  }

  template <class F>
  static unsigned int max_right(int t, unsigned int l, unsigned int r,
                                unsigned int ql, S &sum, F f) {
    if (r <= ql)
      return r;
    if (ql <= l) {
      if (f(op(sum, pool[t].value))) {
        sum = op(sum, pool[t].value);
        return r;
      }
      if (r - l == 1)
        return l;
    }

    unsigned int m = (l + r) / 2;
    unsigned int res = max_right(pool[t].left, l, m, ql, sum, f);
    if (res != m)
      return res;
    return max_right(pool[t].right, m, r, ql, sum, f);
  }

  template <class F>
  static unsigned int max_right_pair(int t, int u, unsigned int l, unsigned int r,
                                     unsigned int ql, S &sum, S &other_sum, F f) {
    if (r <= ql)
      return r;
    if (ql <= l) {
      S x = op(sum, pool[t].value), y = op(other_sum, pool[u].value);
      if (f(x, y)) {
        sum = x;
        other_sum = y;
        return r;
      }
      if (r - l == 1)
        return l;
    }

    unsigned int m = (l + r) / 2;
    unsigned int res =
        max_right_pair(pool[t].left, pool[u].left, l, m, ql, sum, other_sum, f);
    if (res != m)
      return res;
    return max_right_pair(pool[t].right, pool[u].right, m, r, ql, sum, other_sum, f);
  }

  template <class F>
  static unsigned int min_left(int t, unsigned int l, unsigned int r,
                               unsigned int qr, S &sum, F f) {
    if (qr <= l)
      return l;
    if (r <= qr) {
      if (f(op(pool[t].value, sum))) {
        sum = op(pool[t].value, sum);
        return l;
      }
      if (r - l == 1)
        return r;
    }

    unsigned int m = (l + r) / 2;
    unsigned int res = min_left(pool[t].right, m, r, qr, sum, f);
    if (res != m)
      return res;
    return min_left(pool[t].left, l, m, qr, sum, f);
  }

  template <class F>
  static unsigned int min_left_pair(int t, int u, unsigned int l, unsigned int r,
                                    unsigned int qr, S &sum, S &other_sum, F f) {
    if (qr <= l)
      return l;
    if (r <= qr) {
      S x = op(pool[t].value, sum), y = op(pool[u].value, other_sum);
      if (f(x, y)) {
        sum = x;
        other_sum = y;
        return l;
      }
      if (r - l == 1)
        return r;
    }

    unsigned int m = (l + r) / 2;
    unsigned int res =
        min_left_pair(pool[t].right, pool[u].right, m, r, qr, sum, other_sum, f);
    if (res != m)
      return res;
    return min_left_pair(pool[t].left, pool[u].left, l, m, qr, sum, other_sum, f);
  }
};

} // namespace ayuna
