#include "head.h"
// https://uoj.ac/problem/117
const int M = 1e6 + 5, N = 1e6 + 5;
int t, n, m, a[M], la; // t = 1 无向图

struct qxx {
  int nex, t, v;
};
qxx e[M];
int h[N], le;
void add_path(int f, int t, int v) { e[++le] = (qxx){h[f], t, v}, h[f] = le; }

bool vis[N];
int d1[N], d2[N];
void dfs(int u) {
  for (int i = h[u]; i; i = h[u]) {
    while (i && vis[e[i].v]) i = e[i].nex;
    h[u] = i;
    const int v = e[i].t, w = e[i].v;
    if (i) vis[w] = 1, dfs(v), a[++la] = i % 2 ? w : (t == 2 ? w : -w);
  }
}

int main() {
  scanf("%d%d%d", &t, &n, &m);
  int u1, v1;
  FOR(i, 1, m) {
    scanf("%d%d", &u1, &v1);
    add_path(u1, v1, i);
    if (t == 1) add_path(v1, u1, i);
    d1[u1]++, d2[v1]++;
  }

  FOR(i, 1, n)
  if ((d1[i] & 1) ^ (d2[i] & 1) || (t == 2 && d1[i] != d2[i])) return puts("NO"), 0;

  dfs(u1);
  if (la < m) return puts("NO"), 0;
  puts("YES");
  ROF(i, la, 1) printf("%d ", a[i]);
  return 0;
}