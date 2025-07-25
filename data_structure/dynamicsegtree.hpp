#include <cassert>
#include <memory>

template <class S, S (*op)(S, S), S (*e)()>
class DynamicSegmentTree {
public:
  DynamicSegmentTree(long long _n) : n(_n), root(nullptr) {}

  void set(long long p, S x) {
    assert(p < n);
    set(root, 0, n, p, x);
  }
  S get(long long p) const {
    assert(p < n);
    return get(root, 0, n, p);
  }
  S prod(long long l, long long r) const {
    assert(l <= r && r <= n);
    return prod(root, 0, n, l, r);
  }

  S all_prod() const { return root ? root->value : e(); }

  void reset(long long l, long long r) {
    assert(l <= r && r <= n);
    reset(root, 0, n, l, r);
  }

private:
  struct node;
  using node_ptr = std::unique_ptr<node>;

  struct node {
    S value;
    node_ptr left, right;
    node() : value(e()), left(nullptr), right(nullptr) {}
    node(S v) : value(v), left(nullptr), right(nullptr) {}
  };

  long long n;
  node_ptr root;

  void set(node_ptr &t, long long l, long long r, long long p, S x) {
    if(!t)
      t = std::make_unique<node>();
    if(r - l == 1) {
      t->value = x;
      return;
    }
    long long m = (l + r) >> 1;
    if(p < m)
      set(t->left, l, m, p, x);
    else
      set(t->right, m, r, p, x);
    t->value =
        op(t->left ? t->left->value : e(), t->right ? t->right->value : e());
  }

  S get(const node_ptr &t, long long l, long long r, long long p) const {
    if(!t)
      return e();
    if(r - l == 1)
      return t->value;
    long long m = (l + r) >> 1;
    if(p < m)
      return get(t->left, l, m, p);
    else
      return get(t->right, m, r, p);
  }

  S prod(const node_ptr &t, long long l, long long r, long long ql,
         long long qr) const {
    if(!t || r <= ql || qr <= l)
      return e();
    if(ql <= l && r <= qr)
      return t->value;
    long long m = (l + r) >> 1;
    return op(prod(t->left, l, m, ql, qr), prod(t->right, m, r, ql, qr));
  }

  void reset(node_ptr &t, long long l, long long r, long long ql,
             long long qr) {
    if(!t || r <= ql || qr <= l)
      return;
    if(ql <= l && r <= qr) {
      t.reset();
      return;
    }
    long long m = (l + r) >> 1;
    reset(t->left, l, m, ql, qr);
    reset(t->right, m, r, ql, qr);
    t->value =
        op(t->left ? t->left->value : e(), t->right ? t->right->value : e());
  }
};