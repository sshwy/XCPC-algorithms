#include "head.h"
const int SZ = 1e5 + 5, INF = 1e9;
struct Splay {
  int tot, ch[SZ][2], key[SZ], sz[SZ], fa[SZ], root;
  int rv[SZ];
  int new_node(int v) {
    ++tot, ch[tot][0] = ch[tot][1] = fa[tot] = 0, key[tot] = v;
    sz[tot] = rv[tot] = 0;
    return tot;
  }
  Splay() {
    tot = 0, new_node(-INF), new_node(INF), fa[1] = 2, ch[2][0] = 1, root = 2;
  }
  bool get(int u) { return ch[fa[u]][1] == u; }
  void pU(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1; }
  void node_rv(int u) { swap(ch[u][0], ch[u][1]), rv[u] ^= 1; }
  void pD(int u) {
    if (rv[u]) node_rv(ch[u][0]), node_rv(ch[u][1]), rv[u] = 0;
  }
  void rotate(int u) {
    int p = fa[u], pp = fa[p], k = get(u);
    pD(u), ch[pp][get(p)] = u, fa[u] = pp;
    ch[p][k] = ch[u][!k], fa[ch[u][!k]] = p, ch[u][k ^ 1] = p, fa[p] = u;
    pU(p), pU(u);
  }
  void splay(int u, int v) {
    while (fa[u] != v) {
      int p = fa[u];
      if (fa[p] != v) rotate(get(u) == get(p) ? p : u);
      rotate(u);
    }
    if (!v) root = u;
  }
  bool find(int v) { // return if v exists. Based on key
    if (!root) return 0;
    int u = root;
    while (key[u] != v && ch[u][key[u] < v]) pD(u), u = ch[u][key[u] < v];
    splay(u, 0);
    return key[root] == v;
  }
  void insert(int v) {
    if (!root) return root = new_node(v), void();
    int u = root, nu = new_node(v);
    while (ch[u][key[u] < v]) pD(u), u = ch[u][key[u] < v];
    ch[u][key[u] < v] = nu, fa[nu] = u;
    splay(nu, 0);
  }
  int kth(int rk) {
    ++rk;
    if (!root) return 0;
    int u = root;
    while (sz[ch[u][0]] + 1 != rk) {
      pD(u);
      if (rk <= sz[ch[u][0]]) u = ch[u][0];
      else rk -= sz[ch[u][0]] + 1, u = ch[u][1];
    }
    splay(u, 0);
    return u;
  }
};
