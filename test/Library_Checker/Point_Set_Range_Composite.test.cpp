#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <iostream>
#include "data_structure/segmenttree.hpp"
using namespace std;
using ll = long long;

constexpr ll m93 = 998244353ll;
pair<ll, ll> op(pair<ll, ll> a, pair<ll, ll> b) { return make_pair(a.first * b.first % m93, (a.second * b.first % m93 + b.second) % m93);}
pair<ll, ll> e() { return make_pair(1ll, 0ll);}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  SegmentTree<pair<ll, ll>, op, e> st(n);
  for (int i = 0; i < n; i++) {
    int c, d;
    cin >> c >> d;
    st.set(i, make_pair(c, d));
  }
  while (q--) {
    int num;
    cin >> num;
    switch (num) {
      case 0:{
        int p;
        ll c, d;
        cin >> p >> c >> d;
        st.set(p, make_pair(c, d));
        break;
      }
      case 1:{
        int l, r;
        ll x;
        cin >> l >> r >> x;
        auto [c, d] = st.prod(l, r);
        cout << (c * x % m93 + d) % m93 << endl;
        break;
      }
    }
  }
}