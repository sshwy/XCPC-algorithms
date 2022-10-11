#include "head.h"
const int N = 5e4 + 5, M = N * 2, INF = 0x3f3f3f3f;
struct qxx {
  int nex, t, v;
};
qxx e[M];
int h[N], hh[N], le = 1;
void ae(int f, int t, int v) { e[++le] = (qxx){h[f], t, v}, h[f] = le; }
void af(int f, int t, int v) { ae(f, t, v), ae(t, f, 0); }
void af_bidir(int f, int t, int v) { ae(f, t, v), ae(t, f, v); }
#define FORe(i, u, v, w) \
  for (int i = h[u], v, w; v = e[i].t, w = e[i].v, i; i = e[i].nex)
#define FORflowe(i, u, v, w) \
  for (int &i = hh[u], v, w; v = e[i].t, w = e[i].v, i; i = e[i].nex)

int s, t, dep[N];
queue<int> q;

bool bfs() {
  memset(dep, 0, sizeof(dep)); // 可以优化
  dep[s] = 1, q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    FORe(i, u, v, w) if (!dep[v] && w) dep[v] = dep[u] + 1, q.push(v);
  }
  return dep[t] != 0;
}
int dfs(int u, int flow) {
  if (u == t || !flow) return flow;
  int rest = flow;
  FORflowe(i, u, v, w) {
    if (!w || dep[v] != dep[u] + 1) continue;
    int k = dfs(v, min(rest, w));
    e[i].v -= k, e[i ^ 1].v += k, rest -= k;
    if (!rest) break;
  }
  return flow - rest;
}
int dinic() {
  int maxflow = 0;
  while (bfs()) {
    memcpy(hh, h, sizeof(h)); // 可以优化
    for (int x; (x = dfs(s, INF));) maxflow += x;
  }
  return maxflow;
}
