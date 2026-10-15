#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"

#include <iostream>
#include "math/modint_static.hpp"
#include "persistent/persistentlazysegtree.hpp"
using namespace std;
using mint = ayuna::modint998244353;

struct S {
  mint val;
  mint len;
};

S op(S a, S b) {
  a.val += b.val;
  a.len += b.len;
  return a;
}
S e() {
  return S(0, 0);
}
using F = pair<mint, mint>;
S mapping(F f, S x) {
  x.val = f.first * x.val + f.second * x.len;
  return x;
}
F composition(F f, F g) {
  return make_pair(f.first * g.first, f.first * g.second + f.second);
}
F id() {
  return make_pair(1, 0);
}

using ST = ayuna::PersistentLazySegtree<S, op, e, F, mapping, composition, id>;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<S> a(n);
  for (S &i : a) {
    int b;
    cin >> b;
    i.val = b;
    i.len = 1;
  }

  vector<ST> history(q + 1);
  history[0] = ST(a);
  for (int i = 1; i <= q; i++) {
    int num, k;
    cin >> num >> k;
    if (num == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      history[i] = history[k + 1].apply(l, r, make_pair(b, c));
    }
    else if (num == 1) {
      int s, l, r;
      cin >> s >> l >> r;
      history[i] = history[k + 1].assign(history[s + 1], l, r);
    }
    else {
      int l, r;
      cin >> l >> r;
      cout << history[k + 1].prod(l, r).val.val() << '\n';
    }
  }
}
