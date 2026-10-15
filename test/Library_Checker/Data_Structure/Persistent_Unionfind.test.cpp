#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <iostream>
#include <vector>
#include "persistent/persistentunionfind.hpp"
using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ayuna::PersistentUnionFind> history(q + 1);
  history[0] = ayuna::PersistentUnionFind(n);
  for (int i = 1; i <= q; i++) {
    int t, k, u, v;
    cin >> t >> k >> u >> v;
    if (t == 0) {
      history[i] = history[k + 1].merge(u, v);
    }
    else {
      cout << (history[k + 1].same(u, v) ? "1\n" : "0\n");
    }
  }
}
