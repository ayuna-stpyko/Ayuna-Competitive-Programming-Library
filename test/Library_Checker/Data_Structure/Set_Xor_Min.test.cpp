#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include <iostream>
#include "data_structure/binarytrie.hpp"
using namespace std;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  ayuna::BinaryTrie trie;
  int q;
  cin >> q;
  while (q--) {
    int num, x;
    cin >> num >> x;
    if (num == 0) {
      if (trie.count(x) == 0) trie.insert(x);
    }
    else if (num == 1) {
      if (trie.count(x) > 0) trie.erase(x);
    }
    else {
      cout << trie.kth_element_xor(0, x) << endl;
    }
  }
}
