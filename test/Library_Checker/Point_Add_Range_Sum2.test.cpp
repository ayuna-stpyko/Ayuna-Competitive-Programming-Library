#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>
#include <vector>
#include "data_structure/dynamicsegtree.hpp"
using namespace std;
using ll = long long;

ll op(ll a, ll b) { return a + b;}
ll e() { return 0;}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll &i: a) cin >> i;
  DynamicSegmentTree<ll, op, e> st(n);
  for (int i = 0; i < n; i++) st.set(i, a[i]);
  while (q--) {
    int num;
    cin >> num;
    switch (num) {
    case 0:
      int p;
      ll x;
      cin >> p >> x;
      st.set(p, st.get(p) + x);
      break;
    
    case 1:
      int l, r;
      cin >> l >> r;
      cout << st.prod(l, r) << endl;
      break;
    }
  }
}