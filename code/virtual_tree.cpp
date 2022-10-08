const int N = 5e5 + 5;

int n;
vector<int> g[N];
int dep[N], fa[N][20];
int dfn[N], totdfn;
void dfs(int u, int p) {
  dep[u] = dep[p] + 1, fa[u][0] = p, dfn[u] = ++totdfn;
  FOR(j, 1, 19) {
    fa[u][j] = fa[fa[u][j - 1]][j - 1];
    if (fa[u][j] == 0) break;
  }
  for (int v : g[u])
    if (v != p) dfs(v, u);
}
int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  ROF(j, 19, 0) if (dep[x] - (1 << j) >= dep[y]) x = fa[x][j];
  if (x == y) return x;
  ROF(j, 19, 0) if (fa[x][j] != fa[y][j]) x = fa[x][j], y = fa[y][j];
  return fa[x][0];
}
int distance(int x, int y) { return dep[x] + dep[y] - dep[lca(x, y)] * 2; }

typedef pair<int, int> pii;
vector<pii> vt[N];
void VT_addpath(int u, int v, int w) {
  vt[u].pb({v, w});
  vt[v].pb({u, w});
}

int s[N], tp;
void build_VT(vector<int> &V) { //建虚树并把点集更新到V里
  for (int u : V) vt[u].clear();
  sort(V.begin(), V.end(), [](int x, int y) { return dfn[x] < dfn[y]; });
  V.resize(unique(V.begin(), V.end()) - V.begin());
  s[tp = 1] = lca(V.front(), V.back());
  vector<int> Vt;
  for (int u : V) {
    int z = lca(s[tp], u);
    if (u == z) continue;
    while (tp > 1 && dep[s[tp - 1]] >= dep[z])
      VT_addpath(s[tp], s[tp - 1], distance(s[tp], s[tp - 1])), --tp;
    if (s[tp] != z) VT_addpath(s[tp], z, distance(s[tp], z)), s[tp] = z, Vt.pb(z);
    s[++tp] = u;
  }
  while (tp > 1) VT_addpath(s[tp], s[tp - 1], distance(s[tp], s[tp - 1])), --tp;
  V.pb(s[1]);
  V.insert(V.end(), Vt.begin(), Vt.end());
  sort(V.begin(), V.end(), [](int x, int y) { return dfn[x] < dfn[y]; });
  V.resize(unique(V.begin(), V.end()) - V.begin());
}
