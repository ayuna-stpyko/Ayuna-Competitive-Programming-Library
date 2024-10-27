#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <iostream>
#include "data_structure/unionfind.hpp"
using namespace std;

int main(){
  int n, q;
  cin >> n >> q;
  UnionFind uf(n);
  while(q--){
    int t, u, v;
    cin >> t >> u >> v;
    if (t){
      if (uf.same(u, v)) cout << 1 << endl;
      else cout << 0 << endl;
    }
    else uf.merge(u, v);
  }
}
