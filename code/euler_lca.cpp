#include "head.h"
const int N = 1e5 + 5, M = 2e5 + 5;
struct qxx {
  int nex, t;
};
qxx e[N * 2];
int h[N], le;
void add_path(int f, int t) { e[++le] = (qxx){h[f], t}, h[f] = le; }

int bg[N], ed[N], totime, dep[N], st[N * 2][20];
void dfs(int u, int p) {
  dep[u] = dep[p] + 1;
  bg[u] = ++totime;
  st[totime][0] = u;
  for (int i = h[u]; i; i = e[i].nex) {
    const int v = e[i].t;
    if (v == p) continue;
    dfs(v, u);
    st[++totime][0] = u;
  }
  ed[u] = totime;
}
void bin_exp() {
  FOR(j, 1, 19) {
    if ((1 << j) > totime) break;
    int ilim = totime - (1 << j) + 1;
    FOR(i, 1, ilim) {
      if (dep[st[i][j - 1]] < dep[st[i + (1 << j - 1)][j - 1]])
        st[i][j] = st[i][j - 1];
      else st[i][j] = st[i + (1 << j - 1)][j - 1];
    }
  }
}
int lca(int u, int v) {
  int l = bg[u], r = bg[v];
  if (l > r) l ^= r ^= l ^= r;
  int j = log(r - l + 1) / log(2);
  if (dep[st[l][j]] < dep[st[r - (1 << j) + 1][j]]) return st[l][j];
  else return st[r - (1 << j) + 1][j];
}
