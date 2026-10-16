#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <vector>

namespace ayuna {

template <class S, auto op, auto e, class F, auto mapping, auto composition,
          auto id>
  requires requires(S a, S b, F f, F g) {
    { op(a, b) } -> std::same_as<S>;
    { e() } -> std::same_as<S>;
    { mapping(f, a) } -> std::same_as<S>;
    { composition(f, g) } -> std::same_as<F>;
    { id() } -> std::same_as<F>;
  }
class PersistentLazySegtree {
  static_assert(std::equality_comparable<F>,
                "F needs operator== (e.g. bool operator==(const F &) const = default;)");

public:
  PersistentLazySegtree() : PersistentLazySegtree(0, empty_tag{}) {}

  explicit PersistentLazySegtree(int n_) : PersistentLazySegtree(n_, empty_tag{}) {
    if (n == 0)
      return;
    root = alloc_leaf(e());
    for (unsigned int w = 1; w < len; w *= 2)
      root = alloc_internal(root, root);
  }

  explicit PersistentLazySegtree(const std::vector<S> &v)
      : PersistentLazySegtree(static_cast<int>(v.size()), empty_tag{}) {
    if (n == 0)
      return;
    std::vector<int> cur(len);
    int pad = n < static_cast<int>(len) ? alloc_leaf(e()) : -1;
    for (int i = 0; i < static_cast<int>(len); i++)
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
    return get(root, 0, len, static_cast<unsigned int>(k), id());
  }

  PersistentLazySegtree set(int k, const S &x) const {
    assert(0 <= k && k < n);
    PersistentLazySegtree res(n, empty_tag{});
    res.root = set(root, 0, len, static_cast<unsigned int>(k), x, id());
    return res;
  }

  PersistentLazySegtree apply(int l, int r, const F &f) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r)
      return *this;
    PersistentLazySegtree res(n, empty_tag{});
    res.root = apply(root, 0, len, static_cast<unsigned int>(l),
                     static_cast<unsigned int>(r), f, id());
    return res;
  }

  PersistentLazySegtree assign(const PersistentLazySegtree &src, int l,
                               int r) const {
    assert(n == src.n);
    assert(0 <= l && l <= r && r <= n);
    if (l == r)
      return *this;
    if (l == 0 && r == n)
      return src;
    PersistentLazySegtree res(n, empty_tag{});
    res.root = assign(root, src.root, 0, len, static_cast<unsigned int>(l),
                      static_cast<unsigned int>(r), id(), id());
    return res;
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r)
      return e();
    return prod(root, 0, len, static_cast<unsigned int>(l),
                static_cast<unsigned int>(r), id());
  }

  S all_prod() const { return root == -1 ? e() : pool[root].value; }

  template <bool (*f)(S)>
  int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }

  template <class G>
  int max_right(int l, G g) const {
    assert(0 <= l && l <= n);
    assert(g(e()));
    if (l == n)
      return n;
    S sum = e();
    return std::min(n, static_cast<int>(max_right(root, 0, len,
                                                  static_cast<unsigned int>(l),
                                                  sum, g, id())));
  }

  template <bool (*f)(S)>
  int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }

  template <class G>
  int min_left(int r, G g) const {
    assert(0 <= r && r <= n);
    assert(g(e()));
    if (r == 0)
      return 0;
    S sum = e();
    return static_cast<int>(
        min_left(root, 0, len, static_cast<unsigned int>(r), sum, g, id()));
  }

  template <class G>
  int max_right_pair(int l, const PersistentLazySegtree &other, G g) const {
    assert(n == other.n);
    assert(0 <= l && l <= n);
    assert(g(e(), e()));
    if (l == n)
      return n;
    S sum = e(), other_sum = e();
    return std::min(n, static_cast<int>(max_right_pair(
                           root, other.root, 0, len, static_cast<unsigned int>(l),
                           sum, other_sum, g, id(), id())));
  }

  template <class G>
  int min_left_pair(int r, const PersistentLazySegtree &other, G g) const {
    assert(n == other.n);
    assert(0 <= r && r <= n);
    assert(g(e(), e()));
    if (r == 0)
      return 0;
    S sum = e(), other_sum = e();
    return static_cast<int>(min_left_pair(root, other.root, 0, len,
                                          static_cast<unsigned int>(r), sum,
                                          other_sum, g, id(), id()));
  }

  static void reserve(std::size_t node_count) { pool.reserve(node_count); }

  static void clear() { std::vector<Node>().swap(pool); }

private:
  struct Node {
    int left = -1;
    int right = -1;
    S value{};
    F lazy{};
  };

  static inline std::vector<Node> pool;

  int n;
  unsigned int len;
  int root;

  struct empty_tag {};

  PersistentLazySegtree(int n_, empty_tag)
      : n(n_), len(std::bit_ceil(static_cast<unsigned int>(std::max(1, n_)))),
        root(-1) {
    assert(n >= 0);
  }

  static int alloc_leaf(const S &value) {
    pool.push_back(Node{-1, -1, value, id()});
    return static_cast<int>(pool.size()) - 1;
  }

  static int alloc_internal(int l, int r) {
    pool.push_back(Node{l, r, op(pool[l].value, pool[r].value), id()});
    return static_cast<int>(pool.size()) - 1;
  }

  static int apply_node(int t, const F &f) {
    const Node &p = pool[t];
    Node node{p.left, p.right, mapping(f, p.value),
              p.left == -1 ? p.lazy : composition(f, p.lazy)};
    pool.push_back(node);
    return static_cast<int>(pool.size()) - 1;
  }

  static bool is_id(const F &f) { return f == id(); }

  static F compose(const F &f, const F &g) {
    if (is_id(f))
      return g;
    if (is_id(g))
      return f;
    return composition(f, g);
  }

  static int push(int t, const F &f) {
    if (is_id(f))
      return t;
    return apply_node(t, f);
  }

  static S get(int t, unsigned int l, unsigned int r, unsigned int k,
               const F &f) {
    if (r - l == 1)
      return mapping(f, pool[t].value);

    unsigned int m = (l + r) / 2;
    F g = compose(f, pool[t].lazy);
    if (k < m)
      return get(pool[t].left, l, m, k, g);
    else
      return get(pool[t].right, m, r, k, g);
  }

  static int set(int t, unsigned int l, unsigned int r, unsigned int k,
                 const S &x, const F &f) {
    if (r - l == 1)
      return alloc_leaf(x);

    unsigned int m = (l + r) / 2;
    F g = compose(f, pool[t].lazy);
    int left = pool[t].left;
    int right = pool[t].right;
    if (k < m) {
      left = set(left, l, m, k, x, g);
      right = push(right, g);
    }
    else {
      left = push(left, g);
      right = set(right, m, r, k, x, g);
    }
    return alloc_internal(left, right);
  }

  static int apply(int t, unsigned int l, unsigned int r, unsigned int ql,
                   unsigned int qr, const F &x, const F &f) {
    if (r <= ql || qr <= l)
      return push(t, f);
    if (ql <= l && r <= qr)
      return apply_node(t, compose(x, f));

    unsigned int m = (l + r) / 2;
    F g = compose(f, pool[t].lazy);
    int left = apply(pool[t].left, l, m, ql, qr, x, g);
    int right = apply(pool[t].right, m, r, ql, qr, x, g);
    return alloc_internal(left, right);
  }

  static int assign(int dst, int src, unsigned int l, unsigned int r,
                    unsigned int ql, unsigned int qr, const F &fd,
                    const F &fs) {
    if (r <= ql || qr <= l)
      return push(dst, fd);
    if (ql <= l && r <= qr)
      return push(src, fs);

    unsigned int m = (l + r) / 2;
    F gd = compose(fd, pool[dst].lazy);
    F gs = compose(fs, pool[src].lazy);
    int left = assign(pool[dst].left, pool[src].left, l, m, ql, qr, gd, gs);
    int right =
        assign(pool[dst].right, pool[src].right, m, r, ql, qr, gd, gs);
    return alloc_internal(left, right);
  }

  static S prod(int t, unsigned int l, unsigned int r, unsigned int ql,
                unsigned int qr, const F &f) {
    if (r <= ql || qr <= l)
      return e();
    if (ql <= l && r <= qr)
      return mapping(f, pool[t].value);

    unsigned int m = (l + r) / 2;
    F g = compose(f, pool[t].lazy);
    return op(prod(pool[t].left, l, m, ql, qr, g),
              prod(pool[t].right, m, r, ql, qr, g));
  }

  template <class G>
  static unsigned int max_right(int t, unsigned int l, unsigned int r,
                                unsigned int ql, S &sum, G g, const F &f) {
    if (r <= ql)
      return r;
    if (ql <= l) {
      S value = mapping(f, pool[t].value);
      if (g(op(sum, value))) {
        sum = op(sum, value);
        return r;
      }
      if (r - l == 1)
        return l;
    }

    unsigned int m = (l + r) / 2;
    F h = compose(f, pool[t].lazy);
    unsigned int res = max_right(pool[t].left, l, m, ql, sum, g, h);
    if (res != m)
      return res;
    return max_right(pool[t].right, m, r, ql, sum, g, h);
  }

  template <class G>
  static unsigned int min_left(int t, unsigned int l, unsigned int r,
                               unsigned int qr, S &sum, G g, const F &f) {
    if (qr <= l)
      return l;
    if (r <= qr) {
      S value = mapping(f, pool[t].value);
      if (g(op(value, sum))) {
        sum = op(value, sum);
        return l;
      }
      if (r - l == 1)
        return r;
    }

    unsigned int m = (l + r) / 2;
    F h = compose(f, pool[t].lazy);
    unsigned int res = min_left(pool[t].right, m, r, qr, sum, g, h);
    if (res != m)
      return res;
    return min_left(pool[t].left, l, m, qr, sum, g, h);
  }

  template <class G>
  static unsigned int max_right_pair(int t, int u, unsigned int l, unsigned int r,
                                     unsigned int ql, S &sum, S &other_sum, G g,
                                     const F &f, const F &fu) {
    if (r <= ql)
      return r;
    if (ql <= l) {
      S x = op(sum, mapping(f, pool[t].value));
      S y = op(other_sum, mapping(fu, pool[u].value));
      if (g(x, y)) {
        sum = x;
        other_sum = y;
        return r;
      }
      if (r - l == 1)
        return l;
    }

    unsigned int m = (l + r) / 2;
    F h = compose(f, pool[t].lazy);
    F hu = compose(fu, pool[u].lazy);
    unsigned int res = max_right_pair(pool[t].left, pool[u].left, l, m, ql, sum,
                                      other_sum, g, h, hu);
    if (res != m)
      return res;
    return max_right_pair(pool[t].right, pool[u].right, m, r, ql, sum, other_sum,
                          g, h, hu);
  }

  template <class G>
  static unsigned int min_left_pair(int t, int u, unsigned int l, unsigned int r,
                                    unsigned int qr, S &sum, S &other_sum, G g,
                                    const F &f, const F &fu) {
    if (qr <= l)
      return l;
    if (r <= qr) {
      S x = op(mapping(f, pool[t].value), sum);
      S y = op(mapping(fu, pool[u].value), other_sum);
      if (g(x, y)) {
        sum = x;
        other_sum = y;
        return l;
      }
      if (r - l == 1)
        return r;
    }

    unsigned int m = (l + r) / 2;
    F h = compose(f, pool[t].lazy);
    F hu = compose(fu, pool[u].lazy);
    unsigned int res = min_left_pair(pool[t].right, pool[u].right, m, r, qr, sum,
                                     other_sum, g, h, hu);
    if (res != m)
      return res;
    return min_left_pair(pool[t].left, pool[u].left, l, m, qr, sum, other_sum, g,
                         h, hu);
  }
};

} // namespace ayuna
