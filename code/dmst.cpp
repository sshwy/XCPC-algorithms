#include "head.h"
/// Chu-Liu/Edmonds' algorithm
/// 计算有向图（允许重边、不允许自环）给定根的最小权外向生成树（最小树形图）
/// vector<Edge> buildFrom(n, r, ve): n 个点，边集是 ve，根是 r 的最小权外向生成树
///   若无解则返回一个空的 vector
///   要求 ve 非空
///
/// Usage:
const int N = 115, M = 10004;
DirectedMST<N, M> DMST;
int n, m, r;
vector<Edge> E;
int main() {
  scanf("%d%d%d", &n, &m, &r);
  FOR(i, 1, m) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w), E.push_back(Edge(u, v, w));
  }
  auto Et = DMST.buildFrom(n, r, E);

  if (Et.empty()) puts("-1");
  else {
    int ans = 0;
    for (auto e : Et) ans += e.w;
    printf("%d\n", ans);
  }
  return 0;
}
// Algorithm
struct Edge {
  int u, v, w, ow;
  Edge(int _u, int _v, int _w) { u = _u, v = _v, w = ow = _w; }
  void reset() { w = ow; }
};

template <const int N, const int M> struct DirectedMST {
  int nd[N], tnd[N], fa[N], pre[N], In[N], Time[M], totTime, onCir[N], totCir;
  vector<int> toggle[M];

  int get(int u) { return fa[u] == u ? u : fa[u] = get(fa[u]); }
  int getNode(int u) { return nd[u] == u ? u : nd[u] = getNode(nd[u]); }

  bool work(const int n, const int root, vector<Edge> &ve) {
    bool flag = false;
    fill(In, In + n + 1, -1), fill(onCir, onCir + n + 1, 0);
    totCir = 0;

    for_each(i, ve) {
      int u = getNode(ve[i].u), v = getNode(ve[i].v);
      if (u == v) continue;
      if (In[v] == -1 || ve[In[v]].w > ve[i].w) In[v] = i;
    }
    FOR(i, 1, n) fa[i] = i;
    FOR(i, 1, n) if (i != root && getNode(i) == i) {
      if (In[i] == -1) return false;
      Edge e = ve[In[i]];
      int u = getNode(e.u), v = getNode(e.v);
      if (u == v) continue;
      if (get(u) == get(v)) {
        ++totCir;
        for (int z = u; z != -1; z = z == v ? -1 : getNode(ve[In[z]].u))
          onCir[z] = totCir, tnd[z] = v, Time[In[z]] = ++totTime; // assert(z);
        flag = true;
      } else fa[get(u)] = get(v);
    }

    for_each(i, ve) {
      auto &e = ve[i];
      int u = getNode(e.u), v = getNode(e.v);
      if (u == v) continue;
      if (onCir[v] && onCir[v] == onCir[u]) continue;
      if (onCir[v]) toggle[i].push_back(In[v]), e.w -= ve[In[v]].w;
    }

    FOR(i, 1, n) if (onCir[i]) nd[i] = tnd[i]; // assert(getNode(i) == i);
    return flag;
  }
  vector<Edge> buildFrom(int n, int root, vector<Edge> ve) {
    assert(!ve.empty());
    vector<Edge> vt;
    FOR(i, 1, n) nd[i] = i;
    fill(Time, Time + ve.size() + 1, 0), totTime = 0;
    while (work(n, root, ve)) {}
    FOR(i, 1, n) if (getNode(i) == i && i != root) {
      if (In[i] == -1) return vt; // empty
      Time[In[i]] = ++totTime;
    }
    vector<int> SortByTime(totTime + 1, -1);
    for_each(i, ve) if (Time[i]) SortByTime[Time[i]] = i;
    ROF(i, totTime, 1) {
      int x = SortByTime[i];
      if (Time[x])
        for (int y : toggle[x]) Time[y] = 0;
    }
    for_each(i, ve) {
      ve[i].reset();
      if (Time[i]) vt.push_back(ve[i]);
    } // assert(vt.size() == n - 1);
    return vt;
  }
};
