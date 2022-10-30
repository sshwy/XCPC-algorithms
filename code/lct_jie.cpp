#include "head.h"
const int N = 300010;
int fa[N], ch[2][N], mx[N], w[N], sz[N], rev[N], T_sz[N];

void Rev(int u) { swap(ch[0][u], ch[1][u]), rev[u] ^= 1; }
void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u; }
int isroot(int u) { return (u != ch[0][fa[u]] && u != ch[1][fa[u]]) || !u; }
bool child(int u) { return u == ch[1][fa[u]]; }
int Max(int a, int b) { return w[a] > w[b] ? a : b; }
void pushup(int u) {
  sz[u] = sz[ch[0][u]] + sz[ch[1][u]] + 1 + T_sz[u];
  mx[u] = Max(mx[ch[0][u]], Max(ch[1][u], u));
}
void pushdown(int u) {
  if (rev[u]) Rev(ch[0][u]), Rev(ch[1][u]), rev[u] = 0;
}
void rotate(int u) {
  int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
  if (!isroot(f)) connect(u, ff, tmp1);
  fa[u] = ff, connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), pushup(f),
  pushup(u);
}
int st[N], tot, k;
void splay(int u) {
  int now = u, top = 0;
  st[++top] = now;
  while (!isroot(now)) st[++top] = now = fa[now];
  while (top) pushdown(st[top--]);
  for (int f; !isroot(u); rotate(u))
    if (!isroot(f = fa[u])) rotate(child(u) ^ child(f) ? u : f);
}
void access(int u) {
  for (int ls = 0; u; u = fa[ls = u])
    splay(u), T_sz[u] += sz[ch[1][u]], T_sz[u] -= sz[ls], ch[1][u] = ls, pushup(u);
}
void makeroot(int u) { access(u), splay(u), Rev(u); }

bool cut(int u, int v) {
  makeroot(u), access(v), splay(v);
  if (ch[0][v] != u) return true;
  if (sz[v] >= k && sz[u] < k && sz[v] - sz[u] < k) {
    if (tot <= 1) return false;
    tot--;
  } else if (sz[v] - sz[u] >= k && sz[v] >= k) tot++;
  ch[0][u] = fa[ch[0][u]] = 0, pushup(v);
  return true;
}
void link(int u, int v) {
  makeroot(u), access(v), splay(v);
  if (fa[u]) {
    int tmp = mx[v];
    if (tmp == v) return;
    splay(tmp), ch[1][tmp] = fa[ch[1][tmp]] = 0, pushup(tmp);
    splay(u), splay(v), fa[u] = v, T_sz[v] += sz[u], pushup(v);
    return;
  }
  if (sz[v] < k && sz[u] < k && sz[v] + sz[u] >= k) tot++;
  else if (sz[v] >= k && sz[u] >= k) tot--;
  fa[u] = v, T_sz[v] += sz[u], pushup(v);
}