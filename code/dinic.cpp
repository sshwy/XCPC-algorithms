const int N = 5e5 + 5, M = 5e5 + 5, INF = 0x3f3f3f3f;
struct qxx {
  int nex, t, v;
};
qxx e[M];
int h[N], cnt = 1;
void add_path(int f, int t, int v) { e[++cnt] = (qxx){h[f], t, v}, h[f] = cnt; }
void add_flow(int f, int t, int v) { add_path(f, t, v), add_path(t, f, 0); }
void add_dual_flow(int f, int t, int v) { add_path(f, t, v), add_path(t, f, v); }

namespace DINIC {
  int s, t, maxflow, d[N];
  queue<int> q;
  bool bfs() {
    memset(d, 0, sizeof(d));
    q.push(s), d[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t, &w = e[i].v;
        if (!d[v] && w) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t];
  }
  int dinic(int u, int flow) {
    if (u == t) return flow;
    int k, rest = flow;
    for (int i = h[u]; i && rest; i = e[i].nex) {
      const int &v = e[i].t, &w = e[i].v;
      if (!w || d[v] != d[u] + 1) continue;
      k = dinic(v, min(rest, w));
      if (k) e[i].v -= k, e[i ^ 1].v += k, rest -= k;
      else d[v] = 0;
    }
    return flow - rest;
  }
  void go() {
    while (bfs())
      for (int i; i = dinic(s, INF);) maxflow += i;
  }
} // namespace DINIC
/*
 * add_dual_flow:无向边的流（即双向可流）
 */
