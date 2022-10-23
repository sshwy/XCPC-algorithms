#include "head.h"
const int N = 1e6 + 5;
vector<int> g[N], up[N], dn[N];
int dep[N], son[N], he[N], fa[N][20], f0[N], top[N];
void dfs1(int u, int p) {
  dep[u] = dep[p] + 1, son[u] = 0, fa[u][0] = p, f0[u] = p;
  for (int j = 1; fa[u][j - 1] && j < 20; j++) fa[u][j] = fa[fa[u][j - 1]][j - 1];
  for (int v : g[u])
    if (v != p) dfs1(v, u), he[son[u]] < he[v] ? son[u] = v : 0;
  he[u] = son[u] ? he[son[u]] + 1 : 1;
}
void dfs3(int u, int p, int htp) {
  top[u] = htp;
  if (u == htp) {
    for (int v = u; v; v = son[v]) dn[u].pb(v);
    for (int v = u; v && up[u].size() < dn[u].size(); v = f0[v]) up[u].pb(v);
  }
  if (son[u]) dfs3(son[u], u, htp);
  for (int v : g[u])
    if (v != p && v != son[u]) dfs3(v, u, v);
}
int hbit[N]; // FOR(i, 1, n) hbit[i] = i == 1 ? 0 : hbit[i >> 1] + 1;
int kthanc(int u, int k) {
  if (dep[u] <= k) return 0;
  if (k == 0) return u;
  u = fa[u][hbit[k]], k -= 1 << hbit[k];
  int d = dep[u] - k - dep[top[u]];
  if (d >= 0) return dn[top[u]][d];
  else return up[top[u]][-d];
}