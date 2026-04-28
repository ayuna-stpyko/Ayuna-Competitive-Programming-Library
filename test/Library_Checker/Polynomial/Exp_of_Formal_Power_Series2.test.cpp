#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <iostream>
#include "fps/common_ntt.hpp"
#include "math/modint_static.hpp"

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n;
  cin >> n;
  NTTFriendlyFormalPowerSeries<modint998244353> f(n);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    f[i] = a;
  }
  auto g = f.exp();
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << g[i].val();
  }
  cout << endl;
}
