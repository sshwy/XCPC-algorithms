#include "head.h"
const int SZ = 2e5 + 5;
int lc[SZ], rc[SZ], val[SZ], dep[SZ], tot;
int new_node(int v) {
  return ++tot, val[tot] = v, lc[tot] = rc[tot] = 0, dep[tot] = 0, tot;
}
int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (val[x] > val[y]) swap(x, y);
  rc[x] = merge(rc[x], y);
  if (dep[lc[x]] < dep[rc[x]]) swap(lc[x], rc[x]);
  dep[x] = dep[rc[x]] + 1;
  return x;
}
int getmin(int x) { return val[x]; }
int pop(int x) { return val[x] = -1, merge(lc[x], rc[x]); }