#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#define ll long long
#define REP(i, n) for (ll (i) = 0; (i) < (n); (i)++)
#define REPI(i, a, b) for (ll (i) = (a); (i) < (b); (i)++)
#define int long long
using namespace std;
using P = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;

struct UnionFind {
  VI par, rank, diff_weight;
  UnionFind(int n) {
    par = VI(n); iota(par.begin(), par.end(), 0);
    rank = VI(n, 0);
    diff_weight = VI(n, 0);
  }
  int root(int x) {
    if (par[x] == x) {
      return x;
    } else {
      int r = root(par[x]);
      diff_weight[x] += diff_weight[par[x]];
      return par[x] = root(par[x]);
    }
  }
  bool unite(int x, int y, int w) {
    w += weight(x); w -= weight(y);
    x = root(x); y = root(y);
    if (x == y) { return false; }
    if (rank[x] < rank[y]) {
      diff_weight[x] -= w;
      par[x] = y;
    } else {
      diff_weight[y] += w;
      par[y] = x;
      if (rank[x] == rank[y]) { rank[x]++; }
    }
    return true;
  }
  bool same(int x, int y) {
    return root(x) == root(y);
  }
  int weight(int x) {
    root(x); return diff_weight[x];
  }
  int diff(int x, int y) {
    assert(same(x, y));
    return weight(y) - weight(x);
  }
};

signed main() {
}
