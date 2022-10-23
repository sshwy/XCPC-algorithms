#include "head.h"
const int SZ = 2e6 + 500, ALP = 26;
struct SAM { // 1 是起始结点
  int tot, las, s[SZ], ls;
  int tr[SZ][ALP], fail[SZ], len[SZ], end[SZ];
  SAM() { tot = las = 1, len[1] = 0, fail[1] = 0; }
  void insert(char x) {
    s[++ls] = (x -= 'a');
    int u = ++tot, p = las;
    len[u] = len[las] + 1, las = u;
    end[u] = ls; // u 的卫星信息
    while (p && tr[p][x] == 0) tr[p][x] = u, p = fail[p];
    if (!p) fail[u] = 1;
    else {
      int q = tr[p][x];
      if (len[q] == len[p] + 1) fail[u] = q;
      else {
        int cq = ++tot;
        len[cq] = len[p] + 1, fail[cq] = fail[q];
        end[cq] = end[q]; // cq 的卫星信息
        memcpy(tr[cq], tr[q], sizeof(tr[q]));
        fail[q] = fail[u] = cq;
        while (p && tr[p][x] == q) tr[p][x] = cq, p = fail[p];
      }
    }
  }
  void print_node(int u) { // 输出每个结点的状态
    printf("u=%d,len=%d,fail=%d, ", u, len[u], fail[u]);
    FOR(i, end[u] - len[u] + 1, end[u]) putchar(s[i]);
    puts("");
  }
};