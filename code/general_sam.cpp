#include "head.h"
const int N = 2e6 + 50, C = 12;

struct qxx {
  int nex, t;
};
qxx e[N * 2];
int h[N], le = 1;
void add_path(int f, int t) { e[++le] = (qxx){h[f], t}, h[f] = le; }

int n, c, col[N], dg[N];

namespace T {
  int tr[N][C], tr_tot = 1;
  void dfs_add_trie(int u, int p, int tu) {
    int cu = col[u];
    if (!tr[tu][cu]) tr[tu][cu] = ++tr_tot;
    tu = tr[tu][cu];
    for (int i = h[u], v; v = e[i].t, i; i = e[i].nex) {
      if (v == p) continue;
      dfs_add_trie(v, u, tu);
    }
  }
} // namespace T
const int SZ = 2e6 + 5, ALP = 11;
int last[SZ];
struct SAM {
  int tot;
  int len[SZ], tr[SZ][ALP], fail[SZ];
  int tnode[SZ];
  // tnode表示trie上状态的左后一个字符的某一个结点。
  SAM() { tot = 1, len[1] = 0, fail[1] = 0; }
  void insert(int tu, int x) {
    int v = T::tr[tu][x], p = last[tu], u = tr[p][x];
    if (!u) {
      u = ++tot, len[u] = len[p] + 1;
      tnode[u] = v;
      while (p && !tr[p][x]) tr[p][x] = u, p = fail[p];
    }
    last[v] = u;
    if (!p) fail[u] = 1;
    else {
      int q = tr[p][x];
      if (len[q] == len[p] + 1) fail[u] = q;
      else {
        int cq = ++tot;
        len[cq] = len[p] + 1, fail[cq] = fail[q];
        tnode[cq] = tnode[q];
        memcpy(tr[cq], tr[q], sizeof(tr[q]));
        fail[q] = fail[u] = cq;
        while (p && tr[p][x] == q) tr[p][x] = cq, p = fail[p];
      }
    }
  }
  void print_node(int u) {
    printf("u=%2d,len=%2d,fail=%2d,tnode=%2d\n", u, len[u], fail[u], tnode[u]);
  }
  void count() {
    LL ans = 0;
    FOR(i, 1, tot) ans += len[i] - len[fail[i]];
    printf("%lld", ans);
  }
} sam;
queue<int> q;
void go() {
  last[1] = 1;
  q.push(1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    FOR(i, 0, c - 1) {
      if (!T::tr[u][i]) continue;
      sam.insert(u, i);
      q.push(T::tr[u][i]);
    }
  }
  sam.count();
}
int main() {
  scanf("%d%d", &n, &c);
  FOR(i, 1, n) scanf("%d", &col[i]);
  FOR(i, 1, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    add_path(u, v), add_path(v, u);
    dg[u]++, dg[v]++;
  }
  FOR(i, 1, n) if (dg[i] == 1) T::dfs_add_trie(i, 0, 1);
  go();
  return 0;
}
