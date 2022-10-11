#include "head.h"
const int N = 2e5 + 5, INF = 1e9;
// 最大费用最大流！
namespace MCMF {
  struct qxx {
    int nex, t, v, c;
  };
  qxx e[N];
  int h[N], le = 1;
  void ae(int f, int t, int v, int c) { e[++le] = (qxx){h[f], t, v, c}, h[f] = le; }
  void af(int f, int t, int v, int c) { ae(f, t, v, c), ae(t, f, 0, -c); }

  bool vis[N];
  queue<int> q;
  int s, t, d[N], pre[N], incf[N], maxflow, maxcost;
  bool spfa() {
    memset(d, -1, sizeof(d));
    q.push(s), d[s] = 0, incf[s] = INF, incf[t] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = 0;
      for (int i = h[u]; i; i = e[i].nex) {
        const int v = e[i].t, w = e[i].v, c = e[i].c;
        if (!w || d[v] >= d[u] + c) continue;
        d[v] = d[u] + c, incf[v] = min(incf[u], w), pre[v] = i;
        if (!vis[v]) q.push(v), vis[v] = 1;
      }
    }
    return incf[t];
  }
  void update() {
    maxflow += incf[t];
    for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
      e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
      maxcost += incf[t] * e[pre[u]].c;
    }
  }
  void go() {
    while (spfa()) update();
  }
} // namespace MCMF
