#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <iostream>
#include <map>
#include "persistent/persistentsegtree.hpp"
using namespace std;
using ll = long long;

int op(int a, int b) { return a + b; }
int e() { return 0; }

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ll> a(n);
  for (ll &i : a) cin >> i;
  map<ll, vector<int>> mp;
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    mp[a[i]].push_back(i);
  }
  int idx = 0;
  vector<ll> vals;
  for (auto &[k, v] : mp) {
    for (ll i : v) b[i] = idx;
    vals.push_back(k);
    idx++;
  }
  vector<ayuna::PersistentSegtree<int, op, e>> history(n + 1);
  history[0] = ayuna::PersistentSegtree<int, op, e>(idx);
  for (int i = 0; i < n; i++) {
    history[i + 1] = history[i].set(b[i], history[i].get(b[i]) + 1);
  }
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    int idx_k = history[r].max_right_pair(0, history[l], [&](int x, int y) { return x - y <= k; });
    cout << vals[idx_k] << '\n';
  }
}
