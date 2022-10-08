vector<int> g[N];
int dep[N], lon[N], hei[N], fa[N][20], f0[N], htop[N];
vector<int> up[N], dn[N];
void dfs1(int u, int p) {
  dep[u] = dep[p] + 1, lon[u] = 0, fa[u][0] = p, f0[u] = p;
  for (int j = 1; fa[u][j - 1] && j < 20; j++) fa[u][j] = fa[fa[u][j - 1]][j - 1];
  for (int v : g[u])
    if (v != p) dfs1(v, u), (!lon[u] || hei[lon[u]] < hei[v]) ? lon[u] = v : 0;
  hei[u] = lon[u] ? hei[lon[u]] + 1 : 1;
}
void dfs3(int u, int p, int htp) {
  htop[u] = htp;
  if (u == htp) {
    for (int v = u; v; v = lon[v]) dn[u].pb(v);
    for (int v = u; v && up[u].size() < dn[u].size(); v = f0[v]) up[u].pb(v);
  }
  if (lon[u]) dfs3(lon[u], u, htp);
  for (int v : g[u])
    if (v != p && v != lon[u]) dfs3(v, u, v);
}
int highbit[N];
int kthanc(int u, int k) {
  if (dep[u] <= k) return 0;
  if (k == 0) return u;
  u = fa[u][highbit[k]], k -= 1 << highbit[k];
  int d = dep[u] - k - dep[htop[u]];
  if (d >= 0) return dn[htop[u]][d];
  else return up[htop[u]][-d];
}
// FOR(i,1,n)highbit[i]=i==1?0:highbit[i>>1]+1;
