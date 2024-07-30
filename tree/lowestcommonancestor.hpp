#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <cassert>

struct LowestCommonAncestor {
public:
  std::vector<std::vector<int>> parents;
  std::vector<int> depth;
  int lg = 0;

  LowestCommonAncestor(std::vector<std::vector<int>> G, int root = 0) : graph(G), r(root) {
    n = G.size();
    assert(0 <= root && root < n);
    depth.resize(n, inf);
    build();
  }

  void build(){
    while ((1 << lg) < n) lg++;
    parents.resize(lg + 1, std::vector<int>(n));
    std::queue<int> que;
    que.emplace(r);
    depth[r] = 0;
    parents[0][r] = -1;
    while (!que.empty()) {
      int now = que.front();
      que.pop();
      for(const int &to: graph[now]) {
        if (depth[to] == inf) {
          depth[to] = depth[now] + 1;
          que.emplace(to);
          parents[0][to] = now;
        }
      }
    }
    for (int t = 0; t < lg; t++) {
      for (int i = 0; i < n; i++) {
        if (parents[t][i] == -1)
          parents[t + 1][i] = -1;
        else
          parents[t + 1][i] = parents[t][parents[t][i]];
      }
    }
  }

  int lca(int a, int b){
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);

    if (depth[a] > depth[b]) std::swap(a, b);
    while (depth[a] != depth[b]) {
      for (int to = lg; to >= 0; to--) {
        if (depth[b] - (1 << to) >= depth[a]) {
          b = parents[to][b];
          break;
        }
      }
    }
    if (a == b) return a;
    for (int to = lg; to >= 0; to--) {
      if (parents[to][a] != parents[to][b]) {
        a = parents[to][a];
        b = parents[to][b];
      }
    }
    return parents[0][a];
  }

  int distance(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return depth[u] + depth[v] - depth[lca(u, v)] * 2;
  }

  int la(int u, int k) {
    assert(0 <= u && u < n);
    assert(k >= 0);
    if (depth[u] < k) return -1;
    for (int i = 0; i <= lg; i++) {
      if ((k >> i) & 1) {
        k -= (1 << i);
        u = parents[i][u];
      }
      if (k == 0) break;
    }
    return u;
  }

  int jumpto(int u, int v, int k) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    assert(k >= 0);
    int l = lca(u, v);
    if (depth[u] - depth[l] >= k)
      return la(u, k);
    else {
      k -= (depth[u] - depth[l]);
      int d = depth[v] - depth[l];
      if (d - k < 0) return -1;
      else return la(v, d - k);
    }
  }

private:
  int n;
  std::vector<std::vector<int>> graph;
  int r;
  const int inf = 1 << 29;
};
