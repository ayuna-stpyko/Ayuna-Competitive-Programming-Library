#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "tree/lowestcommonancestor.hpp"
#include <iostream>
using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> graph(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    graph[i].push_back(p);
    graph[p].push_back(i);
  }
  ayuna::LowestCommonAncestor tree(graph);
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << tree.lca(u, v) << endl;
  }
}
