#include "head.h"
#define for_adj(g, i, u, v) for (int i = g.h[u], v; v = g.e[i].t, i; i = g.e[i].nex)

const int N = 2e5 + 5, M = 5e5 + 5, P = 1e9 + 7;

vector<int> g1[N], g2[N];

int n, m, ex[M], ey[M], dg[N], tag[N], tc[N];

bool good(int u, int v) { return dg[u] > dg[v] || (dg[u] == dg[v] && u > v); }
void go() {
  int n, m;
  cin >> n >> m;
  fill(dg, dg + n + 1, 0);
  FOR(i, 1, n) g1[i].clear(), g2[i].clear();
  FOR(i, 1, m) {
    cin >> ex[i] >> ey[i];
    dg[ex[i]]++, dg[ey[i]]++;
  }
  FOR(i, 1, m) {
    int u = ex[i], v = ey[i];
    if (!good(u, v)) swap(u, v);
    g2[u].push_back(v);
    g1[u].push_back(v);
    g1[v].push_back(u);
  }

  long long c3 = 0, c4 = 0;
  fill(tag, tag + n + 1, 0);
  FOR(u, 1, n) {
    for (int v : g2[u]) tag[v] = u;
    for (int v : g2[u])
      for (int w : g2[v])
        if (tag[w] == u) ++c3;
  }
  fill(tag, tag + n + 1, 0);
  FOR(u, 1, n) {
    for (int v : g2[u])
      for (int w : g1[v]) {
        if (w == u || !good(u, w)) continue;
        if (tag[w] != u) tc[w] = 0;
        c4 += tc[w];
        tag[w] = u, ++tc[w];
      }
  }
  int ans = (c3 % P * 3 % P + c4 % P + 1ll * m * (n + m - 3) % P) % P;
  FOR(i, 1, n) ans = (ans + (1ll * dg[i] * (dg[i] - 1) / 2) % P) % P;
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  FOR(i, 1, t) go();
  return 0;
}
