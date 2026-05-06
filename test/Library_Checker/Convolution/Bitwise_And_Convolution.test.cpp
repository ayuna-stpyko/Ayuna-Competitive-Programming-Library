#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include <iostream>
#include "math/convolution.hpp"
#include "math/modint_static.hpp"

using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n;
  cin >> n;
  vector<ayuna::modint998244353> a(1 << n), b(1 << n);
  for (int i = 0; i < (1 << n); i++) {
    int k;
    cin >> k;
    a[i] = k;
  }
  for (int i = 0; i < (1 << n); i++) {
    int k;
    cin >> k;
    b[i] = k;
  }
  auto c = ayuna::and_convolution(a, b);
  for (int i = 0; i < (int)c.size(); i++) cout << c[i] << " ";
  cout << endl;
  return 0;
}
