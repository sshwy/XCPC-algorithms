const int N = 1e5 + 5;
struct qxx {
  int nex, t, v;
} e[N * 2];
int h[N], le = 1;
void add_path(int f, int t, int v) { e[++le] = {h[f], t, v}, h[f] = le; }
int n;
bool Cut[N];
int sz[N], sm[N];
void Size(int u, int p) {
  sz[u] = 1, sm[u] = 0;
  for (int i = h[u]; i; i = e[i].nex) {
    int v = e[i].t;
    if (!Cut[v] && v != p) Size(v, u), sz[u] += sz[v], sm[u] = max(sm[u], sz[v]);
  }
}
int Core(int u, int p, int T) {
  int res = u, mx = max(T - sz[u], sm[u]);
  for (int i = h[u]; i; i = e[i].nex) {
    int v = e[i].t;
    if (!Cut[v] && v != p) {
      int x = Core(v, u, T), y = max(T - sz[x], sm[x]);
      if (y < mx) res = x, mx = y;
    }
  }
  return res;
}
void Solve(int u, int p) {
  Size(u, p);
  int core = Core(u, p, sz[u]);
  // do sth ...
  Cut[core] = 1;
  for (int i = h[core]; i; i = e[i].nex) {
    int v = e[i].t;
    if (!Cut[v]) Solve(v, core);
  }
}
