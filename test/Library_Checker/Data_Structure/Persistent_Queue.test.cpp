#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "persistent/persistentqueue.hpp"
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int q;
  cin >> q;
  vector<ayuna::PersistentQueue<ll>> history(q + 1);
  for (int i = 1; i <= q; i++) {
    int num, t;
    cin >> num >> t;
    if (num == 0) {
      ll x;
      cin >> x;
      history[i] = history[t + 1].push(x);
    }
    else {
      ll ans = history[t + 1].front();
      history[i] = history[t + 1].pop();
      cout << ans << '\n';
    }
  }
}
