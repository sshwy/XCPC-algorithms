int n, a[N], root;
int s[N], tp, lc[N], rc[N];
void al(int u, int v) { lc[u] = v; }
void ar(int u, int v) { rc[u] = v; }
void build() {
  FOR(i, 1, n) {
    while (tp > 1 && a[s[tp - 1]] <= a[i]) ar(s[tp - 1], s[tp]), --tp;
    if (tp > 0 && a[s[tp]] <= a[i]) al(i, s[tp]), --tp;
    s[++tp] = i;
  }
  while (tp > 1) ar(s[tp - 1], s[tp]), --tp;
  root = s[1];
}
