---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/modint_static.hpp
    title: math/modint_static.hpp
  - icon: ':heavy_check_mark:'
    path: persistent/persistentlazysegtree.hpp
    title: persistent/persistentlazysegtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/persistent_range_affine_range_sum
  bundledCode: "#line 1 \"test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n\n#line 2 \"math/modint_static.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <numeric>\n#include <type_traits>\n#include <utility>\n\nnamespace ayuna\
    \ {\n\nusing ll = long long;\nusing ull = unsigned long long;\nusing u32 = unsigned\
    \ int;\n\ntemplate <int m>\nstruct modint {\n  using mint = modint;\n\nprivate:\n\
    \  u32 _v;\n\npublic:\n  constexpr modint() : _v(0) {}\n  template <class T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  constexpr modint(T v) {\n    ll x = (ll)(v % (ll)(m));\n    if\
    \ (x < 0)\n      x += m;\n    _v = (u32)(x);\n  }\n\n  u32 val() const { return\
    \ _v; }\n\n  static constexpr u32 mod() { return m; }\n\n  mint &operator++()\
    \ {\n    _v++;\n    if (_v == m)\n      _v = 0;\n    return *this;\n  }\n  mint\
    \ &operator--() {\n    if (_v == 0)\n      _v = m;\n    _v--;\n    return *this;\n\
    \  }\n  mint operator++(int) {\n    mint result = *this;\n    ++*this;\n    return\
    \ result;\n  }\n  mint operator--(int) {\n    mint result = *this;\n    --*this;\n\
    \    return result;\n  }\n\n  mint &operator+=(const mint &r) {\n    _v += r._v;\n\
    \    if (_v >= m)\n      _v -= m;\n    return *this;\n  }\n  mint &operator-=(const\
    \ mint &r) {\n    _v -= r._v;\n    if (_v >= m)\n      _v += m;\n    return *this;\n\
    \  }\n  mint &operator*=(const mint &r) {\n    ull z = _v;\n    z *= r._v;\n \
    \   _v = (u32)(z % m);\n    return *this;\n  }\n  mint &operator/=(const mint\
    \ &r) { return *this = *this * r.inv(); }\n\n  mint operator+() const { return\
    \ *this; }\n  mint operator-() const { return mint() - *this; }\n\n  mint pow(ll\
    \ n) const {\n    assert(0 <= n);\n    mint x = *this, r = 1;\n    while (n) {\n\
    \      if (n & 1)\n        r *= x;\n      x *= x;\n      n >>= 1;\n    }\n   \
    \ return r;\n  }\n  mint inv() const {\n    assert(_v);\n    return pow(m - 2);\n\
    \  }\n\n  friend mint operator+(const mint &l, const mint &r) { return mint(l)\
    \ += r; }\n  friend mint operator-(const mint &l, const mint &r) { return mint(l)\
    \ -= r; }\n  friend mint operator*(const mint &l, const mint &r) { return mint(l)\
    \ *= r; }\n  friend mint operator/(const mint &l, const mint &r) { return mint(l)\
    \ /= r; }\n  friend bool operator==(const mint &l, const mint &r) { return l._v\
    \ == r._v; }\n  friend bool operator!=(const mint &l, const mint &r) { return\
    \ l._v != r._v; }\n  friend std::ostream &operator<<(std::ostream &os, const mint\
    \ &a) {\n    return os << a.val();\n  }\n};\n\nusing modint998244353 = modint<998244353>;\n\
    using modint1000000007 = modint<1000000007>;\n\n} // namespace ayuna\n#line 2\
    \ \"persistent/persistentlazysegtree.hpp\"\n\n#include <algorithm>\n#include <bit>\n\
    #line 6 \"persistent/persistentlazysegtree.hpp\"\n#include <concepts>\n#include\
    \ <cstddef>\n#include <vector>\n\nnamespace ayuna {\n\ntemplate <class S, auto\
    \ op, auto e, class F, auto mapping, auto composition,\n          auto id>\n \
    \ requires requires(S a, S b, F f, F g) {\n    { op(a, b) } -> std::same_as<S>;\n\
    \    { e() } -> std::same_as<S>;\n    { mapping(f, a) } -> std::same_as<S>;\n\
    \    { composition(f, g) } -> std::same_as<F>;\n    { id() } -> std::same_as<F>;\n\
    \  }\nclass PersistentLazySegtree {\n  static_assert(std::equality_comparable<F>,\n\
    \                \"F needs operator== (e.g. bool operator==(const F &) const =\
    \ default;)\");\n\npublic:\n  PersistentLazySegtree() : PersistentLazySegtree(0,\
    \ empty_tag{}) {}\n\n  explicit PersistentLazySegtree(int n_) : PersistentLazySegtree(n_,\
    \ empty_tag{}) {\n    if (n == 0)\n      return;\n    root = alloc_leaf(e());\n\
    \    for (unsigned int w = 1; w < len; w *= 2)\n      root = alloc_internal(root,\
    \ root);\n  }\n\n  explicit PersistentLazySegtree(const std::vector<S> &v)\n \
    \     : PersistentLazySegtree(static_cast<int>(v.size()), empty_tag{}) {\n   \
    \ if (n == 0)\n      return;\n    std::vector<int> cur(len);\n    int pad = n\
    \ < static_cast<int>(len) ? alloc_leaf(e()) : -1;\n    for (int i = 0; i < static_cast<int>(len);\
    \ i++)\n      cur[i] = i < n ? alloc_leaf(v[i]) : pad;\n    while (cur.size()\
    \ > 1) {\n      for (std::size_t i = 0; i < cur.size() / 2; i++)\n        cur[i]\
    \ = alloc_internal(cur[2 * i], cur[2 * i + 1]);\n      cur.resize(cur.size() /\
    \ 2);\n    }\n    root = cur[0];\n  }\n\n  int size() const { return n; }\n\n\
    \  S get(int k) const {\n    assert(0 <= k && k < n);\n    return get(root, 0,\
    \ len, static_cast<unsigned int>(k), id());\n  }\n\n  PersistentLazySegtree set(int\
    \ k, const S &x) const {\n    assert(0 <= k && k < n);\n    PersistentLazySegtree\
    \ res(n, empty_tag{});\n    res.root = set(root, 0, len, static_cast<unsigned\
    \ int>(k), x, id());\n    return res;\n  }\n\n  PersistentLazySegtree apply(int\
    \ l, int r, const F &f) const {\n    assert(0 <= l && l <= r && r <= n);\n   \
    \ if (l == r)\n      return *this;\n    PersistentLazySegtree res(n, empty_tag{});\n\
    \    res.root = apply(root, 0, len, static_cast<unsigned int>(l),\n          \
    \           static_cast<unsigned int>(r), f, id());\n    return res;\n  }\n\n\
    \  PersistentLazySegtree assign(const PersistentLazySegtree &src, int l,\n   \
    \                            int r) const {\n    assert(n == src.n);\n    assert(0\
    \ <= l && l <= r && r <= n);\n    if (l == r)\n      return *this;\n    if (l\
    \ == 0 && r == n)\n      return src;\n    PersistentLazySegtree res(n, empty_tag{});\n\
    \    res.root = assign(root, src.root, 0, len, static_cast<unsigned int>(l),\n\
    \                      static_cast<unsigned int>(r), id(), id());\n    return\
    \ res;\n  }\n\n  S prod(int l, int r) const {\n    assert(0 <= l && l <= r &&\
    \ r <= n);\n    if (l == r)\n      return e();\n    return prod(root, 0, len,\
    \ static_cast<unsigned int>(l),\n                static_cast<unsigned int>(r),\
    \ id());\n  }\n\n  S all_prod() const { return root == -1 ? e() : pool[root].value;\
    \ }\n\n  template <bool (*f)(S)>\n  int max_right(int l) const {\n    return max_right(l,\
    \ [](S x) { return f(x); });\n  }\n\n  template <class G>\n  int max_right(int\
    \ l, G g) const {\n    assert(0 <= l && l <= n);\n    assert(g(e()));\n    if\
    \ (l == n)\n      return n;\n    S sum = e();\n    return std::min(n, static_cast<int>(max_right(root,\
    \ 0, len,\n                                                  static_cast<unsigned\
    \ int>(l),\n                                                  sum, g, id())));\n\
    \  }\n\n  template <bool (*f)(S)>\n  int min_left(int r) const {\n    return min_left(r,\
    \ [](S x) { return f(x); });\n  }\n\n  template <class G>\n  int min_left(int\
    \ r, G g) const {\n    assert(0 <= r && r <= n);\n    assert(g(e()));\n    if\
    \ (r == 0)\n      return 0;\n    S sum = e();\n    return static_cast<int>(\n\
    \        min_left(root, 0, len, static_cast<unsigned int>(r), sum, g, id()));\n\
    \  }\n\n  template <class G>\n  int max_right_pair(int l, const PersistentLazySegtree\
    \ &other, G g) const {\n    assert(n == other.n);\n    assert(0 <= l && l <= n);\n\
    \    assert(g(e(), e()));\n    if (l == n)\n      return n;\n    S sum = e(),\
    \ other_sum = e();\n    return std::min(n, static_cast<int>(max_right_pair(\n\
    \                           root, other.root, 0, len, static_cast<unsigned int>(l),\n\
    \                           sum, other_sum, g, id(), id())));\n  }\n\n  template\
    \ <class G>\n  int min_left_pair(int r, const PersistentLazySegtree &other, G\
    \ g) const {\n    assert(n == other.n);\n    assert(0 <= r && r <= n);\n    assert(g(e(),\
    \ e()));\n    if (r == 0)\n      return 0;\n    S sum = e(), other_sum = e();\n\
    \    return static_cast<int>(min_left_pair(root, other.root, 0, len,\n       \
    \                                   static_cast<unsigned int>(r), sum,\n     \
    \                                     other_sum, g, id(), id()));\n  }\n\n  static\
    \ void reserve(std::size_t node_count) { pool.reserve(node_count); }\n\n  static\
    \ void clear() { std::vector<Node>().swap(pool); }\n\nprivate:\n  struct Node\
    \ {\n    int left = -1;\n    int right = -1;\n    S value{};\n    F lazy{};\n\
    \  };\n\n  static inline std::vector<Node> pool;\n\n  int n;\n  unsigned int len;\n\
    \  int root;\n\n  struct empty_tag {};\n\n  PersistentLazySegtree(int n_, empty_tag)\n\
    \      : n(n_), len(std::bit_ceil(static_cast<unsigned int>(std::max(1, n_)))),\n\
    \        root(-1) {\n    assert(n >= 0);\n  }\n\n  static int alloc_leaf(const\
    \ S &value) {\n    pool.push_back(Node{-1, -1, value, id()});\n    return static_cast<int>(pool.size())\
    \ - 1;\n  }\n\n  static int alloc_internal(int l, int r) {\n    pool.push_back(Node{l,\
    \ r, op(pool[l].value, pool[r].value), id()});\n    return static_cast<int>(pool.size())\
    \ - 1;\n  }\n\n  static int apply_node(int t, const F &f) {\n    const Node &p\
    \ = pool[t];\n    Node node{p.left, p.right, mapping(f, p.value),\n          \
    \    p.left == -1 ? p.lazy : composition(f, p.lazy)};\n    pool.push_back(node);\n\
    \    return static_cast<int>(pool.size()) - 1;\n  }\n\n  static bool is_id(const\
    \ F &f) { return f == id(); }\n\n  static F compose(const F &f, const F &g) {\n\
    \    if (is_id(f))\n      return g;\n    if (is_id(g))\n      return f;\n    return\
    \ composition(f, g);\n  }\n\n  static int push(int t, const F &f) {\n    if (is_id(f))\n\
    \      return t;\n    return apply_node(t, f);\n  }\n\n  static S get(int t, unsigned\
    \ int l, unsigned int r, unsigned int k,\n               const F &f) {\n    if\
    \ (r - l == 1)\n      return mapping(f, pool[t].value);\n\n    unsigned int m\
    \ = (l + r) / 2;\n    F g = compose(f, pool[t].lazy);\n    if (k < m)\n      return\
    \ get(pool[t].left, l, m, k, g);\n    else\n      return get(pool[t].right, m,\
    \ r, k, g);\n  }\n\n  static int set(int t, unsigned int l, unsigned int r, unsigned\
    \ int k,\n                 const S &x, const F &f) {\n    if (r - l == 1)\n  \
    \    return alloc_leaf(x);\n\n    unsigned int m = (l + r) / 2;\n    F g = compose(f,\
    \ pool[t].lazy);\n    int left = pool[t].left;\n    int right = pool[t].right;\n\
    \    if (k < m) {\n      left = set(left, l, m, k, x, g);\n      right = push(right,\
    \ g);\n    }\n    else {\n      left = push(left, g);\n      right = set(right,\
    \ m, r, k, x, g);\n    }\n    return alloc_internal(left, right);\n  }\n\n  static\
    \ int apply(int t, unsigned int l, unsigned int r, unsigned int ql,\n        \
    \           unsigned int qr, const F &x, const F &f) {\n    if (r <= ql || qr\
    \ <= l)\n      return push(t, f);\n    if (ql <= l && r <= qr)\n      return apply_node(t,\
    \ compose(x, f));\n\n    unsigned int m = (l + r) / 2;\n    F g = compose(f, pool[t].lazy);\n\
    \    int left = apply(pool[t].left, l, m, ql, qr, x, g);\n    int right = apply(pool[t].right,\
    \ m, r, ql, qr, x, g);\n    return alloc_internal(left, right);\n  }\n\n  static\
    \ int assign(int dst, int src, unsigned int l, unsigned int r,\n             \
    \       unsigned int ql, unsigned int qr, const F &fd,\n                    const\
    \ F &fs) {\n    if (r <= ql || qr <= l)\n      return push(dst, fd);\n    if (ql\
    \ <= l && r <= qr)\n      return push(src, fs);\n\n    unsigned int m = (l + r)\
    \ / 2;\n    F gd = compose(fd, pool[dst].lazy);\n    F gs = compose(fs, pool[src].lazy);\n\
    \    int left = assign(pool[dst].left, pool[src].left, l, m, ql, qr, gd, gs);\n\
    \    int right =\n        assign(pool[dst].right, pool[src].right, m, r, ql, qr,\
    \ gd, gs);\n    return alloc_internal(left, right);\n  }\n\n  static S prod(int\
    \ t, unsigned int l, unsigned int r, unsigned int ql,\n                unsigned\
    \ int qr, const F &f) {\n    if (r <= ql || qr <= l)\n      return e();\n    if\
    \ (ql <= l && r <= qr)\n      return mapping(f, pool[t].value);\n\n    unsigned\
    \ int m = (l + r) / 2;\n    F g = compose(f, pool[t].lazy);\n    return op(prod(pool[t].left,\
    \ l, m, ql, qr, g),\n              prod(pool[t].right, m, r, ql, qr, g));\n  }\n\
    \n  template <class G>\n  static unsigned int max_right(int t, unsigned int l,\
    \ unsigned int r,\n                                unsigned int ql, S &sum, G\
    \ g, const F &f) {\n    if (r <= ql)\n      return r;\n    if (ql <= l) {\n  \
    \    S value = mapping(f, pool[t].value);\n      if (g(op(sum, value))) {\n  \
    \      sum = op(sum, value);\n        return r;\n      }\n      if (r - l == 1)\n\
    \        return l;\n    }\n\n    unsigned int m = (l + r) / 2;\n    F h = compose(f,\
    \ pool[t].lazy);\n    unsigned int res = max_right(pool[t].left, l, m, ql, sum,\
    \ g, h);\n    if (res != m)\n      return res;\n    return max_right(pool[t].right,\
    \ m, r, ql, sum, g, h);\n  }\n\n  template <class G>\n  static unsigned int min_left(int\
    \ t, unsigned int l, unsigned int r,\n                               unsigned\
    \ int qr, S &sum, G g, const F &f) {\n    if (qr <= l)\n      return l;\n    if\
    \ (r <= qr) {\n      S value = mapping(f, pool[t].value);\n      if (g(op(value,\
    \ sum))) {\n        sum = op(value, sum);\n        return l;\n      }\n      if\
    \ (r - l == 1)\n        return r;\n    }\n\n    unsigned int m = (l + r) / 2;\n\
    \    F h = compose(f, pool[t].lazy);\n    unsigned int res = min_left(pool[t].right,\
    \ m, r, qr, sum, g, h);\n    if (res != m)\n      return res;\n    return min_left(pool[t].left,\
    \ l, m, qr, sum, g, h);\n  }\n\n  template <class G>\n  static unsigned int max_right_pair(int\
    \ t, int u, unsigned int l, unsigned int r,\n                                \
    \     unsigned int ql, S &sum, S &other_sum, G g,\n                          \
    \           const F &f, const F &fu) {\n    if (r <= ql)\n      return r;\n  \
    \  if (ql <= l) {\n      S x = op(sum, mapping(f, pool[t].value));\n      S y\
    \ = op(other_sum, mapping(fu, pool[u].value));\n      if (g(x, y)) {\n       \
    \ sum = x;\n        other_sum = y;\n        return r;\n      }\n      if (r -\
    \ l == 1)\n        return l;\n    }\n\n    unsigned int m = (l + r) / 2;\n   \
    \ F h = compose(f, pool[t].lazy);\n    F hu = compose(fu, pool[u].lazy);\n   \
    \ unsigned int res = max_right_pair(pool[t].left, pool[u].left, l, m, ql, sum,\n\
    \                                      other_sum, g, h, hu);\n    if (res != m)\n\
    \      return res;\n    return max_right_pair(pool[t].right, pool[u].right, m,\
    \ r, ql, sum, other_sum,\n                          g, h, hu);\n  }\n\n  template\
    \ <class G>\n  static unsigned int min_left_pair(int t, int u, unsigned int l,\
    \ unsigned int r,\n                                    unsigned int qr, S &sum,\
    \ S &other_sum, G g,\n                                    const F &f, const F\
    \ &fu) {\n    if (qr <= l)\n      return l;\n    if (r <= qr) {\n      S x = op(mapping(f,\
    \ pool[t].value), sum);\n      S y = op(mapping(fu, pool[u].value), other_sum);\n\
    \      if (g(x, y)) {\n        sum = x;\n        other_sum = y;\n        return\
    \ l;\n      }\n      if (r - l == 1)\n        return r;\n    }\n\n    unsigned\
    \ int m = (l + r) / 2;\n    F h = compose(f, pool[t].lazy);\n    F hu = compose(fu,\
    \ pool[u].lazy);\n    unsigned int res = min_left_pair(pool[t].right, pool[u].right,\
    \ m, r, qr, sum,\n                                     other_sum, g, h, hu);\n\
    \    if (res != m)\n      return res;\n    return min_left_pair(pool[t].left,\
    \ pool[u].left, l, m, qr, sum, other_sum, g,\n                         h, hu);\n\
    \  }\n};\n\n} // namespace ayuna\n#line 6 \"test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp\"\
    \nusing namespace std;\nusing mint = ayuna::modint998244353;\n\nstruct S {\n \
    \ mint val;\n  mint len;\n};\n\nS op(S a, S b) {\n  a.val += b.val;\n  a.len +=\
    \ b.len;\n  return a;\n}\nS e() {\n  return S(0, 0);\n}\nusing F = pair<mint,\
    \ mint>;\nS mapping(F f, S x) {\n  x.val = f.first * x.val + f.second * x.len;\n\
    \  return x;\n}\nF composition(F f, F g) {\n  return make_pair(f.first * g.first,\
    \ f.first * g.second + f.second);\n}\nF id() {\n  return make_pair(1, 0);\n}\n\
    \nusing ST = ayuna::PersistentLazySegtree<S, op, e, F, mapping, composition, id>;\n\
    \nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n  int n, q;\n  cin\
    \ >> n >> q;\n  vector<S> a(n);\n  for (S &i : a) {\n    int b;\n    cin >> b;\n\
    \    i.val = b;\n    i.len = 1;\n  }\n\n  vector<ST> history(q + 1);\n  history[0]\
    \ = ST(a);\n  for (int i = 1; i <= q; i++) {\n    int num, k;\n    cin >> num\
    \ >> k;\n    if (num == 0) {\n      int l, r, b, c;\n      cin >> l >> r >> b\
    \ >> c;\n      history[i] = history[k + 1].apply(l, r, make_pair(b, c));\n   \
    \ }\n    else if (num == 1) {\n      int s, l, r;\n      cin >> s >> l >> r;\n\
    \      history[i] = history[k + 1].assign(history[s + 1], l, r);\n    }\n    else\
    \ {\n      int l, r;\n      cin >> l >> r;\n      cout << history[k + 1].prod(l,\
    \ r).val.val() << '\\n';\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_range_affine_range_sum\"\
    \n\n#include \"math/modint_static.hpp\"\n#include \"persistent/persistentlazysegtree.hpp\"\
    \n#include <iostream>\nusing namespace std;\nusing mint = ayuna::modint998244353;\n\
    \nstruct S {\n  mint val;\n  mint len;\n};\n\nS op(S a, S b) {\n  a.val += b.val;\n\
    \  a.len += b.len;\n  return a;\n}\nS e() {\n  return S(0, 0);\n}\nusing F = pair<mint,\
    \ mint>;\nS mapping(F f, S x) {\n  x.val = f.first * x.val + f.second * x.len;\n\
    \  return x;\n}\nF composition(F f, F g) {\n  return make_pair(f.first * g.first,\
    \ f.first * g.second + f.second);\n}\nF id() {\n  return make_pair(1, 0);\n}\n\
    \nusing ST = ayuna::PersistentLazySegtree<S, op, e, F, mapping, composition, id>;\n\
    \nint main() {\n  cin.tie(0);\n  ios::sync_with_stdio(0);\n  int n, q;\n  cin\
    \ >> n >> q;\n  vector<S> a(n);\n  for (S &i : a) {\n    int b;\n    cin >> b;\n\
    \    i.val = b;\n    i.len = 1;\n  }\n\n  vector<ST> history(q + 1);\n  history[0]\
    \ = ST(a);\n  for (int i = 1; i <= q; i++) {\n    int num, k;\n    cin >> num\
    \ >> k;\n    if (num == 0) {\n      int l, r, b, c;\n      cin >> l >> r >> b\
    \ >> c;\n      history[i] = history[k + 1].apply(l, r, make_pair(b, c));\n   \
    \ }\n    else if (num == 1) {\n      int s, l, r;\n      cin >> s >> l >> r;\n\
    \      history[i] = history[k + 1].assign(history[s + 1], l, r);\n    }\n    else\
    \ {\n      int l, r;\n      cin >> l >> r;\n      cout << history[k + 1].prod(l,\
    \ r).val.val() << '\\n';\n    }\n  }\n}\n"
  dependsOn:
  - math/modint_static.hpp
  - persistent/persistentlazysegtree.hpp
  isVerificationFile: true
  path: test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp
  requiredBy: []
  timestamp: '2026-10-17 00:37:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp
layout: document
redirect_from:
- /verify/test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp
- /verify/test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp.html
title: test/Library_Checker/Data_Structure/Persistent_Range_Affine_Range_Sum.test.cpp
---
