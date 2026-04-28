#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <iostream>
#include "math/modint_static.hpp"
#include "fps/common.hpp"

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  FormalPowerSeries<modint1000000007> a(n), b(m);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    a[i] = k;
  }
  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;
    b[i] = k;
  }
  a *= b;
  for (int i = 0; i < n + m - 1; i++) {
    if (i) cout << " ";
    cout << a[i].val();
  }
  cout << endl;
}
