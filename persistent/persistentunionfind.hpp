#pragma once

#include <cassert>
#include <utility>

#include "persistentarray.hpp"

namespace ayuna {

class PersistentUnionFind {
public:
  PersistentUnionFind() = default;

  explicit PersistentUnionFind(int n) : data(n, -1) {}

  int leader(int a) const { return find(a).first; }

  bool same(int a, int b) const {
    assert(0 <= b && b < data.size());
    return leader(a) == leader(b);
  }

  int size(int a) const { return find(a).second; }

  PersistentUnionFind merge(int a, int b) const {
    assert(0 <= b && b < data.size());
    auto [x, sx] = find(a);
    auto [y, sy] = find(b);
    if (x == y)
      return *this;

    if (sx < sy)
      std::swap(x, y);

    PersistentUnionFind res;
    res.data = data.set(x, -(sx + sy)).set(y, x);
    return res;
  }

private:
  PersistentArray<int> data;

  std::pair<int, int> find(int a) const {
    assert(0 <= a && a < data.size());
    int p;
    while ((p = data.get(a)) >= 0)
      a = p;
    return {a, -p};
  }
};

} // namespace ayuna
