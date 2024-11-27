#include <cassert>
#include <vector>
#include <functional>

template <class S, auto op, auto e> struct SegmentTree {
  SegmentTree(int n) : SegmentTree(std::vector<S>(n, e())) {}
  SegmentTree(const std::vector<S> &v) : _n(v.size()) {
    size = bit_ceil((unsigned int)_n);
    log = __builtin_ctz((unsigned int)size);
    d.resize(size << 1, e());
    for (int i = 0; i < _n; i++) d[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) update(i);
  }

  void set(int p, S x){
    assert(0 <= p && p < _n);
    p += size;
    d[p] = x;
    for (int i = 1; i <= log; i++) update(p >> i);
  }

  S get(const int p) const{
    assert(0 <= p && p < _n);
    return d[p + size];
  }

  S prod(int l, int r) const{
    assert(0 <= l && l <= r && r <= _n);
    S sml = e(), smr = e();
    l += size;
    r += size;
    while (l < r) {
      if (l & 1) sml = op(sml, d[l++]);
      if (r & 1) smr = op(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return op(sml, smr);
  }

  S all_prod() const{
    return d[1];
  }

private:
  int _n, size, log;
  std::vector<S> d;
  void update(int i) { d[i] = op(d[i << 1], d[i << 1 | 1]); }

  unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x <<= 1;
    return x;
  }
};