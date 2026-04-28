#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include <iostream>
#include "tree/lowestcommonancestor.hpp"
using namespace std;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> graph(n);
  for (int i = 0; i < n - 1; i++){
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  LowestCommonAncestor lca(graph);

  while(q--){
    int s, t, i;
    cin >> s >> t >> i;
    cout << lca.jumpto(s, t, i) << endl;
  }
}
