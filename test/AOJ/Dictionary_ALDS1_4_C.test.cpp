#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_4_C"
#include "data_structure/trie.hpp"
#include <iostream>
using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int n;
  cin >> n;
  ayuna::Trie<26, 'A'> trie;
  while (n--) {
    string s, t;
    cin >> s >> t;
    if (s == "insert")
      trie.add(t);
    else {
      if (trie.exist(t))
        cout << "yes\n";
      else
        cout << "no\n";
    }
  }
}
