#include "head.h"
const int N = 1e6 + 5, M = N * 2;
struct qxx {
  int nex, t;
} e[M];
int h[N], le;
void add_path(int f, int t) { e[++le] = (qxx){h[f], t}, h[f] = le; }
#define FORe(i, u, v) for (int i = h[u], v; v = e[i].t, i; i = e[i].nex)

bool in_s[N];
int dfn[N], low[N], totdfn, s[N], tp;
int scc[N], totscc, sz[N]; // 每个点所属SCC标号，每个SCC的大小
void dfs(int u) {
  low[u] = dfn[u] = ++totdfn;
  s[++tp] = u, in_s[u] = 1;
  FORe(i, u, v) {
    if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
    else if (in_s[v]) low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    ++totscc;
    while (s[tp] != u) scc[s[tp]] = totscc, in_s[s[tp]] = 0, --tp, ++sz[totscc];
    scc[s[tp]] = totscc, in_s[s[tp]] = 0, --tp, ++sz[totscc];
  }
}
// FOR(i, 1, n) if(!dfn[i]) dfs(i);
