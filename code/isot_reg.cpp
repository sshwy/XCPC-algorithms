#include "head.h"

const int N = 1005, M = 70, SZ = M * N * 4, INF = 0x3f3f3f3f;
typedef unsigned long long ULL;

struct NetworkFlow {
  int s, t, l;
  struct qxx {
    int nex, t, v;
  } e[SZ];
  int h[N], hh[N], le;
  void ae(int u, int v, int c) { e[++le] = (qxx){h[u], v, c}, h[u] = le; }
  void af(int u, int v, int c) { ae(u, v, c), ae(v, u, 0); }
#define for_adj(i, u, v) for (int i = h[u], v; v = e[i].t, i; i = e[i].nex)
#define for_adj_hh(i, u, v) for (int &i = hh[u], v; v = e[i].t, i; i = e[i].nex)
  int d[N];
  void init(int len) {
    l = len, le = 1, s = 0, t = len + 1;
    memset(h, 0, sizeof(h[0]) * (len + 2));
  }
  queue<int> q;
  bool bfs() {
    memset(d, -1, sizeof(d));
    d[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for_adj(i, u, v) if (e[i].v && d[v] == -1) d[v] = d[u] + 1, q.push(v);
    }
    return d[t] != -1;
  }
  int dfs(int u, int flow) {
    if (u == t || !flow) return flow;
    int rest = flow;
    for_adj_hh(i, u, v) if (e[i].v && d[v] == d[u] + 1) {
      int k = dfs(v, min(e[i].v, rest));
      e[i].v -= k, e[i ^ 1].v += k, rest -= k;
      if (!rest) break;
    }
    return flow - rest;
  }
  void go() {
    while (bfs()) {
      memcpy(hh, h, sizeof(h[0]) * (l + 2));
      dfs(s, INF);
    }
  }
  bool inS(int u) { return d[u] != -1; }
} flow;

struct base {
  ULL b[M];
  base() { memset(b, 0, sizeof(b)); }
  bool insert(ULL x) {
    ROF(i, 63, 0) if (x >> i & 1) {
      if (b[i]) x ^= b[i];
      else return b[i] = x, true;
    }
    return false;
  }
  bool check(ULL x) {
    ROF(i, 63, 0) if (x >> i & 1) {
      if (b[i]) x ^= b[i];
      else return true;
    }
    return false;
  }
};

vector<int> g[N];
void ae(int u, int v) { g[u].push_back(v); } // (u,v): f(u) <= f(v)

int n, m, a[M], b[M];
int nd[N], tag[N], ntag;
int t1[N], t2[N], f[N], id[N];
ULL c[N], v[N];

void solve(int L, int R, int l, int r) { // f in [L,R], nd[l..r]
  if (L == R) {
    FOR(i, l, r) f[nd[i]] = L;
    return;
  }
  int Mid = (L + R) >> 1, l1 = 0, l2 = 0;
  // f = Mid or Mid+1
  ++ntag;
  FOR(i, l, r) tag[nd[i]] = ntag, id[nd[i]] = i - l + 1;
  flow.init(r - l + 1);
  FOR(i, l, r) {
    int u = nd[i], w = 2 * Mid - 2 * v[u] + 1;
    if (w > 0) flow.af(id[u], flow.t, w);
    else flow.af(flow.s, id[u], -w);
    for_each(j, g[u]) if (tag[g[u][j]] == ntag) flow.af(id[u], id[g[u][j]], INF);
  }
  flow.go();
  FOR(i, l, r) {
    int u = nd[i];
    if (flow.inS(id[u])) t2[++l2] = u;
    else t1[++l1] = u;
  } // assert(l1 + l2 == r - l + 1);
  FOR(i, 1, l1) nd[i + l - 1] = t1[i];
  FOR(i, 1, l2) nd[i + l + l1 - 1] = t2[i];
  solve(L, Mid, l, l + l1 - 1), solve(Mid + 1, R, l + l1, r);
}
void buildE() {
  FOR(i, 1, m) {
    base B;
    FOR(j, 1, m) if (j != i) assert(B.insert(c[a[j]]));
    FOR(j, 1, n) if (j != a[i] && B.check(c[j])) ae(a[i], j);
  }
  FOR(i, 1, m) {
    base B;
    FOR(j, 1, m) if (j != i) assert(B.insert(c[b[j]]));
    FOR(j, 1, n) if (j != b[i] && B.check(c[j])) ae(j, b[i]);
  }
}
int main() {
  scanf("%d%d", &n, &m);
  FOR(i, 1, n) scanf("%llu", c + i);
  FOR(i, 1, n) scanf("%llu", v + i);
  FOR(i, 1, m) scanf("%d", a + i);
  FOR(i, 1, m) scanf("%d", b + i);

  buildE();
  FOR(i, 1, n) nd[i] = i;
  solve(0, *max_element(v + 1, v + n + 1), 1, n);
  ULL ans = 0;
  FOR(i, 1, n) ans += (f[i] - v[i]) * (f[i] - v[i]);
  // FOR(i,1,n) printf("%d%c", f[i], " \n"[i==n]);
  printf("%llu", ans);
  return 0;
}