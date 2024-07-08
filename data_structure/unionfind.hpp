#include <algorithm>
#include <cassert>
#include <vector>

struct UnionFind {
public:
  UnionFind(int N) : _n(N) { parent_or_size.resize(_n, -1); }

  int merge(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    if(same(a, b))
      return leader(a);
    if(size(a) < size(b))
      std::swap(a, b);
    int x = leader(a), y = leader(b);
    parent_or_size[x] += parent_or_size[y];
    parent_or_size[y] = x;
    return a;
  }

  bool same(const int a, const int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    return leader(a) == leader(b);
  }

  int leader(const int a) {
    assert(0 <= a && a < _n);
    if(parent_or_size[a] < 0)
      return a;
    parent_or_size[a] = leader(parent_or_size[a]);
    return parent_or_size[a];
  }

  int size(const int a) {
    assert(0 <= a && a < _n);
    return -parent_or_size[leader(a)];
  }

  std::vector<std::vector<int>> groups() {
    std::vector<std::vector<int>> ret(_n);
    for(int i = 0; i < _n; i++) {
      if(parent_or_size[i] < 0) {
        ret[i].reserve(-parent_or_size[i]);
      }
    }
    for(int i = 0; i < _n; i++) {
      ret[leader(i)].push_back(i);
    }
    ret.erase(std::remove_if(ret.begin(), ret.end(), [](const std::vector<int> &a) { return a.empty(); }), ret.end());
    return ret;
  }

private:
  const int _n;
  std::vector<int> parent_or_size;
};
