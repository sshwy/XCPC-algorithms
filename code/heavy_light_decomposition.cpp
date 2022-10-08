vector<int> g[N];
int sz[N], dep[N], big[N], top[N], fa[N], totdfn;
int b[N], id[N];
void dfs1(int u, int p) {
  sz[u] = 1, dep[u] = dep[p] + 1, big[u] = 0, fa[u] = p;
  for (int v : g[u])
    if (v != p)
      dfs1(v, u), sz[u] += sz[v], (!big[u] || sz[big[u]] < sz[v]) ? big[u] = v : 0;
}
void dfs2(int u, int p, int tp) {
  top[u] = tp, b[++totdfn] = u, id[u] = totdfn;
  if (big[u]) dfs2(big[u], u, tp);
  for (int v : g[u])
    if (v != p && v != big[u]) dfs2(v, u, v);
}
int lca(int u, int v) {
  while (top[u] != top[v])
    dep[top[u]] < dep[top[v]] ? swap(u, v), 0 : 0, u = fa[top[u]];
  return dep[u] < dep[v] ? u : v;
}
int kthanc(int u, int k) {
  while (dep[u] - k < dep[top[u]]) k -= dep[u] - dep[top[u]] + 1, u = fa[top[u]];
  return b[id[top[u]] + dep[u] - dep[top[u]] - k];
}
