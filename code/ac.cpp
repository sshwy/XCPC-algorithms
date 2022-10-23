#include "head.h"
const int SZ = 1e5 + 5, ALP = 26;
struct AC { // 0 是起始结点
  int tr[SZ][26], fail[SZ], tot, q[SZ], ql, qr;
  void init() { tot = -1, new_node(); }
  int new_node() {
    return ++tot, fail[tot] = 0, memset(tr[tot], 0, sizeof(tr[tot])), tot;
  }
  void insert(const char *s) {
    int u = 0;
    while (*s) {
      int c = *s - '0';
      if (!tr[u][c]) tr[u][c] = new_node();
      u = tr[u][c], ++s;
    }
  }
  void build() {
    ql = 1, qr = 0;
    FOR(i, 0, ALP - 1) if (tr[0][i]) q[++qr] = tr[0][i];
    while (ql <= qr) {
      int u = q[ql++];
      FOR(c, 0, ALP - 1) {
        if (tr[u][c]) fail[tr[u][c]] = tr[fail[u]][c], q[++qr] = tr[u][c];
        else tr[u][c] = tr[fail[u]][c];
      }
    } // q 里就是 BFS 序
  }
  AC() { init(); }
};