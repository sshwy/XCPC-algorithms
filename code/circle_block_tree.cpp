#include "head.h"
const int N = 5e5 + 5, M = N;
struct qxx {
  int nex, t;
};
qxx e[M];
int h[N], le = 1;
void ae(int f, int t) { e[++le] = (qxx){h[f], t}, h[f] = le; }

void tree_ae(int u, int v) {} // 圆方树加边

int n, m;
int dfn[N], low[N], ndfn, s[N], tp, vcc;
void tarjan(int u, int p) {
  dfn[u] = low[u] = ++ndfn;
  s[++tp] = u;
  for (int i = h[u]; i; i = e[i].nex) {
    const int v = e[i].t;
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v]) {
        ++vcc, tree_ae(u, vcc + n);
        do { tree_ae(s[tp], vcc + n); } while (s[tp--] != v);
      }
    } else low[u] = min(low[u], dfn[v]);
  }
}